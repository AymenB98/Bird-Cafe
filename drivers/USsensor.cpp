//!**************************************************************
//! \file
//! \brief Defines Ultrasonic subclass
//!**************************************************************

#include "USsensor.h"
#include "UDP.h"
#include "latencyTimers.h"
#include <Python.h>
#include <curses.h>

 #define LATENCY_DEBUG

// Pre-porcessor to seperate testing code with the rest of the code
#ifdef LATENCY_DEBUG

float fullDuration;
float tweetDuration;
float USDuration;
float imageReadDuration;

FILE* fullDurLog = fopen("fullDurLog.dat", "at");
FILE* tweetDurLog = fopen("tweetDurLog.dat", "at");
FILE* usDurLog = fopen("usDurLog.dat", "at");
FILE* imReadDurLog = fopen("imReadDurLog.dat", "at");
#endif

float Ultrasonic::distanceCalcUS(float pulseTime)
{
    float pulseDist = (pulseTime*speed_of_sound)/2;
    return pulseDist;
}

float Ultrasonic::measureDistance()
{
    digitalWrite(trig, LOW); //trigger pin low for 2us, clears pin
    delayMicroseconds(2);
    digitalWrite(trig, HIGH); //trigger pin high for 10us to send pulse
    delayMicroseconds(10);
    digitalWrite(trig, LOW); //trigger pin low to end 10us pulse
   
   std::chrono::high_resolution_clock::time_point loopStart = std::chrono::high_resolution_clock::now(); 
   bool timeout = 0;
    while (digitalRead(echo) == LOW && timeout == 0)
    {
        if((std::chrono::duration<float>(std::chrono::high_resolution_clock::now()-loopStart).count()) >1) //throws error if stuck in loop
        {
            timeout = 1; //Prevents getting stuck in loop if hardware fault - will result in a very short distance being measured
            printf("Echo pin stuck low\n");
            
        }
    }
    std::chrono::high_resolution_clock::time_point timerStart = std::chrono::high_resolution_clock::now(); //start timer
    while (digitalRead(echo) == HIGH)
    {
       if((std::chrono::duration<float>(std::chrono::high_resolution_clock::now()-timerStart).count()) >1) //throws error if stuck in loop

        {
            timeout = 1; //Prevents getting stuck in loop if hardware fault - will result in a very long distance being measured
            printf("Echo pin stuck high\n");
        }
    }
    std::chrono::high_resolution_clock::time_point timerStop = std::chrono::high_resolution_clock::now();  //stop timer

    float pulseDur = std::chrono::duration<float>(timerStop-timerStart).count(); //force timer to float
    float distance = distanceCalcUS(pulseDur);

    return distance;
}

Ultrasonic::Ultrasonic(int Trig, int Echo)
{
    wiringPiSetupGpio(); 

    echo = Echo;
    trig = Trig;

    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);
}

void Ultrasonic::setTrigger(int Trig)
{
    trig = Trig;
}

void Ultrasonic::setEcho(int Echo)
{
    echo = Echo;
}

void Ultrasonic::start()
{
    if (USThread)
    {
        std::cout << "thread already running";
        //throw "ERROR: Thread already running.";
    }
        USThread = new std::thread(run, this);
}

void Ultrasonic::stop()
{
    running = 0;
    if (USThread)
    {
        USThread->join();
        delete USThread;
        USThread = NULL;
    }
}


//! @brief The getFileContent function has been adapted from code written by Q-Engineering called 'TFLite_Classifier.cpp'
//! available on https://www.github.com/Qengineering/TensorFlow_Lite_SSD_RPi_32-bits
//! The purpose of this function is to extract the labels found in the COCO_labels.txt file.
bool Ultrasonic::getFileContent(std::string fileName)
{
	
    // Open the File
	std::ifstream in(fileName.c_str());
	// Check if object is valid
	if(!in.is_open()) return false;

	std::string str;
	// Read the next line from File untill it reaches the end.
	while (std::getline(in, str))
	{
		// Line contains string of length > 0 then save it in vector
		if(str.size()>0) Labels.push_back(str);
	}
	// Close The File
	in.close();
	return true;
}


//! @brief The detect_from_picture function has been adapted from code written by Q-Engineering called 'TFLite_Classifier.cpp'
//! available on https://www.github.com/Qengineering/TensorFlow_Lite_SSD_RPi_32-bits
//! The purpose of this function is to output classification labels and prediction scores for objects detected in a picture.
void Ultrasonic::detect_from_picture(Mat &src)
{
    
    std::unique_ptr<tflite::Interpreter> interpreter;

    Mat image;
    int cam_width =src.cols;
    int cam_height=src.rows;
    float f;
    int i;
    string name;

#ifdef LATENCY_DEBUG
    // Timer start variable for image classification
    std::chrono::high_resolution_clock::time_point imageReadTimerStart = std::chrono::high_resolution_clock::now(); 
#endif
    // Load model
    auto model = tflite::FlatBufferModel::BuildFromFile("../../drivers/detect.tflite");
    
    // Build the interpreter

    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);

    interpreter->AllocateTensors();

	// Get the names
	bool result = getFileContent("../../drivers/COCO_labels.txt");
	if(!result)
	{
        cout << "loading labels failed";
        exit(-1);
	}

    // Copy image to input as input tensor
    cv::resize(src, image, Size(width,height));
    memcpy(interpreter->typed_input_tensor<uchar>(0), image.data, image.total() * image.elemSize());

    interpreter->SetAllowFp16PrecisionForFp32(true);
    
    // Quad core
    interpreter->SetNumThreads(4);      

    // Run the model
    interpreter->Invoke();      


    const float* detection_locations = interpreter->tensor(interpreter->outputs()[0])->data.f;
    const float* detection_classes=interpreter->tensor(interpreter->outputs()[1])->data.f;
    const float* detection_scores = interpreter->tensor(interpreter->outputs()[2])->data.f;
    const int    num_detections = *interpreter->tensor(interpreter->outputs()[3])->data.f;

    // Set confidence threshold for model
    const float confidence_threshold = 0.44;
    //Bool tweet used to check if classification of "bird" is above threshold
    bool tweet = false;

    for(int i = 0; i < num_detections; i++){
        if(detection_scores[i] >= confidence_threshold){
            int  det_index = (int)detection_classes[i]+1;
            float y1=detection_locations[4*i  ]*cam_height;
            float x1=detection_locations[4*i+1]*cam_width;
            float y2=detection_locations[4*i+2]*cam_height;
            float x2=detection_locations[4*i+3]*cam_width;

            Rect rec((int)x1, (int)y1, (int)(x2 - x1), (int)(y2 - y1));
          
            rectangle(src,rec, Scalar(0, 0, 255), 1, 8, 0);
           
            putText(src, format("%s", Labels[det_index].c_str()), Point(x1, y1-5) ,FONT_HERSHEY_SIMPLEX,0.5, Scalar(0, 0, 255), 1, 8, 0);
           
            // An output to the terminal
            /*  
             *  This is used to output the detection scores from the confidence_threshold
             *  to a max of 1 alongside it's corresponding label for each of the objects
             *  detected in the image provided.
             */
            cout << detection_scores[i] << " : " << Labels[det_index] << "\n";

            // Check for bird
            /*
            *   If statement which checks the predicted labels of the object classified
            *   to see if they are equal to "bird" if true, this edits a boolean variable
            *   'tweet' to be true.
            */
            
            if(Labels[det_index] == "bird") 
            {
                tweet = true; /*!< tweet boolean is used as a check to execute code that posts picture to Twitter. */
            }
            
        }

    }

#ifdef LATENCY_DEBUG
    std::chrono::high_resolution_clock::time_point imageReadTimerStop = std::chrono::high_resolution_clock::now(); 
    imageReadDuration = std::chrono::duration <float> (imageReadTimerStop - imageReadTimerStart).count();
    fprintf(imReadDurLog, "%f\n", 1000*imageReadDuration); 
#endif

    // If tweet = true Python script to make a Tweet will be executed
  
    if(tweet)
    {
#ifdef LATENCY_DEBUG
        std::chrono::high_resolution_clock::time_point tweetTimerStart = std::chrono::high_resolution_clock::now(); 
#endif
        // Execute Python script to make Tweet
        // Code below was based on open source code found at the following link:
        // https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
        // by A. Mukhopadhyay
        
        // Set file path for Twitter script
        char pythonFile[] = "../../drivers/twitter_upload.py";
        FILE* fp;

        Py_Initialize();
        // Open the file
        fp = _Py_fopen(pythonFile, "r");
        // Execute the file
        PyRun_SimpleFile(fp, pythonFile);

        Py_Finalize();

#ifdef LATENCY_DEBUG
        std::chrono::high_resolution_clock::time_point tweetTimerStop = std::chrono::high_resolution_clock::now(); 
        tweetDuration = std::chrono::duration<float> (tweetTimerStop - tweetTimerStart).count();
        printf("TweetTime: %f\n", 1000*tweetDuration);  
        std::cout << "Tweet Timer: " << tweetDuration << "s" << std::endl;
#endif
    }
}

void Ultrasonic::run(Ultrasonic* ultrasonic)
{
    ultrasonic->running = 1;
    ultrasonic->visitCount = 0;

    while(ultrasonic->running) 
    {  
        // Send visit count to web page via UDP packet
        UDPTransmit sendPacket(ultrasonic->visitCount);
        switch(ultrasonic->newStimulus)
        {
            case 1:
            {
#ifdef LATENCY_DEBUG
                std::chrono::high_resolution_clock::time_point USTimerStart = std::chrono::high_resolution_clock::now();
#endif

                if(ultrasonic->measureDistance() <= 0.3 && ultrasonic->measureDistance() <= 0.3 && ultrasonic->measureDistance() <= 0.3) //3 quick checks to lower error chance
                { 
                    ultrasonic->newStimulus = false;
                    // Update visit count
                    ultrasonic->visitCount++;

#ifdef LATENCY_DEBUG
                    std::chrono::high_resolution_clock::time_point USTimerStop = std::chrono::high_resolution_clock::now(); 
                    USDuration = std::chrono::duration <float> (USTimerStop - USTimerStart).count();
                    fprintf(usDurLog, "%f\n", 1000*USDuration); 
#endif 
                    ultrasonic->takePhoto();
                            
                    /*
                    *  Input the image to be classified as imread("directory/name"). If there is no image
                    *  an error will be sent out to the console.
                    */  
                    Mat frame = imread("../../Photos/birdcafe.jpg");
                    
#ifdef LATENCY_DEBUG
                    std::cout << "image read Timer: " << imageReadDuration << "s" << std::endl;
#endif
                    if (frame.empty()) 
                    {
                        cerr << "Can not load picture!" << endl;
                        exit(-1); 
                    }
                        
                    /*
                    *  The function detect_from_picture() will pass the image to be classified
                    *  to the SSD object detection function. From this the the labels and detection
                    *  scores are posted to console.
                    */ 
                    ultrasonic->detect_from_picture(frame);
                }
            }
            break;

            case 0:
            {
                if(ultrasonic->measureDistance() > 0.3 && ultrasonic->measureDistance() > 0.3 && ultrasonic->measureDistance() > 0.3)

                {
                    ultrasonic->newStimulus = true;
                }
            }
            
            
        }
    }
}
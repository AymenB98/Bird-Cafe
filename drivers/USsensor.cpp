//!**************************************************************
//! \file
//! \brief Defines Ultrasonic subclass
//!**************************************************************

#include "USsensor.h"
#include "UDP.h"

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
   
   std::chrono::steady_clock::time_point loopStart = std::chrono::steady_clock::now(); 
   bool timeout = 0;
    while (digitalRead(echo) == LOW && timeout == 0)
    {
        if((std::chrono::duration<float>(std::chrono::steady_clock::now()-loopStart).count()) >5) //throws error if stuck in loop
        {
            timeout = 1; //Prevents getting stuck in loop if hardware fault - will result in a very short distance being measured
            std::cerr << "Echo pin stuck low" <<std::endl;
            
        }
    }
    std::chrono::steady_clock::time_point timerStart = std::chrono::steady_clock::now(); //start timer
    while (digitalRead(echo) == HIGH)
    {
       if((std::chrono::duration<float>(std::chrono::steady_clock::now()-timerStart).count()) >5) //throws error if stuck in loop
        {
            timeout = 1; //Prevents getting stuck in loop if hardware fault - will result in a very long distance being measured
            std::cerr << "Echo pin stuck high" <<std::endl;
        }
    }
    std::chrono::steady_clock::time_point timerStop = std::chrono::steady_clock::now();  //stop timer
    

    float pulseDur = std::chrono::duration<float>(timerStop-timerStart).count(); //force timer to float
    float distance = distanceCalcUS(pulseDur);

    if (distance < 0.3)
    {
        std::cout << distance << std::endl;
    }
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

    
    // Introduction of a clock
    /* 
     *  Introduces a clock which will be able to mark the start point Tbegin
     *  and the end point Tend. This is used to calculate the total time to
     *  classify an image and passing the outputs.
     */
    chrono::steady_clock::time_point Tbegin, Tend; 

    // Timer start variable
    /* 
     * Tbegin is the start point for the internal timer.
     */
    Tbegin = chrono::steady_clock::now();

    // Load model
    
    auto model = tflite::FlatBufferModel::BuildFromFile("/home/pi/projects/BirdCafe/Bird-Cafe/drivers/detect.tflite");
    //std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile("detect.tflite");
    
    // Build the interpreter
    
    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);

    interpreter->AllocateTensors();

	// Get the names
   
	bool result = getFileContent("/home/pi/projects/BirdCafe/Bird-Cafe/drivers/COCO_labels.txt");
	if(!result)
	{
        cout << "loading labels failed";
        exit(-1);
	}

    // copy image to input as input tensor
    cv::resize(src, image, Size(width,height));
    memcpy(interpreter->typed_input_tensor<uchar>(0), image.data, image.total() * image.elemSize());

    interpreter->SetAllowFp16PrecisionForFp32(true);
  
    interpreter->SetNumThreads(4);      //quad core

    interpreter->Invoke();      // run your model

    const float* detection_locations = interpreter->tensor(interpreter->outputs()[0])->data.f;
    const float* detection_classes=interpreter->tensor(interpreter->outputs()[1])->data.f;
    const float* detection_scores = interpreter->tensor(interpreter->outputs()[2])->data.f;
    const int    num_detections = *interpreter->tensor(interpreter->outputs()[3])->data.f;
   
    //there are ALWAYS 10 detections no matter how many objects are detectable
    //cout << "number of detections: " << num_detections << "\n";

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
                cout << "bird detected \n";
                tweet = true; /*!< tweet boolean is used as a check to execute code that posts picture to Twitter. */
            }
            
        }

    }

    // Process if tweet = true
    /*
    *   If tweet = true Python script to make a Tweet will be executed
    */
    if(tweet)
    {
        std::chrono::steady_clock::time_point tweetTimerStart = std::chrono::steady_clock::now(); 
        // Execute Python script to make Tweet
        system("python ../twitter_upload.py");
        std::chrono::steady_clock::time_point tweetTimerStop = std::chrono::steady_clock::now(); 
        auto tweetDuration = std::chrono::duration_cast <std::chrono::milliseconds> (tweetTimerStop - tweetTimerStart).count();
        std::cout << "Tweet Timer: " << tweetDuration << "ms" << std::endl;
    }

    // Timer end variable
    /* 
     *  Tend is the end point for the internal timer.
     */
    Tend = chrono::steady_clock::now();

    // Latency for bird classfication
    /* 
     *  f is used to calculate the time difference between Tend and Tbegin.
     *  The time is calculated in milliseconds.
     */
    f = chrono::duration_cast <chrono::milliseconds> (Tend - Tbegin).count();
    
    // Output to terminal
    /*
     *  This is a simple output to the command line which shows how long
     *  the total time from start of the classfication process until the end.
     */
    cout << "Process time: " << f << " mSec" << endl;

}

void Ultrasonic::run(Ultrasonic* ultrasonic)
{
    ultrasonic->running = 1;
    ultrasonic->visitCount = 0;

    while (ultrasonic->running) 
    {   
        std::chrono::steady_clock::time_point USTimerStart = std::chrono::steady_clock::now();
        if(ultrasonic->measureDistance() < 0.3)
        {
            if(ultrasonic->measureDistance() < 0.3)
            {
                if(ultrasonic->measureDistance() < 0.3) //3 quick checks to lower error chance
                { 

                    ultrasonic->visitCount++;
                    UDPTransmit sendPacket(ultrasonic->visitCount);
                    

                    std::chrono::steady_clock::time_point USTimerStop = std::chrono::steady_clock::now(); 
                    auto USDuration = std::chrono::duration_cast <std::chrono::milliseconds> (USTimerStop - USTimerStart).count();
                    std::cout << "Ultrasonic Timer: " << USDuration << "ms" << std::endl;
                    ultrasonic->takePhoto();
                    
                    /*
                    *  Input the image to be classified as imread("directory/name"). If there is no image
                    *  an error will be sent out to the console.
                    */  
                        std::chrono::steady_clock::time_point imageReadTimerStart = std::chrono::steady_clock::now(); 
                        Mat frame = imread("/home/pi/projects/BirdCafe/Bird-Cafe/Photos/birdcafe.jpg");
                        std::chrono::steady_clock::time_point imageReadTimerStop = std::chrono::steady_clock::now(); 
                        auto imageReadDuration = std::chrono::duration_cast <std::chrono::milliseconds> (imageReadTimerStop - imageReadTimerStart).count();
                        std::cout << "image read Timer: " << imageReadDuration << "ms" << std::endl;
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
                    // std::this_thread::sleep_for(std::chrono::seconds(30));
                }
            }  
        }
    }
}
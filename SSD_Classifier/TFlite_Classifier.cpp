#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>
#include <opencv2/core/ocl.hpp>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/lite/examples/label_image/get_top_n.h"
#include "tensorflow/lite/model.h"
#include <cmath>
#include <cstdlib>
#include "/home/pi/projects/BirdCafe/Bird-Cafe/udp/UdpTx/udp_tx.h"

//Jonathan Roarty GUID: 2254735

//This code has been adapted by code made by Q-Engineering
//Permission was obtained to utilise the reposiory
//Further info can be found on the Classifer-Readme.txt
using namespace cv;
using namespace std;

const size_t width = 300;
const size_t height = 300;

std::vector<std::string> Labels;
std::unique_ptr<tflite::Interpreter> interpreter;

static bool getFileContent(std::string fileName)
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

void detect_from_picture(Mat &src)
{
    Mat image;
    int cam_width =src.cols;
    int cam_height=src.rows;

    // copy image to input as input tensor
    cv::resize(src, image, Size(width,height));
    memcpy(interpreter->typed_input_tensor<uchar>(0), image.data, image.total() * image.elemSize());

    interpreter->SetAllowFp16PrecisionForFp32(true);
    interpreter->SetNumThreads(4);      //quad core

        //cout << "tensors size: " << interpreter->tensors_size() << "\n";
        //cout << "nodes size: " << interpreter->nodes_size() << "\n";
        //cout << "inputs: " << interpreter->inputs().size() << "\n";
        //cout << "input(0) name: " << interpreter->GetInputName(0) << "\n";
        //cout << "outputs: " << interpreter->outputs().size() << "\n";

    interpreter->Invoke();      // run your model

    const float* detection_locations = interpreter->tensor(interpreter->outputs()[0])->data.f;
    const float* detection_classes=interpreter->tensor(interpreter->outputs()[1])->data.f;
    const float* detection_scores = interpreter->tensor(interpreter->outputs()[2])->data.f;
    const int    num_detections = *interpreter->tensor(interpreter->outputs()[3])->data.f;

    //there are ALWAYS 10 detections no matter how many objects are detectable
    //cout << "number of detections: " << num_detections << "\n";

    const float confidence_threshold = 0.5;
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
            
            /**  
             *  This is used to output the detection scores from the confidence_threshold
             *  to a max of 1 alongside it's corresponding label for each of the objects
             *  detected in the image provided.
             */
            cout << detection_scores[i] << " : " << Labels[det_index] << "\n";

            if(Labels[det_index] == "bird") {

                cout << "bird detected \n";
                tweet = true;

            }
            

        }
    }

    if(tweet){
        // Create new instance of class which transmits UDP packet
        UDPTransmit updatePacket;
        // Tell web page that 5 birds have visited today    
        updatePacket.sendPacket(1);
        // Execute Python script to make Tweet
        system("python /home/pi/projects/Python_twitter/twitter_upload.py");
    }
}

int main(int argc,char ** argv)
{
    float f;
    float FPS[16];
    int i;
    int Fcnt=0;
    Mat frame;
    Mat image;
    string name;

    /** 
     *  Introduces a clock which will be able to mark the start point Tbegin
     *  and the end point Tend. This is used to calculate the total time to
     *  classify an image and passing the outputs.
     */ 
    chrono::steady_clock::time_point Tbegin, Tend;

    /** 
     * Tbegin is the start point for the internal timer.
     */
    Tbegin = chrono::steady_clock::now();

    // Load model
    std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile("detect.tflite");

    // Build the interpreter
    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);

    interpreter->AllocateTensors();

	// Get the names
	bool result = getFileContent("COCO_labels.txt");
	if(!result)
	{
        cout << "loading labels failed";
        exit(-1);
	}

    /**
     *  Input the image to be classified as imread("directory/name"). If there is no image
     *  an error will be sent out to the console.
     */
    frame = imread("Bird_1.PNG");
    if (frame.empty()) {
        cerr << "Can not load picture!" << endl;
        exit(-1);
    }

    /**
     *  The function detect_from_picture() will pass the image to be classified
     *  to the SSD object detection function. From this the the labels and detection
     *  scores are posted to console.
     */
    detect_from_picture(frame);

    /** 
     *  Tend is the end point for the internal timer.
     */
    Tend = chrono::steady_clock::now();

    /** 
     *  f is used to calculate the time difference between Tend and Tbegin.
     *  The time is calculated in milliseconds.
     */
    f = chrono::duration_cast <chrono::milliseconds> (Tend - Tbegin).count();
    
    /**
     *  This is a simple output to the command line which shows how long
     *  the total time from start of the classfication process until the end.
     */
    cout << "Process time: " << f << " mSec" << endl;

    /** 
     *  imshow is used here to display the image that was inputted with boxes and labels
     *  drawn around the detected objects in the image.
     */
    imshow("Classfication Result", frame);
    
    /** 
     *  A name is generated which will be assigned to the the classified image with
     *  boxes and labels on the detected objects when it is saved.
     */
    name = ("Class_output" + std::to_string(1) + ".jpg");
    
    /** 
     *  imwrite is used to save the classified image with boxes and labels along
     *  with the name generated. The image will be saved to the directory local 
     *  to the executable.
     */
    imwrite(name, frame);

    return 0;
}

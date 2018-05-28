#include "view_frame.h"
#include "capture_frame.h"
#include <stdio.h>
#include <opencv2/dnn.hpp>
#include <string.h>
#include <opencv2/opencv.hpp>
#include "crack_detection.h"

void CrackDetection::initialize_network(std::string caffe_model, std::string config)
{
    cv::Ptr<cv::dnn::Importer> importer;
    try                                     //Try to import Caffe GoogleNet model
    {
        importer = cv::dnn::createCaffeImporter(config, caffe_model);
    }
    catch (const cv::Exception &err)        //Importer can throw errors, we will catch them
    {
        std::cerr << err.msg << std::endl;
    }
    if (!importer)
    {
        std::cerr << "Can't load network by using the following files: " << std::endl;
        std::cerr << "prototxt:   " << config << std::endl;
        std::cerr << "caffemodel: " << caffe_model << std::endl;
        exit(-1);
    }

    importer->populateNet(network);
    importer.release();  

    return;

}

bool CrackDetection::detect_crack(CaptureFrame input)
{
    cv::Mat image = input.retrieve_image().clone();
    cv::Scalar mean = cv::Scalar(159.396,168.509,173.733);//This data will be available in imagenet_mean.binary.prototext created according to the training data
    cv::Mat blob;
    cv::resize(image,image,cv::Size(227,227));
    cv::imshow("testing",image);
    std::cout<< image.rows<<"  "<<image.cols<<"\n";
    blob = cv::dnn::blobFromImage(image,1,image.size(),mean,false,false);

    network.setInput(blob);
   
    cv::Mat prob = network.forward();

    cv::Point classIdPoint;

    double confidence;
    

    cv::minMaxLoc(prob.reshape(1,1),0,&confidence,&classIdPoint);
    
    int result = classIdPoint.x;
    std::cout<<"Prediction = "<<result<<"   Confidence = "<<confidence<<"\n";
    cv::waitKey(0);
    if(result == 0) return true;
    else return false;

}

// void CrackDetection::divide_image(CaptureFrame input, int dest_row, int dest_col)
// {
//     cv::Mat image = input.retrieve_image().clone();
//     divided_images.clear();


// }
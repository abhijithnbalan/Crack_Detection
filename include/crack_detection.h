
#ifndef _crack_detection_h
#define _crack_detection_h

#include <opencv2/opencv.hpp> 
#include "opencv2/imgproc/imgproc.hpp"
#include <string.h>
#include <opencv2/dnn.hpp>
#include "logger.h"
#include "capture_frame.h"
#include "image_processing.h"

// using namespace cv;
// using namespace cv::dnn;
// using namespace std;

class CrackDetection : public ImageProcessing
{
    private:
        cv::dnn::Net network; Logger logger;
        std::vector<cv::Mat> divided_images;

    protected:

    public:

        CaptureFrame pre_processing(CaptureFrame input, int mode);
        bool detect_crack(CaptureFrame input);
        CaptureFrame output_overlay(CaptureFrame input);
        void initialize_network(std::string caffe_model, std::string config);
        // void divide_image(CaptureFrame image,int dest_row,int dest_col);
};



#endif

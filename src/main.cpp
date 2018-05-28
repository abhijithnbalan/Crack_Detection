//Standard inlcludes
#include <unistd.h>
#include <string.h>
#include <sstream>

//User defined includes
#include "capture_frame.h"
#include "view_frame.h"
#include "crack_detection.h"
#include "logger.h"


int main(int argc, char **argv) //The main Function.
{
    
    int success = chdir("..");
    Logger logger;
    logger.log_info("Crack Detection starts");
    logger.log_debug("Working directory switched to one directory back");

    if(success != 0)
    {
        logger.log_error("Unable to change working directory");
        std::cout<<"couldn't change the directory/\n";
        return -1;    
    }

    CrackDetection crack_det;
    CaptureFrame input_image;
    input_image.capture_image(argv[1],"input");
    logger.log_debug("Image_Loaded");
    
    std::string caffe_model,config_file;

    if(argc >=3)
    {
        caffe_model = argv[2];
        config_file = argv[3];
    }
    else
    {
        caffe_model = "Model/trained_model.caffemodel";
        config_file = "Model/model.prototxt";
    }

    crack_det.initialize_network(caffe_model , config_file);
    logger.log_warn("Network Loaded Successfully");
    bool result = crack_det.detect_crack(input_image);

    if(result)
    {
        std::cout<<"Alert !! crack identified\n";

    }



return 1;

}



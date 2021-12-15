#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

// Globals
namespace g
{
    const std::string filename = samples::findFile("lena.jpg");

    struct Images { Mat input, output; };
    Images image;
};

int main()
{
    std::cout << "How to use the OpenCV parallel_for_ to parallelize your code (OpenCV: " << CV_VERSION  << ")" << std::endl;
    
    g::image.input = imread(g::filename);

    if (g::image.input.empty())
    {
        std::cout << "Could not read image " << g::filename << std::endl;
        return EXIT_FAILURE;
    }
    
    imshow("input image", g::image.input);
    waitKey(0);

    return EXIT_SUCCESS;
}
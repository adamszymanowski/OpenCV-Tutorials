#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

int main()
{
    std::cout << "Getting Started with Images (OpenCV: " << CV_VERSION  << ")" << std::endl;
    
    samples::addSamplesDataSearchPath("/home/adam/opencv/samples/data");
    std::string image_path = samples::findFile("starry_night.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);

    if (img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window

    if (k == 's')
    {
        imwrite("starry_night.png", img);
    }
    
    return 0;
}
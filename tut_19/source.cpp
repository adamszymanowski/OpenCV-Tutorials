#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

cv::Mat source_image, destination_image;

const char* window_name = "Threshold Demo";
const char* trackbar_threshold_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_threshold_value = "Value";

const int max_value = 255;
const int max_type = 4;
const int max_binary_value = 255;

static void threshold_demo(int, void*)
{
    int threshold_value = cv::getTrackbarPos(trackbar_threshold_value, window_name);
    int threshold_type = cv::getTrackbarPos(trackbar_threshold_type, window_name);
    cv::threshold(source_image, destination_image, threshold_value, max_binary_value, threshold_type);
    cv::imshow(window_name, destination_image);
}

int main()
{
    std::cout << "Basic Thresholding Operations (OpenCV: " << CV_VERSION  << ")" << std::endl;
    source_image = cv::imread(cv::samples::findFile("chicky_512.png"), cv::IMREAD_GRAYSCALE);

    if (source_image.empty())
    {
        std::cout << "* ERROR: Cannot open image" << std::endl;
        return EXIT_FAILURE;
    }
    cv::namedWindow(window_name);
    cv::createTrackbar(trackbar_threshold_type, window_name, nullptr, max_type, threshold_demo);
    cv::createTrackbar(trackbar_threshold_value, window_name, nullptr, max_value, threshold_demo);

    threshold_demo(0,0); // Call the function to initialize
    cv::waitKey();
}
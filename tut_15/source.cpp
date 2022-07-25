#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

void Morphology_Operations(int, void*);

const char* window_name = "Morphology Transformations Demo";
int const maximum_operator = 4;
int const maximum_element = 2;
int const maximum_kernel_size = 21;
const char* operator_trackbar = "Operator:\n 0: Opening | 1: Closing | 2: Gradient | 3: Top Hat | 4: Black Hat";
const char* element_trackbar = "Element:\n 0: Rect | 1: Cross | 2: Ellipse";
const char* kernel_size_trackbar = "Kernel Size:\n 2n+1";

cv::Mat source_image, destination_image;

int main()
{
    std::cout << "More Morphology Transformations (OpenCV: " << CV_VERSION  << ")" << std::endl;
    
    source_image = cv::imread(cv::samples::findFile("baboon.jpg"));
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    
    cv::createTrackbar(operator_trackbar, window_name, nullptr, maximum_operator, Morphology_Operations);
    cv::createTrackbar(element_trackbar,window_name, nullptr, maximum_element, Morphology_Operations);
    cv::createTrackbar(kernel_size_trackbar, window_name, nullptr, maximum_kernel_size, Morphology_Operations);

    // Default start
    Morphology_Operations(0, 0);
    
    cv::waitKey();
}

void Morphology_Operations(int, void*)
{
    int morphology_element = cv::getTrackbarPos(element_trackbar, window_name);
    int morphology_operator = cv::getTrackbarPos(operator_trackbar, window_name);
    int morphology_size = cv::getTrackbarPos(kernel_size_trackbar, window_name);
    
    int operation = morphology_operator + 2;

    cv::Mat element = cv::getStructuringElement(morphology_element, 
                                                cv::Size(2 * morphology_size + 1, 2 * morphology_size + 1),
                                                cv::Point(morphology_size, morphology_size));
    
    cv::morphologyEx(source_image, destination_image, operation, element);
    cv::imshow(window_name, destination_image);
}
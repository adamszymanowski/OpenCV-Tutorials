#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

cv::Mat source_image, erosion_image, dilation_image;
const int max_elem = 2;
const int max_kernel_size = 21;

//static void erosion(int, void*);
void erosion(int, void*);
void dilation(int, void*);

const char* source_window = "Source Image";
const char* erosion_window = "Erosion Image";    
const char* dilation_window = "Dilation Image";

const char* erosion_elem_trackbar = "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse";
const char* erosion_size_trackbar = "Kernel size:\n 2n+1";

const char* dilation_size_trackbar = "Kernel size:\n 2n+1";
const char* dilation_elem_trackbar = "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse";

int main()
{
    std::cout << "Eroding and Dilating (OpenCV: " << CV_VERSION  << ")" << std::endl;

    std::string filename = cv::samples::findFile("LinuxLogo.jpg");
    source_image = cv::imread(filename);
    if (source_image.empty())
    {
        std::cout << "* ERROR: empty image: " << filename << std::endl;
        return EXIT_FAILURE;
    }

    cv::namedWindow(erosion_window);
    cv::createTrackbar(erosion_elem_trackbar, erosion_window, nullptr, max_elem, erosion);
    cv::createTrackbar(erosion_size_trackbar, erosion_window, nullptr, max_kernel_size, erosion);

    cv::namedWindow(dilation_window);
    cv::createTrackbar(dilation_elem_trackbar, dilation_window, nullptr, max_elem, dilation);
    cv::createTrackbar(dilation_size_trackbar, dilation_window, nullptr, max_kernel_size, dilation);

    // default start
    erosion(0, 0);
    dilation(0, 0);

    cv::imshow(source_window, source_image);
    cv::moveWindow(source_window, 0, 0); 

    cv::waitKey();

    return EXIT_SUCCESS;
}

void erosion(int, void*)
{
    int erosion_elem = cv::getTrackbarPos(erosion_elem_trackbar, erosion_window);
    int erosion_type;
    if (erosion_elem == 0) { erosion_type = cv::MORPH_RECT; }
    if (erosion_elem == 1) { erosion_type = cv::MORPH_CROSS; }
    if (erosion_elem == 2) { erosion_type = cv::MORPH_ELLIPSE; }

    int erosion_size = cv::getTrackbarPos(erosion_size_trackbar, erosion_window);

    cv::Mat element = cv::getStructuringElement(
        erosion_type, 
        cv::Size(2*erosion_size + 1, 2*erosion_size +1), 
        cv::Point(erosion_size, erosion_size)
    );
    cv::erode(source_image, erosion_image, element);
    
    cv::imshow(erosion_window, erosion_image);
    cv::moveWindow(erosion_window, source_image.cols*1.2, 0);
}  

void dilation(int, void*)
{
    int dilation_elem = cv::getTrackbarPos(dilation_elem_trackbar, dilation_window);
    int dilation_type;
    if (dilation_elem == 0) { dilation_type = cv::MORPH_RECT; }
    if (dilation_elem == 1) { dilation_type = cv::MORPH_CROSS; }
    if (dilation_elem == 2) { dilation_type = cv::MORPH_ELLIPSE; }

    int dilation_size = cv::getTrackbarPos(dilation_size_trackbar, dilation_window);

    cv::Mat element = cv::getStructuringElement(
        dilation_type, 
        cv::Size(2*dilation_size + 1, 2*dilation_size +1), 
        cv::Point(dilation_size, dilation_size)
    );
    cv::dilate(source_image, dilation_image, element);

    cv::imshow(dilation_window, dilation_image);
    cv::moveWindow(dilation_window, source_image.cols*2.4, 0);
}
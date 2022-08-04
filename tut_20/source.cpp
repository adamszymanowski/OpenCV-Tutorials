#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>

// Windows
const char* window_capture = "Video Capture";
const char* window_threshold = "Threshold";
// Trackbars
const char* trackbar_low_H = "Low H";
const char* trackbar_high_H = "High H";
const char* trackbar_low_S = "Low S";
const char* trackbar_high_S = "High S";
const char* trackbar_low_V = "Low V";
const char* trackbar_high_V = "High V";
// Values
const int max_H = 179;
const int max_S = 255;
const int max_V = 255;
int high_H = max_H, high_S = max_S, high_V = max_V;
int low_H = 0, low_S = 0, low_V = 0;
// Callbacks declarations
void callback_high_H(int, void *);
void callback_low_H(int, void *);
void callback_high_S(int, void *);
void callback_low_S(int, void *);
void callback_high_V(int, void *);
void callback_low_V(int, void *);


int main()
{
    std::cout << "Thresholding Operations using inRange (OpenCV: " << CV_VERSION  << ")" << std::endl;
    // Window setup
    cv::namedWindow(window_capture);
    cv::namedWindow(window_threshold);
    // Trackbar setup
    cv::createTrackbar(trackbar_high_H, window_threshold, nullptr, max_H, callback_high_H);
    cv::createTrackbar(trackbar_low_H, window_threshold, nullptr, max_H, callback_low_H);
    cv::createTrackbar(trackbar_high_S, window_threshold, nullptr, max_S, callback_high_S);
    cv::createTrackbar(trackbar_low_S, window_threshold, nullptr, max_S, callback_low_S);
    cv::createTrackbar(trackbar_high_V, window_threshold, nullptr, max_V, callback_high_V);
    cv::createTrackbar(trackbar_low_V, window_threshold, nullptr, max_V, callback_low_V);
    // Capture and image setup
    cv::Mat frame, frame_HSV, frame_threshold;
    cv::VideoCapture camera{0};

    if (camera.isOpened())
    {
        std::cout << "* SUCCESS: camera initialized" << std::endl;
    }
    else
    {
        std::cout << "* ERROR: camera NOT initialized" << std::endl;
        return EXIT_FAILURE;
    }

    for (;;)
    {
        camera.read(frame);
        if (frame.empty())
        {
            std::cout << "* ERROR: Could NOT read frame!" << std::endl;
            break;
        }
        cv::cvtColor(frame, frame_HSV, cv::COLOR_BGR2HSV);
        cv::inRange(frame_HSV, cv::Scalar(low_H, low_S, low_V), cv::Scalar(high_H, high_S, high_V), frame_threshold);

        cv::imshow(window_capture, frame);
        cv::imshow(window_threshold, frame_threshold);

        char key = (char)cv::waitKey(30);
        if (key == 'q' or key == 27)
        {
            std::cout << "* INFO: quitting..." << std::endl;
            break;
        }
    }
    std::cout << "Application END" << std::endl;
}

void callback_high_H(int, void *)
{
    high_H = cv::getTrackbarPos(trackbar_high_H, window_threshold);
    high_H = cv::max(high_H, low_H+1);
    cv::setTrackbarPos(trackbar_high_H, window_threshold, high_H);
}

void callback_low_H(int, void *)
{
    low_H = cv::getTrackbarPos(trackbar_low_H, window_threshold);
    low_H = cv::min(high_H-1, low_H);
    cv::setTrackbarPos(trackbar_low_H, window_threshold, low_H);
}

void callback_high_S(int, void *)
{
    high_S = cv::getTrackbarPos(trackbar_high_S, window_threshold);
    high_S = cv::max(high_S, low_S+1);
    cv::setTrackbarPos(trackbar_high_S, window_threshold, high_S);
}

void callback_low_S(int, void *)
{
    low_S = cv::getTrackbarPos(trackbar_low_S, window_threshold);
    low_S = cv::min(high_S-1, low_S);
    cv::setTrackbarPos(trackbar_low_S, window_threshold, low_S);
}

void callback_high_V(int, void *)
{
    high_V = cv::getTrackbarPos(trackbar_high_V, window_threshold);
    high_V = cv::max(high_V, low_V+1);
    cv::setTrackbarPos(trackbar_high_V, window_threshold, high_V);
}

void callback_low_V(int, void *)
{
    low_V = cv::getTrackbarPos(trackbar_low_V, window_threshold);
    low_V = cv::min(high_V-1, low_V);
    cv::setTrackbarPos(trackbar_low_V, window_threshold, low_V);
}
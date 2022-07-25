#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

int main()
{
    std::cout << "Hit-or-Miss (OpenCV: " << CV_VERSION  << ")" << std::endl;


    cv::Mat input_image = (cv::Mat_<int>(8, 8) <<
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 0, 0, 0, 1,
        0, 1, 1, 1, 0, 0, 0, 0,
        0, 1, 1, 1, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 1, 0, 1, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0, 0, 0);  
    
    input_image *= 255;
    input_image.convertTo(input_image, CV_8U);

    cv::Mat kernel = (cv::Mat_<int>(3, 3) <<
        0, 1, 0,
        1, -1, 1,
        0, 1, 0);

    cv::Mat output_image;
    cv::morphologyEx(input_image, output_image, cv::MORPH_HITMISS, kernel);

    kernel = (kernel + 1) * 127;
    kernel.convertTo(kernel, CV_8U);

    const int rate = 50;
    cv::resize(input_image, input_image, cv::Size(), rate, rate, cv::INTER_NEAREST);
    cv::resize(kernel, kernel, cv::Size(), rate, rate, cv::INTER_NEAREST);
    cv::resize(output_image, output_image, cv::Size(), rate, rate, cv::INTER_NEAREST);

    cv::imshow("Kernel", kernel);
    cv::moveWindow("Kernel", 0, 0);    
    cv::imshow("Original", input_image);
    cv::moveWindow("Original", 0, 210);
    cv::imshow("Hit or Miss", output_image);
    cv::moveWindow("Hit or Miss", 500, 210);


    cv::waitKey();
}
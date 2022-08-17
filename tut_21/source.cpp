#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

int main()
{
    std::cout << "Making Your Own Linear Filters! (OpenCV: " << CV_VERSION  << ")" << std::endl;
    
    cv::Mat destination_image;
    cv::Mat source_image = cv::imread(cv::samples::findFile("butterfly.jpg"), cv::IMREAD_COLOR);
    if (source_image.empty())
    {
        std::cout << "* ERROR: empty image." << std::endl;
        return EXIT_FAILURE;
    }

    // Initialize arguments for the filter
    auto anchor = cv::Point(-1,-1);
    double delta = 0.0;
    int ddepth = -1;

    for (int index = 0; index <= 5; ++index)
    {
        // Update kernel
        int kernel_size = 3 + 2 * index;
        cv::Mat kernel = cv::Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size); // Divide to normalize

        // Apply filter
        cv::filter2D(source_image, destination_image, ddepth, kernel, anchor, delta, cv::BORDER_DEFAULT);
        cv::putText(destination_image, "kernel size: " + std::to_string(kernel_size), 
                    cv::Point(260, 340), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255, 0, 255), 2);
        imshow("Normalized Box Filter", destination_image);

        char ch = (char)cv::waitKey(750);
        if (ch == 27) { break; }
    }

    cv::waitKey();
}
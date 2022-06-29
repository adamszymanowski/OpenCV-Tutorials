#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>

const int delay_caption = 1500;
const int delay_blur = 150;
const int max_kernel_length = 31;
const char* window_name = "Smoothing Demo";

int display_caption(const char* caption);
int display_destination_image(int delay);
cv::Mat source_image, destination_image, 
homogenous_image, gaussian_image, median_image, bilateral_image;

int main()
{
    std::cout << "Smoothing Images (OpenCV: " << CV_VERSION  << ")" << std::endl;

    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    
    const std::string filename = cv::samples::findFile("lena.jpg");
    source_image = cv::imread(filename);
    if (source_image.empty())
    {
        std::cout << "* ERROR: Empty image " << filename << std::endl;
        return EXIT_FAILURE;
    }

    if (display_caption("Original Image"))  
        return 0;

    destination_image = source_image.clone();
    if (display_destination_image(delay_caption))
        return 0;


    if (display_caption("Homogenous Blur"))
        return 0;

    destination_image = source_image.clone();
    for (int i = 1; i < max_kernel_length; i = i + 2)
    {
        cv::blur(source_image, destination_image, cv::Size(i, i), cv::Point(-1, -1));
        if (display_destination_image(delay_blur))
            return 0;
    }
    homogenous_image = destination_image.clone();


    if (display_caption("Gaussian Blur"))
        return 0;

    destination_image = source_image.clone();
    for (int i = 1; i < max_kernel_length; i = i + 2)
    {
        cv::GaussianBlur(source_image, destination_image, cv::Size(i, i), 0, 0);
        if (display_destination_image(delay_blur))
            return 0;
    }
    gaussian_image = destination_image.clone();


    if (display_caption("Median Blur"))
        return 0;

    destination_image = source_image.clone();
    for (int i = 1; i < max_kernel_length; i = i + 2)
    {
        cv::medianBlur(source_image, destination_image, i);
        if (display_destination_image(delay_blur))
            return 0;
    }
    median_image = destination_image.clone();

    if (display_caption("Bilateral Blur"))
        return 0;

    destination_image = source_image.clone();
    for (int i = 1; i < max_kernel_length; i = i + 2)
    {
        cv::bilateralFilter(source_image, destination_image, i, i*2, i/2);
        if (display_destination_image(delay_blur))
            return 0;
    }
    bilateral_image = destination_image.clone();
    cv::destroyWindow(window_name);

    // Final showcase comparison
    const int off = 24;
    const char* original_image_window = "Original Image";
    cv::imshow(original_image_window, source_image);
    cv::moveWindow(original_image_window, 0, 0);

    const char* homogenous_blur_window = "Homogenous Blur";
    cv::imshow(homogenous_blur_window, homogenous_image);
    cv::moveWindow(homogenous_blur_window, 0, source_image.rows+off);

    const char* gaussian_blur_window = "Gaussian Blur";
    cv::imshow(gaussian_blur_window, gaussian_image);
    cv::moveWindow(gaussian_blur_window, source_image.cols+off, source_image.rows+off);

    const char* median_blur_window = "Median Blur";
    cv::imshow(median_blur_window, median_image);
    cv::moveWindow(median_blur_window, source_image.cols*2+off, source_image.rows+off);

    const char* bilateral_blur_window = "Bilateral Blur";
    cv::imshow(bilateral_blur_window, bilateral_image);
    cv::moveWindow(bilateral_blur_window, source_image.cols*3+off, source_image.rows+off);

    std::cout << "cols " << source_image.cols << "rows " << source_image.rows << std::endl;
    cv::waitKey();
    return EXIT_SUCCESS;
}

int display_caption(const char* caption)
{
    destination_image = cv::Mat::zeros(source_image.size(), source_image.type());
    cv::putText(
        destination_image, caption,
        cv::Point((source_image.cols / 4), (source_image.rows / 2)),
        cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255)
    );
    return display_destination_image(delay_caption);
}

int display_destination_image(int delay)
{
    cv::imshow(window_name, destination_image);
    return (cv::waitKey(delay) != -1);
}
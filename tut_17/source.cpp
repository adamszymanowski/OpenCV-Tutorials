#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

void show_wait_destroy(const char* window_name, cv::Mat image);

int main()
{
    std::cout << "Extract horizontal and vertical lines by using morphological operations (OpenCV: " << CV_VERSION  << ")" << std::endl;
    cv::Mat source_image = cv::imread(cv::samples::findFile("notes.png"), cv::IMREAD_GRAYSCALE);

    cv::imshow("Source Image", source_image);
    cv::moveWindow("Source Image", 0, 0);

    cv::Mat grayscale_image = source_image.clone();

    cv::Mat binary_image;
    // Apply adaptiveThreshold at bitwise_not of grayscale_image (notice ~ symbol)
    cv::adaptiveThreshold(~grayscale_image, binary_image, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 15, -2);
    show_wait_destroy("Binary Image", binary_image);

    cv::Mat horizontal_lines_image = binary_image.clone();
    cv::Mat vertical_lines_image = binary_image.clone();

    int horizontal_size = horizontal_lines_image.cols / 30;
    cv::Mat horizontal_structure = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(horizontal_size, 1));

    cv::erode(horizontal_lines_image, horizontal_lines_image, horizontal_structure, cv::Point(-1, -1));
    cv::dilate(horizontal_lines_image, horizontal_lines_image, horizontal_structure, cv::Point(-1, -1));
    show_wait_destroy("Horizontal lines", horizontal_lines_image);

    int vertical_size = vertical_lines_image.rows / 30;
    cv::Mat vertical_structure = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, vertical_size));

    cv::erode(vertical_lines_image, vertical_lines_image, vertical_structure, cv::Point(-1, -1));
    cv::dilate(vertical_lines_image, vertical_lines_image, vertical_structure, cv::Point(-1, -1));
    show_wait_destroy("Vertical lines", vertical_lines_image);

    cv::bitwise_not(vertical_lines_image, vertical_lines_image);
    show_wait_destroy("Vertical lines inverted", vertical_lines_image);

    // Extract edges and smooth image
    // 1. extract edges
    // 2. dilate(edges)
    // 3. vertical_lines.copyTo(smooth)
    // 4. blur smooth image
    // 5. smooth.copyTo(vertical_lines, edges)

    // Step 1
    cv::Mat edges_image;
    cv::adaptiveThreshold(vertical_lines_image, edges_image, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 3, -2);
    show_wait_destroy("Edges Image", edges_image);
    // Step 2
    cv::Mat kernel = cv::Mat::ones(2, 2, CV_8UC1);
    cv::dilate(edges_image, edges_image, kernel);
    show_wait_destroy("Dilated edges", edges_image);
    // Step 3
    cv::Mat smooth_image;
    vertical_lines_image.copyTo(smooth_image);
    // Step 4
    cv::blur(smooth_image, smooth_image, cv::Size(2,2));
    // Step 5
    smooth_image.copyTo(vertical_lines_image, edges_image);
    show_wait_destroy("Smooth Image (final)", vertical_lines_image);
}

void show_wait_destroy(const char* window_name, cv::Mat image)
{
    cv::imshow(window_name, image);
    cv::moveWindow(window_name, 0, 200);
    cv::waitKey(0);
    cv::destroyWindow(window_name);
}
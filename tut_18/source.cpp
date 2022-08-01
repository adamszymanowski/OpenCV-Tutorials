#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

int main()
{
    std::cout << "Image Pyramids (OpenCV: " << CV_VERSION  << ")" << std::endl;
    std::cout << "Keyboard controls:" << std::endl;
    std::cout << "[i] -> zoom in \n"
                 "[o] -> zoom out \n"
                 "[ESC] -> quit" << std::endl;

    cv::Mat source_image = cv::imread(cv::samples::findFile("chicky_512.png"));

    if (source_image.empty())
    {
        std::cout << "Error opening image!" << std::endl;
        return EXIT_FAILURE;
    }

    for (;;)
    {
        imshow("Image Pyramids", source_image);
        char ch = (char)cv::waitKey(0);

        if (ch == 27) { break; }
        if (ch == 'i')
        {
            std::cout << "- Zoom in: image * 2" << std::endl;
            cv::pyrUp(source_image, source_image, cv::Size(source_image.cols * 2, source_image.rows * 2));
        }
        if (ch == 'o')
        {
            std::cout << "- Zoom out: image / 2" << std::endl;
            cv::pyrDown(source_image, source_image, cv::Size(source_image.cols / 2, source_image.rows / 2));
        }

    }

}
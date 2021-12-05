#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace cv;

void Sharpen(const Mat& input_img, Mat& output_img);

int main()
{
    double t;
    std::cout << "Mask operations on matrices (OpenCV: " << CV_VERSION  << ")" << std::endl;

    Mat original_image, sharpen_image_1, sharpen_image_2;

    std::string img_path = samples::findFile("fruits.jpg"); 
    original_image = imread(img_path, IMREAD_COLOR);

    if (original_image.empty())
    {
        std::cout << "Could not read the image: "  << img_path << std::endl;
        return EXIT_FAILURE;
    }

    // Function 1
    t = (double)getTickCount();

    Sharpen(original_image, sharpen_image_1);

    t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
    std::cout << "Handwritten funciton time passed in milliseconds: " << t << std::endl;

    // Function 2
    Mat kernel = (Mat_<char>(3,3) << 0, -1, 0,
                                    -1,  5,-1,
                                     0, -1, 0);

    t = (double)getTickCount();

    filter2D(original_image, sharpen_image_2, original_image.depth(), kernel);

    t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
    std::cout << "Built-in filter2d time passed in milliseconds: " << t << std::endl;

    // Show all images
    imshow("Original Image", original_image);
    imshow("Sharpen Image 1", sharpen_image_1);
    imshow("Sharpen Image 2", sharpen_image_2);

    waitKey(0);

    return EXIT_SUCCESS;
}

void Sharpen(const Mat& input_img, Mat& output_img)
{
    CV_Assert(input_img.depth() == CV_8U); // Accept only unsigned 8-bit images

    const int channels = input_img.channels();
    output_img.create(input_img.size(), input_img.type());

    for (int j = 1; j < input_img.rows - 1; ++j)
    {
        const uchar* previous = input_img.ptr<uchar>(j - 1);
        const uchar* current  = input_img.ptr<uchar>(j);
        const uchar* next     = input_img.ptr<uchar>(j + 1);

        uchar* output = output_img.ptr<uchar>(j);

        for (int i = channels; i < channels * (input_img.cols-1); ++i)
        {
            *output++ = saturate_cast<uchar>(
                5*current[i] - current[i - channels] - current[i + channels] - previous[i] - next[i]
            );
        }
    }

    // Since we didn't applied kernel to borders, set them to zeros instead.
    output_img.row(0).setTo(Scalar(0));
    output_img.row(output_img.rows-1).setTo(Scalar(0));
    output_img.col(0).setTo(Scalar(0));
    output_img.col(output_img.cols-1).setTo(Scalar(0));
}
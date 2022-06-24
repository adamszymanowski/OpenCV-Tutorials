#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/simd_intrinsic.hpp>

#include <iostream>



const int N = 100005, K = 2000;

namespace
{

void convolution_sequential(cv::Mat source, cv::Mat& destination, cv::Mat kernel)
{
    unsigned rows = source.rows;
    unsigned columns = source.cols;
    destination = cv::Mat(rows, columns, CV_8UC1);

    unsigned kernel_size = kernel.cols / 2;
    cv::copyMakeBorder(source, source, kernel_size, kernel_size, kernel_size, kernel_size, BORDER_REPLICATE);
    for (unsigned i = 0; i < rows; ++i)
    { 
        uchar* destination_pointer = destination.ptr<uchar>(i);
        for (unsigned j = 0; j < columns; ++j)
        {
            float value = 0;
            for (int k = -kernel_size; k <= kernel_size; ++k)
            {
                // slighlty faster results when we create a pointer due to more efficient memory access.
                uchar* source_pointer = source.ptr(i + kernel_size + k);
                for (int l = -kernel_size; l <= kernel_size; ++l)
                {
                    value += kernel.ptr<float>(k + kernel_size)[l + kernel_size] * source_pointer[j + kernel_size + i];
                }
            }
            destination_pointer[j] = saturate_cast<uchar> value;
        }
    }
}

void convolution_1d(cv::Mat source, cv::Mat destination, cv::Mat kernel)
{
    
}

void convolution_1d_smid(cv::Mat source, cv::Mat kernel, float* answer, int row = 0, int row_kernel = 0, int length = -1)
{

}

void convolute_simd(cv::Mat source, cv::Mat& destination, cv::Mat kernel)
{

}

}
int main()
{
    std::cout << "Vectorizing your code using Universal Intrinsics (OpenCV: " << CV_VERSION  << ")" << std::endl;

    return 0;
}
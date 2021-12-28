#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

// Globals
namespace g
{
    const std::string filename = samples::findFile("lena.jpg");

    struct Images { Mat input, output_1, output_2, output_3; };
    Images image;
    
    struct WindowNames { const std::string input, output_sequential; };
    WindowNames window_name {
        .input = "Input Image",
        .output_sequential = "Output Image Sequential"
    };

    Mat kernel = (Mat_<double>(3,3) <<
                    1, 0, -1,
                    1, 0, -1,
                    1, 0, -1
    );
};

namespace conv
{
    void seq(Mat source, Mat& destination, Mat kernel)
    {
        const int 
        rows = source.rows, 
        cols = source.cols,
        border = kernel.rows / 2;
        copyMakeBorder(source, source, border, border, border, border, BORDER_REPLICATE);

        destination = Mat(rows, cols, source.type());

        for (int idx_i = 0; idx_i < rows; ++idx_i)
        {
            uchar *dest_ptr = destination.ptr(idx_i);
            for (int idx_j = 0; idx_j < cols; ++idx_j)
            {
                double value = 0;
                for (int idx_k = -border; idx_k <= border; ++idx_k)
                {
                    // Slightly faster results when we create a ptr due to more efficient memory access.
                    uchar *src_ptr = source.ptr(idx_i + border + idx_k);
                    for (int idx_l =  -border; idx_l <= border; ++idx_l)
                    {
                        value += kernel.ptr<double>(idx_k + border)[idx_l + border] * src_ptr[idx_j + border + idx_l];
                    }
                }
                dest_ptr[idx_j] = saturate_cast<uchar>(value);
            }
        }
    }
// namespace end
} 

int main()
{
    std::cout << "How to use the OpenCV parallel_for_ to parallelize your code (OpenCV: " << CV_VERSION  << ")" << std::endl;
    
    g::image.input = imread(g::filename, IMREAD_GRAYSCALE);

    if (g::image.input.empty())
    {
        std::cout << "Could not read image " << g::filename << std::endl;
        return EXIT_FAILURE;
    }
    namedWindow(g::window_name.input, 1);
    namedWindow(g::window_name.output_sequential, 1);
    double t;
    
    // sequential
    t = (double)getTickCount();
    conv::seq(g::image.input, g::image.output_1, g::kernel);

    t = ((double)getTickCount() - t) / getTickFrequency();
    std::cout << "Sequential implementation " << (t * 1000) << " ms" << std::endl;
    
    // show input and output images
    imshow(g::window_name.input, g::image.input);
    imshow(g::window_name.output_sequential, g::image.output_1);

    waitKey(0);

    return EXIT_SUCCESS;
}
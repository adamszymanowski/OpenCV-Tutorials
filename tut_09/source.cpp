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

    struct Images { Mat input, output_sequential, output_parallel, output_parallel_row_split; };
    Images image;
    
    struct WindowNames { const std::string input, output_sequential, output_parallel, output_parallel_row_split; };
    WindowNames window_name {
        .input = "Input Image",
        .output_sequential = "Output Image for Sequential",
        .output_parallel = "Output Image for Parallel",
        .output_parallel_row_split = "Output Image for Parallel Row Split"
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
        border = kernel.rows / 2; // taking care of egde values
        copyMakeBorder(source, source, border, border, border, border, BORDER_REPLICATE);

        destination = Mat(rows, cols, source.type());

        for (int idx_i = 0; idx_i < rows; ++idx_i)
        {
            uchar *dest_ptr = destination.ptr(idx_i);
            for (int idx_j = 0; idx_j < cols; ++idx_j)
            {
                double value = 0.0;
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

    void parallel(Mat source, Mat& destination, Mat kernel)
    {
        const int
        rows = source.rows,
        cols = source.cols,
        border = kernel.rows / 2;
        copyMakeBorder(source, source, border, border, border, border, BORDER_REPLICATE);

        destination = Mat(rows, cols, CV_8UC1, Scalar(0));
        parallel_for_(Range(0, rows * cols), [&](const Range &range)
        {
            for (int idx_r = range.start; idx_r < range.end; ++idx_r)
            {
                int 
                idx_i = idx_r / cols,
                idx_j = idx_r % cols;

                double value = 0.0;
                for (int idx_k = -border; idx_k <= border; ++idx_k)
                {
                    uchar *src_ptr = source.ptr(idx_i + border + idx_k);
                    for (int idx_l = -border; idx_l <= border; ++idx_l)
                    {
                        value += kernel.ptr<double>(idx_k + border)[idx_l + border] * src_ptr[idx_j + border + idx_l];
                    }
                }
                destination.ptr(idx_i)[idx_j] = saturate_cast<uchar>(value);
            }
        });
    }

    void parallel_row_split(Mat source, Mat& destination, Mat kernel)
    {
        const int
        rows = source.rows,
        cols = source.cols,
        border = kernel.rows / 2; // taking care of edge values
        copyMakeBorder(source, source, border, border, border, border, BORDER_REPLICATE);

        destination = Mat(rows, cols, CV_8UC1, Scalar(0));
        parallel_for_(Range(0, rows), [&](const Range &range)
        {
            for (int idx_i = range.start; idx_i < range.end; ++idx_i)
            {
                uchar* dest_ptr = destination.ptr(idx_i);
                for (int idx_j = 0; idx_j < cols; ++idx_j)
                {
                    double value = 0.0;
                    for (int idx_k = -border; idx_k <= border; ++idx_k)
                    {
                        uchar *src_ptr = source.ptr(idx_i + border + idx_k);
                        for (int idx_l = -border; idx_l <= border; ++idx_l)
                        {
                            value += kernel.ptr<double>(idx_k + border)[idx_l + border] * src_ptr[idx_j + border + idx_l];
                        }
                    }
                    dest_ptr[idx_j] = saturate_cast<uchar>(value);
                }
            }

        });

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
    conv::seq(g::image.input, g::image.output_sequential, g::kernel);
    t = ((double)getTickCount() - t) / getTickFrequency();
    std::cout << "Sequential implementation " << (t * 1000) << " ms" << std::endl;

    #ifdef CV_CXX11
    std::cout << "C++ 11 is available!" << std::endl;
    #endif

    // parallel
    t = (double)getTickCount();
    conv::parallel(g::image.input, g::image.output_parallel, g::kernel);
    t = ((double)getTickCount() - t) / getTickFrequency();
    std::cout << "Parallel implementation " << (t * 1000) << " ms" << std::endl;

    // parallel row split
    t = (double)getTickCount();
    conv::parallel_row_split(g::image.input, g::image.output_parallel_row_split, g::kernel);
    t = ((double)getTickCount() - t) / getTickFrequency();
    std::cout << "Parallel Row Split implementation " << (t * 1000) << " ms" << std::endl;
    
    // show input and output images
    imshow(g::window_name.input, g::image.input);
    imshow(g::window_name.output_sequential, g::image.output_sequential);
    imshow(g::window_name.output_parallel, g::image.output_parallel);
    imshow(g::window_name.output_parallel_row_split, g::image.output_parallel_row_split);

    waitKey(0);

    return EXIT_SUCCESS;
}
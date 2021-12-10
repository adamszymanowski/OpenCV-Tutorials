#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

namespace 
{
    // Global variables
    struct Images { Mat original, corrected, gamma_corrected; };
    Images global_image;
    
    struct Parameters { int alpha = 100, beta = 100, gamma = 100; };
    Parameters param;
    
    struct WindowNames {
        const std::string 
        brightness_and_contrast = "Brigtness and contrast adjustments",
        gamma = "Gamma correction";
    };
    WindowNames window_name;

    struct TrackbarNames {
        const std::string 
        contrast = "Alpha gain (contrast)",
        brightness = "Beta bias (brightness)",
        gamma = "Gamma correction";
    };
    TrackbarNames trackbar_name;

    // alpha and beta transform
    void basic_linear_transform(const Mat& image, const double alpha, const int beta)
    {
        CV_Assert(!image.empty());
        Mat converted_image;
        image.convertTo(converted_image, -1, alpha, beta);
        hconcat(image, converted_image, global_image.corrected);
        imshow(window_name.brightness_and_contrast, global_image.corrected);
    }

    void on_linear_transform_alpha_trackbar(int, void *)
    {
        param.alpha = getTrackbarPos(trackbar_name.contrast, window_name.brightness_and_contrast);

        double alpha_value = param.alpha / 100.0;
        int beta_value = param.beta - 100;
        basic_linear_transform(global_image.original, alpha_value, beta_value);
    }

    void on_linear_transform_beta_trackbar(int, void *)
    {
        param.beta = getTrackbarPos(trackbar_name.brightness, window_name.brightness_and_contrast);

        double alpha_value = param.alpha / 100.0;
        int beta_value = param.beta - 100;
        basic_linear_transform(global_image.original, alpha_value, beta_value);
    }

    // gamma correction
    void gamma_correction(const Mat& image, const float gamma)
    {
        CV_Assert(gamma >= 0);
        CV_Assert(!image.empty());
        
        Mat look_up_table(1, 256, CV_8U);
        uchar* lut_p = look_up_table.ptr();
        
        for (int i = 0; i < 256; ++i)
        {
            lut_p[i] = saturate_cast<uchar>(pow(i / 255.0, 1.0/gamma) * 255.0);
        }

        Mat result_image = image.clone();
        LUT(image, look_up_table, result_image);

        hconcat(image, result_image, global_image.gamma_corrected);
        imshow(window_name.gamma, global_image.gamma_corrected);
    }

    void on_gamma_correction_trackbar(int, void *)
    {
        param.gamma = getTrackbarPos(trackbar_name.gamma, window_name.gamma);
        float gamma_value = (param.gamma / 100.0);
        //std::cout << "g=(" << param.gamma << ", " << gamma_value << ")" << std::endl;
        gamma_correction(global_image.original, gamma_value);
    }
}


int main()
{
    std::cout << " Contrast and Brightness Adjustments, Gamma Correction (OpenCV: " << CV_VERSION  << ")" << std::endl;

    // Load image
    std::string filename = samples::findFile("lena.jpg");
    global_image.original = imread(filename);
    if (global_image.original.empty())
    {
        std::cout << "Error reading file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

    // Show images and user interface
    namedWindow(window_name.brightness_and_contrast);
    createTrackbar(trackbar_name.contrast, window_name.brightness_and_contrast, nullptr, 500, on_linear_transform_alpha_trackbar);
    setTrackbarPos(trackbar_name.contrast, window_name.brightness_and_contrast, param.alpha);
    createTrackbar(trackbar_name.brightness, window_name.brightness_and_contrast, nullptr, 200, on_linear_transform_beta_trackbar);
    setTrackbarPos(trackbar_name.brightness, window_name.brightness_and_contrast, param.beta);

    namedWindow(window_name.gamma);
    createTrackbar(trackbar_name.gamma, window_name.gamma, nullptr, 300, on_gamma_correction_trackbar);
    setTrackbarPos(trackbar_name.gamma, window_name.gamma, param.gamma);

    waitKey();

    return EXIT_SUCCESS;
}
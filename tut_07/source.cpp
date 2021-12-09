#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

int main()
{
    std::cout << "Discrete Fourier Transform (OpenCV: " << CV_VERSION  << ")" << std::endl;

    // Load image
    const std::string filename = samples::findFile("lena.jpg");
    Mat image = imread(filename, IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cout << "Couldn't load image " << filename << std::endl;
        EXIT_FAILURE;
    }

    // DFT preparation
    Mat padded_image;
    const int m = getOptimalDFTSize(image.rows);
    const int n = getOptimalDFTSize(image.cols);
            // Expand padded_image to optimal size, and on the border add zero values
    copyMakeBorder(image, padded_image, 0, m - image.rows, 0, n - image.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded_image), Mat::zeros(padded_image.size(), CV_32F)};

    Mat complex_image;
    merge(planes, 2, complex_image);    // Add to the expaned another plane with zeros
    dft(complex_image, complex_image);  // This way result may fit in source matrix
            
            // Compute the magnitude and switch to logarithmic scale
            // => log(1 + sqrt(Re(DFT(img)^2) + Im(DFT(img)^2))
    split(complex_image, planes);       // planes[0] = Re(DFT(img)), planes[1] = Im(DFT(img))
    magnitude(planes[0], planes[1], planes[0]);
    Mat magnitude_image = planes[0];

            // Switch to logarithmic scale
    magnitude_image += Scalar::all(1);
    log(magnitude_image, magnitude_image);

            // Crop the spectrum, if it has an odd number of rows or columns
    magnitude_image = magnitude_image(Rect(0, 0, magnitude_image.cols & -2, magnitude_image.rows & -2));

            // Rearrange the quadrants of Fourier image, so that origin is at the image center
    const int cx = magnitude_image.cols / 2;
    const int cy = magnitude_image.rows / 2;

    Mat quad_1(magnitude_image, Rect(0, 0, cx, cy));    // Top-Left (Create ROI per quadrant)
    Mat quad_2(magnitude_image, Rect(cx, 0, cx, cy));   // Top-Right
    Mat quad_3(magnitude_image, Rect(0, cy, cx, cy));   // Bottom-Left
    Mat quad_4(magnitude_image, Rect(cx, cy, cx, cy));  // Bottom-Right

    #if 0
            // NOTE Change #if 0 to #if 1, to actually show
            // Show them for fun, because why not?
    normalize(quad_1, quad_1, 0, 1, NORM_MINMAX);
    normalize(quad_2, quad_2, 0, 1, NORM_MINMAX);
    normalize(quad_3, quad_3, 0, 1, NORM_MINMAX);
    normalize(quad_4, quad_4, 0, 1, NORM_MINMAX);
    imshow("Quad 1", quad_1);
    imshow("Quad 2", quad_2);
    imshow("Quad 3", quad_3);
    imshow("Quad 4", quad_4);
    #endif

    Mat temp_quad;
    quad_1.copyTo(temp_quad);    // swap Top-Left with Bottom-Right
    quad_4.copyTo(quad_1); 
    temp_quad.copyTo(quad_4);

    quad_2.copyTo(temp_quad);   // swap Top-Right with Bottom-Left
    quad_3.copyTo(quad_2);
    temp_quad.copyTo(quad_3);
    
    normalize(magnitude_image, magnitude_image, 0, 1, NORM_MINMAX); // Transform the matrix with float values into
                                                                    // a viewable image form (float beteewn values 0 and 1).
    
    // Show result
    imshow("Image", image);
    imshow("Spectrum magnitude", magnitude_image);
    waitKey();

    return EXIT_SUCCESS;
}
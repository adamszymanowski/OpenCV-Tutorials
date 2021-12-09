#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

struct Images {
    std::string path_to_h, path_to_r, description_h, description_r;
    Mat horizontal, rotated;
};
Images image;


int main()
{
    std::cout << "DFT on Horizontal Text and Rotated Text images(OpenCV: " << CV_VERSION  << ")" << std::endl;

    image.description_h = "Horizontal Text";
    image.path_to_h = samples::findFile("imageTextN.png");
    image.description_r = "Rotated Text";
    image.path_to_r = samples::findFile("imageTextR.png");

    image.horizontal = imread(image.path_to_h, IMREAD_GRAYSCALE);
    if (image.horizontal.empty())
    {
        std::cout << "Could not load " << image.path_to_h << std::endl;
        return EXIT_FAILURE;
    }

    image.rotated = imread(image.path_to_r, IMREAD_GRAYSCALE);
    if (image.rotated.empty())
    {
        std::cout << "Could not load " << image.path_to_r << std::endl;
        return EXIT_FAILURE;
    }

    // horizontal image DFT
    Mat padded_image_h;
    const int mh = getOptimalDFTSize(image.horizontal.rows);
    const int nh = getOptimalDFTSize(image.horizontal.cols);
    copyMakeBorder(image.horizontal, padded_image_h, 0, (mh - image.horizontal.rows), 0, (nh - image.horizontal.cols), BORDER_CONSTANT, Scalar::all(0));
    Mat planes_h[] = {Mat_<float>(padded_image_h), Mat::zeros(padded_image_h.size(), CV_32F)};

    Mat complex_image_h;
    merge(planes_h, 2, complex_image_h);
    dft(complex_image_h, complex_image_h);
    split(complex_image_h, planes_h);
    magnitude(planes_h[0], planes_h[1], planes_h[0]);
    Mat magnitude_image_h = planes_h[0];
    magnitude_image_h += Scalar::all(1);
    log(magnitude_image_h, magnitude_image_h);
    magnitude_image_h = magnitude_image_h(Rect(0, 0, magnitude_image_h.cols & -2, magnitude_image_h.rows & -2));

    const int cxh = magnitude_image_h.cols / 2;
    const int cyh = magnitude_image_h.rows / 2;

    Mat quad_0h(magnitude_image_h, Rect(0, 0, cxh, cyh));
    Mat quad_1h(magnitude_image_h, Rect(cxh, 0, cxh, cyh));
    Mat quad_2h(magnitude_image_h, Rect(0, cyh, cxh, cyh));
    Mat quad_3h(magnitude_image_h, Rect(cxh, cyh, cxh, cyh));

    Mat temp_quad_h;
    quad_0h.copyTo(temp_quad_h);
    quad_3h.copyTo(quad_0h);
    temp_quad_h.copyTo(quad_3h);

    quad_1h.copyTo(temp_quad_h);
    quad_2h.copyTo(quad_1h);
    temp_quad_h.copyTo(quad_2h);

    normalize(magnitude_image_h, magnitude_image_h, 0, 1, NORM_MINMAX);
    std::cout << "hozizontal image size           " << image.horizontal.size() << std::endl;
    std::cout << "horizontal image magnitude size " << magnitude_image_h.size() << std::endl;
    imshow(image.description_h, image.horizontal);
    imshow(image.description_h + " Magintude", magnitude_image_h);

    // rotated image DFT
    Mat padded_image_r;

    const int mr = getOptimalDFTSize(image.rotated.rows);
    const int nr = getOptimalDFTSize(image.rotated.cols);
    copyMakeBorder(image.rotated, padded_image_r, 0, (mr-image.rotated.rows), 0, (nr-image.rotated.cols), BORDER_CONSTANT, Scalar::all(0));
    Mat planes_r[] = {Mat_<float>(padded_image_r), Mat::zeros(padded_image_r.size(), CV_32F)};

    Mat complex_image_r;
    merge(planes_r, 2, complex_image_r);
    dft(complex_image_r, complex_image_r);
    split(complex_image_r, planes_r);
    magnitude(planes_r[0], planes_r[1], planes_r[0]);
    Mat magnitude_image_r = planes_r[0];
    magnitude_image_r += Scalar::all(1);
    log(magnitude_image_r, magnitude_image_r);
    magnitude_image_r = magnitude_image_r(Rect(0, 0, magnitude_image_r.cols & -2, magnitude_image_r.rows & -2));

    const int cxr = magnitude_image_r.cols / 2;
    const int cyr = magnitude_image_r.rows / 2;

    Mat quad_0r(magnitude_image_r, Rect(0, 0, cxr, cyr));
    Mat quad_1r(magnitude_image_r, Rect(cxr, 0, cxr, cyr));
    Mat quad_2r(magnitude_image_r, Rect(0, cyr, cxr, cyr));
    Mat quad_3r(magnitude_image_r, Rect(cxr, cyr, cxr, cyr));

    Mat temp_quad_r;
    quad_0r.copyTo(temp_quad_r);
    quad_3r.copyTo(quad_0r);
    temp_quad_r.copyTo(quad_3r);

    quad_1r.copyTo(temp_quad_r);
    quad_2r.copyTo(quad_1r);
    temp_quad_r.copyTo(quad_2r);

    normalize(magnitude_image_r, magnitude_image_r, 0, 1, NORM_MINMAX);
    std::cout << "rotated image size          " << image.rotated.size() << std::endl;
    std::cout << "rotated imagemagnitude size " << magnitude_image_r.size() << std::endl; 
    imshow(image.description_r, image.rotated);
    imshow(image.description_r + " Magnitude", magnitude_image_r);

    waitKey(0);

    return EXIT_SUCCESS;
}
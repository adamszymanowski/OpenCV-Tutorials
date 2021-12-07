#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;
// we're NOT using "using namespace std;" to avoid collisions between the beta variable and std::beta in C++17
using std::cin;
using std::cout;
using std::endl;

int main(int,char**)
{
    std::cout << "Changing the contrast and brightness of an image! (OpenCV: " << CV_VERSION  << ")" << std::endl;
    
    // Load image
    const std::string filename = samples::findFile("lena.jpg");
    Mat image = imread(filename);
    if (image.empty())
    {
        cout << "Could not load image " << filename << endl;
        return EXIT_FAILURE;
    }

    // User input
    double alpha = 1.0, input_alpha; // contrast
    int beta = 0, input_beta; // brightness

    cout << "Enter alpha (contrast) [0.0-3.0]: ";
    cin >> input_alpha;
    cout << "Enter beta (brightness) [0-100]: ";
    cin >> input_beta;

    if (input_alpha >= 1.0 && input_alpha <= 3.0)
    {
        alpha = input_alpha;
    }
    else 
    {
        cout << "Wrong vaule for alpha, using default alpha=" << alpha << " instead." << endl;
    }

    if (input_beta >= 0 && input_beta <= 100)
    {
        beta = input_beta;
    }
    else 
    {
        cout << "Wrong vaule for alpha, using default beta=" << beta << " instead." << endl;
    }

    // Pixel-by-pixel transformation
    Mat transformed_image_1 = Mat::zeros(image.size(), image.type());
    for (int y = 0; y < image.rows; ++y)
    {
        for (int x = 0; x < image.cols; ++x)
        {
            for (int c = 0; c < image.channels(); ++c)
            {
                transformed_image_1.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(alpha*image.at<Vec3b>(y,x)[c] + beta);
            }
        }
    }

    // Transformation using convertTo
    Mat transformed_image_2 = Mat::zeros(image.size(), image.type());
    image.convertTo(transformed_image_2, -1, alpha, beta);

    imshow("Original Image", image);
    imshow("Transformed (pixel-by-pixel) image", transformed_image_1);
    imshow("Transformed (convertTo) image", transformed_image_2);
    waitKey(0);

    return EXIT_SUCCESS;
}
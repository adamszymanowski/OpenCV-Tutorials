#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;
// we're NOT "using namespace std;" here to avoid collisions between beta variable and std::beta in c++17 
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::cout << "Adding (blending) two images using OpenCV (OpenCV: " << CV_VERSION  << ")" << std::endl;

    // User input
    double alpha = 0.5, beta, input;
    cout << "Enter alpha <0.0-1.0>: ";
    cin >> input;
    if (input > 0 && input < 1)
    {
        alpha = input;
    }
    else
    {
        cout << "Wrong value of alpha, using default " << alpha << " instead." << endl;
    }
    beta = 1.0 - alpha;

    // Image loading
    cout << "---- INFO ----" << endl;
    const std::string filename_1 = samples::findFile("WindowsLogo.jpg");
    const std::string filename_2 = samples::findFile("LinuxLogo.jpg"); 
 
    Mat image_1 = imread(filename_1);
    Mat image_2 = imread(filename_2);

    if (image_1.empty()) 
    { 
        cout << "Error loading " << filename_1 << endl;
        return EXIT_FAILURE;
    }

    if (image_2.empty())
    {
        cout << "Error loading " << filename_2 << endl;
        return EXIT_FAILURE;
    }

    cout << filename_1 << " dimensions: " << image_1.cols << "x" << image_1.rows << endl;
    cout << filename_1 << " dimensions: " << image_2.cols << "x" << image_2.rows << endl;
    cout << "--------------" << endl;

    // Blending
    Mat blended_img;
    addWeighted(image_1, alpha, image_2, beta, 0.0, blended_img);

    imshow("Linear Blend", blended_img);
    waitKey(0);

    return EXIT_SUCCESS;
}
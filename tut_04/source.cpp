#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    std::cout << "Operations with images (OpenCV: " << CV_VERSION  << ")" << std::endl;

    string filename = samples::findFile("baboon.jpg");
    
    {
        // Load an inmage from a file
        Mat image = imread(filename);
        CV_UNUSED(image);
    }
    {
        // Load an image from a file in grayscale
        Mat image = imread(filename, IMREAD_GRAYSCALE);
        CV_UNUSED(image);
    }
    {
        Mat image(64, 64, CV_8UC3, Scalar(255,0,255)); // Magenta image B G R
        imwrite("magenta_img.png", image);
    }
    {
        Mat image(4,4, CV_8UC3, Scalar(255, 0, 254)); // Magenta image B G R

        int y = 0, x = 0;
        {
            Scalar intensity = image.at<uchar>(y, x);
            cout << "Pixel access 1 - " 
                 << "intensity at (y:" << y << ", x:" << x << ")="
                 << intensity << endl;
            
            CV_UNUSED(intensity);
        }
        {
            Scalar intensity = image.at<uchar>(Point(y, x));
            cout << "Pixel access 2 - " 
                 << "intensity at (y:" << y << ", x:" << x << ")="
                 << intensity << endl;

            CV_UNUSED(intensity);
        }
        {
            Scalar intensity = image.at<Vec3b>(y, x);

            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];
            
            cout << "Pixel access 3 - " 
                 << "intensity at (y:" << y << ", x:" << x << ")="
                 << "R: " << (unsigned int)red << ", G: " << (unsigned int)green << ", B: " << (unsigned int)blue << endl;

            CV_UNUSED(blue);
            CV_UNUSED(green);
            CV_UNUSED(red);
        }
        {
            Vec3f intensity = image.at<Vec3f>(y, x);

            float blue = intensity.val[0];
            float green = intensity.val[1];
            float red = intensity.val[2];

            cout << "Pixel access 4 - " 
            << "intensity at (y:" << y << ", x:" << x << ")="
            << "R: " << red << ", G: " << green << ", B: " << blue << endl;

            CV_UNUSED(blue);
            CV_UNUSED(green);
            CV_UNUSED(red);
        }
        {
            const int size = 32;
            Mat image(size, size, CV_8UC3, Scalar(255, 0, 254)); // Magenta image B G R
            
            for (int i = 0; i < size; ++i)
                image.at<Vec3b>(i, i) = Vec3b(0, 255, 255); // Yellow diagonal

            //imwrite("small_magenta_img.png", image);
        }
        {
            // NOTE: There are functions in OpenCV, especially from calib3d module, such as cv::projectPoints, 
            // that take an array of 2D or 3D points in the form of Mat
            int i = 0;

            // Mat from points vector
            vector<Point2f> points;
            Mat pointsMat = Mat(points);


            // Point access
            //Point2f point = pointsMat.at<Point2f>(i, 0); // This segfaults for some reason ...
            //CV_UNUSED(point);
        }
    }

    // Memory Management and reference counting
    {
        vector<Point3f> points;

        for (int i = 0; i < 16; ++i)
            points.push_back(Point3f(255.0, 192.0, 128.0));

        Mat pointsMat = Mat(points).reshape(1);
        imwrite("from_vec3f_points.png", pointsMat);
        CV_UNUSED(pointsMat);
    }
    {
        Mat image = imread(filename);
        Mat clone_image = image.clone();
        CV_UNUSED(clone_image);
    }
    {
        Mat image = imread(filename);
        Mat sobelx;
        Sobel(image, sobelx, CV_32F, 1, 0);
        imwrite("sobelx.png", sobelx);
    }

    // Primitive operations
    {
        Mat image;
        {
            // Set image to black
            image = Scalar(0);
        }
        {
            image = imread(filename);
            // Select ROI
            Rect r(10, 10, 100, 100);
            Mat small_image = image(r);
            imwrite("small_image.png", small_image);
            CV_UNUSED(small_image);
        }
    }

    {
        // BGR to Gray
        Mat image = imread(filename);
        Mat gray_image;
        cvtColor(image, gray_image, COLOR_BGR2GRAY);
        imwrite("gray_image.png", gray_image);
    }
    {
        // Convert to CV_32F
        Mat src, dst;
        src.convertTo(dst, CV_32F);
    }

    // Visualizing images
    {
        Mat image = imread(filename);
        Mat gray_image;
        cvtColor(image, gray_image, COLOR_BGR2GRAY);
        Mat sobelx;
        Sobel(gray_image, sobelx, CV_32F, 1, 0);
        double min_val, max_val;
        minMaxLoc(sobelx, &min_val, &max_val); // find minimum and maximum intesities;
        Mat normalized_image;
        sobelx.convertTo(normalized_image, CV_8U, 255.0/(max_val - min_val), -min_val * (255.0/(max_val - min_val)));
        imshow("Sobel image", sobelx);
        imshow("Sobel normalized?", normalized_image); // I guess it's normalized, tutorial doesn't explain
        waitKey();
    }

    return 0;
}
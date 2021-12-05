#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;

Mat& ScanImageAndReduceC(Mat& img, const uchar* const table);
Mat& ScanImageAndReduceIterator(Mat& img, const uchar* const table);
Mat& ScanImageAndReduceRandomAccess(Mat& img, const uchar* const table);
const string func_name_1 = "ScanImageAndReduceC";
const string func_name_2 = "ScanImageAndReduceIterator";
const string func_name_3 = "ScanImageAndReduceRandomAccess";

int main(int argc, char** argv)
{
    cout << "How To Scan Images (OpenCV: " << CV_VERSION  << ")" << endl;

    Mat original_img, reduced_img_1, reduced_img_2, reduced_img_3, reduced_img_4;
    string image_path = samples::findFile("starry_night.jpg");
    original_img = imread(image_path);

    if (original_img.empty())
    {
        cout << "Could not read image: " << image_path << endl;
        return -1;
    }

    int divideWith = 96;

    uchar table[256];
    for (int i = 0; i < 256; ++i)
        table[i] = (uchar)(divideWith * (i/divideWith));

    const int times = 100;
    double t;

    // Function 1
    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        Mat clone_img = original_img.clone();
        reduced_img_1 = ScanImageAndReduceC(clone_img, table);
    }

    t = 1000 * (getTickCount() - t) / getTickFrequency();
    t /= times;
    cout << "Time of reducing with C operator [] (" << func_name_1 
        << ") averaged for " << times << " runs: " << t << " milliseconds." << endl;

    // Function 2
    t =(double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        Mat clone_img = original_img.clone();
        reduced_img_2 = ScanImageAndReduceIterator(clone_img, table);
    }

    t = 1000 * (getTickCount() - t) / getTickFrequency();
    t /= times;
    cout << "Time of reducing with the iterator (" << func_name_2 
    << ") averaged for " << times << " runs: " << t << " milliseconds." << endl;

    // Function 3
    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        Mat clone_img = original_img.clone();
        reduced_img_3 = ScanImageAndReduceRandomAccess(clone_img, table);
    }

    t = 1000 * (getTickCount() - t) / getTickFrequency();
    t /= times;
    cout << "Time of reducing with on-the-fly address generation - at function (" << func_name_2 
    << ") averaged for " << times << " runs: " << t << " milliseconds." << endl;

    // Function 4 (built-in LUT)
    Mat look_up_table(1, 256, CV_8U);
    uchar* p = look_up_table.ptr();
    for (int i = 0; i < 256; ++i)
        p[i] = table[i];

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        Mat clone_img = original_img.clone();
        LUT(clone_img, look_up_table, reduced_img_4);
    }

    t = 1000 * (getTickCount() - t) / getTickFrequency();
    t /= times;
    cout << "Time of reducing with LUT function"
    << " averaged for " << times << " runs: " << t << " milliseconds." << endl;


    // Display all the images
    imshow("Original Image", original_img);
    imshow("Reduced Image by " + func_name_1, reduced_img_1);
    imshow("Reduced Image by " + func_name_2, reduced_img_2);
    imshow("Reduced Image by " + func_name_3, reduced_img_3);
    imshow("Reduced Image by LUT", reduced_img_4);

    waitKey(0);

    return 0;
}

Mat& ScanImageAndReduceC(Mat& img, const uchar* const table)
{
    // Accept only char type matrices
    CV_Assert(img.depth() == CV_8U);

    const int channels = img.channels();

    int nRows = img.rows;
    int nCols = img.cols * channels;

    if (img.isContinuous())
    {
        nCols *= nRows;
        nRows = 1; 
    }

    int i, j;
    uchar* p;
    for (i = 0; i < nRows; ++i)
    {
        p = img.ptr<uchar>(i);
        for (j = 0; j < nCols; ++j)
        {
            p[j] = table[p[j]];
        }
    }

    return img;
}

Mat& ScanImageAndReduceIterator(Mat& img, const uchar* const table)
{
    // Accept only char type matrices
    CV_Assert(img.depth() == CV_8U);

    const int channels = img.channels();
    switch (channels)
    {
        case 1:
        {
            MatIterator_<uchar> it, end;
            for (it = img.begin<uchar>(), end = img.end<uchar>(); it != end; ++it)
                *it = table[*it];
        } break;

        case 3:
        {
            MatIterator_<Vec3b> it, end;
            for (it = img.begin<Vec3b>(), end = img.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        } break;
        default:
            cout << "switch default in " << func_name_2 << "shouldn't be reached" << endl;
    }

    return img;
}

Mat& ScanImageAndReduceRandomAccess(Mat& img, const uchar* const table)
{
    // Accept only char type matrices
    CV_Assert(img.depth() == CV_8U);

    const int channels = img.channels();
    switch (channels)
    {
        case 1:
        {
            for (int i = 0; i < img.rows; ++i)
                for (int j = 0; j <img.cols; ++j)
                    img.at<uchar>(i, j) = table[img.at<uchar>(i, j)];
        } break;

        case 3:
        {
            Mat_<Vec3b> img_vec3 = img;
            for (int i = 0; i < img.rows; ++i)
            {
                for (int j = 0; j < img.cols; ++j)
                {
                    img_vec3(i, j)[0] = table[img_vec3(i, j)[0]];
                    img_vec3(i, j)[1] = table[img_vec3(i, j)[1]];
                    img_vec3(i, j)[2] = table[img_vec3(i, j)[2]];
                }
            }
            img = img_vec3; 
        } break;
        default:
            cout << "switch default in " << func_name_3 << "shouldn't be reached" << endl;
    }

    return img;
}
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);

int main(int argc, char** argv)
{
    cout << "How To Scan Images (OpenCV: " << CV_VERSION  << ")" << endl;

    Mat original_img, reduced_img;
    string image_path = samples::findFile("starry_night.jpg");
    original_img = imread(image_path);

    if (original_img.empty())
    {
        cout << "Could not read image: " << image_path << endl;
        return -1;
    }

    int divideWith = 64;

    uchar table[256];
    for (int i = 0; i < 256; i++)
        table[i] = (uchar)(divideWith * (i/divideWith));

    const int times = 100;
    double t;

    t = (double)getTickCount();

    for (int i = 0; i < times; i++)
    {
        cv::Mat clone_img = original_img.clone();
        reduced_img = ScanImageAndReduceC(clone_img, table);
    }

    t = 1000 * (getTickCount() - t) / getTickFrequency();
    cout << "Time of reducing with C operator [] (averaged for "
        << times << " runs): " << t << " milliseconds." << endl;

    imshow("Original Image", original_img);
    imshow("Reduced Image", reduced_img);
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

/*
    switch (channels)
    {
        case 1:
        {

        } break;

        case 3:
        {

        } break;
        default:
            cout << "switch default in " << "canImageAndReduceIterator" << "shouldn't be reached" << endl;
    }
*/
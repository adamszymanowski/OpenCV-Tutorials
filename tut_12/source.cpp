#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

const int number = 100;
const int delay = 5;
const int window_width = 900;
const int window_height = 600;
int x_1 = -window_width/2;
int x_2 = window_width*3/2;
int y_1 = -window_width/2;
int y_2 = window_width*3/2;

static cv::Scalar randomColor(cv::RNG& rng);
int Drawing_Random_Lines(cv::Mat image, const char* window_name, cv::RNG rng);
int Drawing_Random_Rectangles(cv::Mat image, const char* window_name, cv::RNG rng);
int Drawing_Random_Ellipses(cv::Mat image, const char* window_name, cv::RNG rng);
int Drawing_Random_Polylines(cv::Mat image, const char* window_name, cv::RNG rng);
int Drawing_Random_Filled_Polygons(cv::Mat image, const char* window_name, cv::RNG rng);
int Drawing_Random_Circles(cv::Mat image, const char* window_name, cv::RNG rng);
int Displaying_Random_Text(cv::Mat image, const char* window_name, cv::RNG rng);
int Displaying_Big_End(cv::Mat image, const char* window_name);

int main()
{
    std::cout << "Random generator and text with OpenCV (OpenCV: " << CV_VERSION  << ")" << std::endl;
    int c;
    const char* window_name = "Drawing_2 Tutorial";
    cv::RNG rng(0xFFFFFFFF);

    cv::Mat image = cv::Mat::zeros(window_height, window_width, CV_8UC3);
    cv::imshow(window_name, image);
    cv::waitKey(delay);

    c = Drawing_Random_Lines(image, window_name, rng);
    if (c != 0) return 0;

    c = Drawing_Random_Rectangles(image, window_name, rng);
    if (c != 0) return 0;

    c = Drawing_Random_Ellipses(image, window_name, rng);
    if (c != 0) return 0;

    c = Drawing_Random_Polylines(image, window_name, rng);
    if (c != 0) return 0; 

    c = Drawing_Random_Filled_Polygons(image, window_name, rng);
    if (c != 0) return 0; 

    c = Drawing_Random_Circles(image, window_name, rng);
    if (c != 0) return 0;

    c = Displaying_Random_Text(image, window_name, rng);
    if (c != 0) return 0;

    c = Displaying_Big_End(image, window_name);
    if (c != 0) return 0;

    cv::waitKey(0);
}

int Drawing_Random_Lines(cv::Mat image, const char* window_name, cv::RNG rng)
{
    cv::Point pt1, pt2;
    for (int i = 0; i < number; ++i)
    {
        pt1.x = rng.uniform(x_1, x_2);
        pt1.y = rng.uniform(y_1, y_2);
        pt2.x = rng.uniform(x_1, x_2);
        pt2.y = rng.uniform(y_1, y_2);

        cv::line(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), 8);
        cv::imshow(window_name, image);
        if (cv::waitKey(delay)>= 0)
            return -1;
    }

    return 0;
}

static cv::Scalar randomColor(cv::RNG& rng)
{
    int icolor = (unsigned) rng;
    return cv::Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

int Drawing_Random_Rectangles(cv::Mat image, const char* window_name, cv::RNG rng)
{   
    cv::Point pt1, pt2;
    int thickness;
    for (int i = 0; i < number; ++i)
    {
        thickness = rng.uniform(-1, 10);
        pt1.x = rng.uniform(x_1, x_2);
        pt1.y = rng.uniform(y_1, y_2);
        pt2.x = rng.uniform(x_1, x_2);
        pt2.y = rng.uniform(y_1, y_2);

        cv::rectangle(image, pt1, pt2, randomColor(rng), thickness, cv::LINE_8);

        cv::imshow(window_name, image);
        if (cv::waitKey(delay) >= 0)
            { return -1; }
    }

    return 0;
}

int Drawing_Random_Ellipses(cv::Mat image, const char* window_name, cv::RNG rng)
{
    //std::cout << "RAN" << std::endl;
    for (int i = 0; i < number; ++i)
    {
        cv::Point center;
        center.x = rng.uniform(x_1, x_2);
        center.y = rng.uniform(y_1, y_2);

        cv::Size axes;
        axes.width = rng.uniform(100, 200);
        axes.height = rng.uniform(100, 200);

        double angle = rng.uniform(90, 180);

        cv::ellipse(
            image, center, axes, angle, angle - 100, angle + 200,
            randomColor(rng), rng.uniform(-1, 9), cv::LINE_8 
        );
        
        cv::imshow(window_name, image);
        if (cv::waitKey(delay) >= 0)
            { return -1; }
    }
    return 0;
}

int Drawing_Random_Polylines(cv::Mat image, const char* window_name, cv::RNG rng)
{
    for(int i = 0; i < number; ++i)
    {
        cv::Point pt[2][3];

        pt[0][0].x = rng.uniform(x_1, x_2);
        pt[0][0].y = rng.uniform(y_1, y_2);
        pt[0][1].x = rng.uniform(x_1, x_2);
        pt[0][1].y = rng.uniform(y_1, y_2);
        pt[0][2].x = rng.uniform(x_1, x_2);
        pt[0][2].y = rng.uniform(y_1, y_2);
        pt[1][0].x = rng.uniform(x_1, x_2);
        pt[1][0].y = rng.uniform(y_1, y_2);
        pt[1][1].x = rng.uniform(x_1, x_2);
        pt[1][1].y = rng.uniform(y_1, y_2);
        pt[1][2].x = rng.uniform(x_1, x_2);
        pt[1][2].y = rng.uniform(y_1, y_2);

        const cv::Point* ppt[2] = { pt[0], pt[1] };
        int npt[] = { 3, 3 };
        
        cv::polylines(image, ppt, npt, 2, true, randomColor(rng), rng.uniform(1, 10), cv::LINE_8);
        
        cv::imshow(window_name, image);
        if (cv::waitKey(delay) >= 0)
            { return -1; }
    }
    return 0;
}

int Drawing_Random_Filled_Polygons(cv::Mat image, const char* window_name, cv::RNG rng)
{
    for (int i = 0; i < number; ++i)
    {
        cv::Point pt[2][3];

        pt[0][0].x = rng.uniform(x_1, x_2);
        pt[0][0].y = rng.uniform(y_1, y_2);
        pt[0][1].x = rng.uniform(x_1, x_2);
        pt[0][1].y = rng.uniform(y_1, y_2);
        pt[0][2].x = rng.uniform(x_1, x_2);
        pt[0][2].y = rng.uniform(y_1, y_2);
        pt[1][0].x = rng.uniform(x_1, x_2);
        pt[1][0].y = rng.uniform(y_1, y_2);
        pt[1][1].x = rng.uniform(x_1, x_2);
        pt[1][1].y = rng.uniform(y_1, y_2);
        pt[1][2].x = rng.uniform(x_1, x_2);
        pt[1][2].y = rng.uniform(y_1, y_2);

        const cv::Point* ppt[2] = { pt[0], pt[1] };
        int npt[] = { 3, 3 };
        
        cv::fillPoly(image, ppt, npt, 2, randomColor(rng), cv::LINE_8);
        
        cv::imshow(window_name, image);
        if (cv::waitKey(delay) >= 0)
            { return -1; }
    }
    return 0;
}

int Drawing_Random_Circles(cv::Mat image, const char* window_name, cv::RNG rng)
{
    for (int i = 0; i < number; ++i)
    {
        cv::Point center;
        center.x = rng.uniform(x_1, x_2);
        center.y = rng.uniform(y_1, y_2);

        cv::circle(image, center, rng.uniform(30, 300), randomColor(rng), rng.uniform(-1, 9), cv::LINE_8);

        cv::imshow(window_name, image);
        if (cv::waitKey(delay) >= 0)
            { return -1; }
    }

    return 0;
}

int Displaying_Random_Text(cv::Mat image, const char* window_name, cv::RNG rng)
{
    for (int i = 0; i < number; ++i)
    {
        cv::Point org;
        org.x = rng.uniform(x_1, x_2);
        org.y = rng.uniform(y_1, y_2);

        cv::putText(image, "Testing text rendering", org, rng.uniform(0,8),
                    rng.uniform(0, 100)*0.05+0.1, randomColor(rng), rng.uniform(1, 10), cv::LINE_8);

        cv::imshow(window_name, image);
        if (cv::waitKey(delay) >= 0)
            { return -1; }
    }

    return 0;
}

int Displaying_Big_End(cv::Mat image, const char* window_name)
{
    const char* text = "OpenCV Forever!";
    cv::Size text_size = cv::getTextSize(text, cv::FONT_HERSHEY_COMPLEX, 3, 5, 0);
    cv::Point org{(window_width - text_size.width)/2, (window_height - text_size.height)/2};
    cv::Mat image2;
    for (int i = 0; i < 255; ++i)
    {

        image2 = image - cv::Scalar::all(i);
        cv::putText(image2, text, org, cv::FONT_HERSHEY_COMPLEX, 
                    3, cv::Scalar(i, i, 255), 5, cv::LINE_8);

        cv::imshow(window_name, image2);
        if (cv::waitKey(delay) >= 0)
            { return -1; }
    }
    return 0;
}
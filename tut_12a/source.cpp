#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

const int number = 100;
const int delay = 5;
const int window_width = 900;
const int window_height = 600;

static cv::Scalar randomColor(cv::RNG& rng);
static cv::Point randomPoint(cv::RNG& rng);
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
    
    const char* window_name = "Drawing_2 Tutorial";
    cv::RNG rng(0xFFFFFFFF);

    cv::Mat image = cv::Mat::zeros(window_height, window_width, CV_8UC3);
    cv::imshow(window_name, image);
    cv::waitKey(delay);

    if ( Drawing_Random_Lines(image, window_name, rng) != 0 )               { return 0; } 
    if ( Drawing_Random_Rectangles(image, window_name, rng) != 0 )          { return 0; }
    if ( Drawing_Random_Ellipses(image, window_name, rng) != 0 )            { return 0; }
    if ( Drawing_Random_Polylines(image, window_name, rng) != 0 )           { return 0; }
    if ( Drawing_Random_Filled_Polygons(image, window_name, rng) != 0 )     { return 0; }
    if ( Drawing_Random_Circles(image, window_name, rng) != 0 )             { return 0; }
    if ( Displaying_Random_Text(image, window_name, rng) != 0 )             { return 0; }
    if ( Displaying_Big_End(image, window_name) != 0 )                      { return 0; }

    cv::waitKey(0);
}

static cv::Scalar randomColor(cv::RNG& rng)
{
    int icolor = (unsigned) rng;
    return cv::Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

static cv::Point randomPoint(cv::RNG& rng)
{
    const int coord_min = -window_width/2;
    const int coord_max = window_width*3/2;
    return cv::Point(rng.uniform(coord_min, coord_max), rng.uniform(coord_min, coord_max));
}

int Drawing_Random_Lines(cv::Mat image, const char* window_name, cv::RNG rng)
{
    cv::Point pt1, pt2;
    for (int i = 0; i < number; ++i)
    {
        pt1 = randomPoint(rng);
        pt2 = randomPoint(rng);

        cv::line(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), 8);
        cv::imshow(window_name, image);
        if (cv::waitKey(delay)>= 0)
            return -1;
    }

    return 0;
}

int Drawing_Random_Rectangles(cv::Mat image, const char* window_name, cv::RNG rng)
{   
    cv::Point pt1, pt2;
    int thickness;
    for (int i = 0; i < number; ++i)
    {
        thickness = rng.uniform(-1, 10);
        pt1 = randomPoint(rng);
        pt2 = randomPoint(rng);

        cv::rectangle(image, pt1, pt2, randomColor(rng), thickness, cv::LINE_8);

        cv::imshow(window_name, image);
        if (cv::waitKey(delay) >= 0)
            return -1;
    }

    return 0;
}

int Drawing_Random_Ellipses(cv::Mat image, const char* window_name, cv::RNG rng)
{
    for (int i = 0; i < number; ++i)
    {
        cv::Point center;
        center = randomPoint(rng);

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
            return -1;
    }
    return 0;
}

int Drawing_Random_Polylines(cv::Mat image, const char* window_name, cv::RNG rng)
{
    const int number_of_points = 6;
    for(int i = 0; i < number; ++i)
    {
        std::vector<cv::Point> points;
        for (int n = 0; n < number_of_points; ++n)
            points.push_back(randomPoint(rng));

        cv::polylines(image, points, true, randomColor(rng), rng.uniform(1, 10), cv::LINE_8);
        
        cv::imshow(window_name, image);
        if (cv::waitKey(delay) >= 0)
            return -1;
    }
    return 0;
}

int Drawing_Random_Filled_Polygons(cv::Mat image, const char* window_name, cv::RNG rng)
{
    const int number_of_points = 6;
    for(int i = 0; i < number; ++i)
    {
        std::vector<cv::Point> points;
        for (int n = 0; n < number_of_points; ++n)
            points.push_back(randomPoint(rng));
        
        cv::fillPoly(image, points, randomColor(rng), cv::LINE_8);
        
        cv::imshow(window_name, image);
        if (cv::waitKey(delay) >= 0)
            return -1;
    }
    return 0;
}

int Drawing_Random_Circles(cv::Mat image, const char* window_name, cv::RNG rng)
{
    for (int i = 0; i < number; ++i)
    {
        cv::Point center = randomPoint(rng);

        cv::circle(image, center, rng.uniform(30, 300), randomColor(rng), rng.uniform(-1, 9), cv::LINE_8);

        cv::imshow(window_name, image);
        if (cv::waitKey(delay) >= 0)
            return -1;
    }

    return 0;
}

int Displaying_Random_Text(cv::Mat image, const char* window_name, cv::RNG rng)
{
    for (int i = 0; i < number; ++i)
    {
        cv::Point org = randomPoint(rng);

        cv::putText(image, "Testing text rendering", org, rng.uniform(0,8),
                    rng.uniform(0, 100)*0.05+0.1, randomColor(rng), rng.uniform(1, 10), cv::LINE_8);

        cv::imshow(window_name, image);
        if (cv::waitKey(delay) >= 0)
            return -1;
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
            return -1;
    }
    return 0;
}

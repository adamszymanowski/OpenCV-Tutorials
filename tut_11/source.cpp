#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

const unsigned image_length = 400;
void my_ellipse(cv::Mat image, double angle);
void my_filled_circle(cv::Mat image, cv::Point center);
void my_rook_polygon(cv::Mat image);
void my_line(cv::Mat image, cv::Point start, cv::Point end);

int main()
{
    std::cout << "Basic Drawing (OpenCV: " << CV_VERSION  << ")" << std::endl;
    
    // Setup
    const char* window_atom = "Drawing 1: Atom";
    const char* window_rook = "Drawing 2: Rook";

    cv::Mat image_atom = cv::Mat::zeros(image_length, image_length, CV_8UC3);
    cv::Mat image_rook = cv::Mat::zeros(image_length, image_length, CV_8UC3);

    // Drawing 1
    my_ellipse(image_atom, 90);
    my_ellipse(image_atom, 0);
    my_ellipse(image_atom, 45);
    my_ellipse(image_atom, -45);

    my_filled_circle(image_atom, cv::Point(image_length/2, image_length/2));

    // Drawing 2
    my_rook_polygon(image_rook);

    cv::rectangle(
        image_rook,
        cv::Point(0, 7*image_length/8),
        cv::Point(image_length, image_length),
        cv::Scalar(0, 255, 255),
        cv::FILLED,
        cv::LINE_8
    );

    my_line(image_rook, cv::Point(0, 15*image_length/16), cv::Point(image_length, 15*image_length/16));
    my_line(image_rook, cv::Point(image_length/4, 7*image_length/8), cv::Point(image_length/4, image_length));
    my_line(image_rook, cv::Point(image_length/2, 7*image_length/8), cv::Point(image_length/2, image_length));
    my_line(image_rook, cv::Point(3*image_length/4, 7*image_length/8), cv::Point(3*image_length/4, image_length));

    // Display results
    cv::imshow(window_atom, image_atom);
    cv::moveWindow(window_atom, image_length, image_length/2);
    cv::imshow(window_rook, image_rook);
    cv::moveWindow(window_rook, image_length*2, image_length/2);
    cv::waitKey();
}

void my_ellipse(cv::Mat image, double angle)
{
    const int thickness = 2;
    const int line_type = 8;

    cv::ellipse(
        image,
        cv::Point(image_length/2, image_length/2),
        cv::Size(image_length/4, image_length/16),
        angle,
        0,
        360,
        cv::Scalar(255, 0, 0),
        thickness,
        line_type
    );
}

void my_filled_circle(cv::Mat image, cv::Point center)
{
    cv::circle(
        image,
        center,
        image_length/32,
        cv::Scalar(0, 0, 255),
        cv::FILLED,
        cv::LINE_8
    );
}

void my_rook_polygon(cv::Mat image)
{
    const int line_type = cv::LINE_8;
    const auto il = image_length;
    
    std::vector<cv::Point> polygon = {
        cv::Point{    il/4,   7*il/8  },
        cv::Point{  3*il/4,   7*il/8  },
        cv::Point{  3*il/4,  13*il/16 },
        cv::Point{ 11*il/16, 13*il/16 },
        cv::Point{ 19*il/32,  3*il/8  },
        cv::Point{  3*il/4,   3*il/8  },
        cv::Point{  3*il/4,     il/8  },
        cv::Point{ 26*il/40,    il/8  },
        cv::Point{ 26*il/40,    il/4  },
        cv::Point{ 22*il/40,    il/4  },
        cv::Point{ 22*il/40,    il/8  },
        cv::Point{ 18*il/40,    il/8  },
        cv::Point{ 18*il/40,    il/4  },
        cv::Point{ 14*il/40,    il/4  },
        cv::Point{ 14*il/40,    il/8  },
        cv::Point{    il/4,     il/8  },
        cv::Point{    il/4,   3*il/8  },
        cv::Point{ 13*il/32,  3*il/8  },
        cv::Point{  5*il/16, 13*il/16 },
        cv::Point{    il/4,  13*il/16 }
    };


    cv::fillPoly(
        image,
        polygon,
        cv::Scalar(255, 255, 255),
        line_type
    );

}

void my_line(cv::Mat image, cv::Point start, cv::Point end)
{
    const int thickness = 2;
    const int line_type = cv::LINE_8;
    cv::line(
        image,
        start,
        end,
        cv::Scalar(0,0,0),
        thickness,
        line_type
    );
}

#include <opencv2/core.hpp>

#include <iostream>
#include <string>

struct MyData
{
    MyData() : A(0), X(0), id()
    {}
    explicit MyData(int) : A(97), X(CV_PI), id("mydata1234")        // explicit to avoid implicit conversion
    {}
    void write(cv::FileStorage& fs) const                           // Write serialization
    {
        fs << "{" << "A" << A << "X" << X << "id" << id << "}";
    }
    void read (const cv::FileNode& node)                            // Read serialization
    {
        A = (int)node["A"];
        X = (double)node["X"];
        id = (std::string)node["id"];
    }

    int A;
    double X;
    std::string id;
};

// These write and read functions ust be defined for serialization in FileStorage to work
static void write(cv::FileStorage& fs, const std::string&, const MyData& x)
{
    x.write(fs);
}
static void read(const cv::FileNode& node, MyData& x, const MyData& default_value= MyData())
{
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

// This function will print out our custom class to the console
static std::ostream& operator<<(std::ostream& out, const MyData& m)
{
    out << "{ id = " << m.id << ", ";
    out << "X = " << m.X << ", ";
    out << "A = " << m.A << "}";
    return out;
}

int main(int argc, char* argv[])
{
    std::cout << "File Input and Output using XML and YAML files (OpenCV: " << CV_VERSION  << ")" << std::endl;

    if (argc != 2)
    {
        const bool too_many = (argc > 2);
        if (too_many) 
            std::cout << "Too many arguments! ";
        else
            std::cout << "No arguments! ";

        std::cout << "Please provide output ";
        if (too_many) { std::cout << " just"; }
        std::cout << "filename, for example:" << std::endl;
        std::cout << argv[0] << " " << "output.xml" << std::endl;
        return EXIT_FAILURE;
    }

    const std::string filename = argv[1];

    {   // Write
        std::cout << "Writing to " << filename << std::endl;
        cv::Mat R = cv::Mat_<uchar>::eye(3, 3),
            T = cv::Mat_<double>::zeros(3, 1);
        MyData m(1);

        cv::FileStorage fs(filename, cv::FileStorage::WRITE);

        fs << "iterationNr" << 100;
        fs << "strings" << "[";
        fs << "image.jpg" << "Awesomeness" << "../data/baboon.jpg";
        fs << "]";

        fs << "Mapping";
        fs << "{" <<    "One" << 1;
        fs <<           "Two" << 2 << "}";

        fs << "R" << R;
        fs << "T" << T;

        fs << "MyData" << m;
        fs.release();
        std::cout << "Write Done." << std::endl;
    }

    {   // Read
        std::cout << "\nReading " << filename << std::endl;
        cv::FileStorage fs;
        fs.open(filename, cv::FileStorage::READ);

        if (!fs.isOpened())
        {
            std::cerr << "Failed to open " << filename << std::endl;
            return EXIT_FAILURE;
        }

        int itNr;
        const std::string s_it_nr = "iterationNr";
        fs[s_it_nr] >> itNr;
        std::cout << s_it_nr << " " << itNr << std::endl;

        cv::FileNode n = fs["strings"]; // Read string sequence - Get Node
        if (n.type() != cv::FileNode::SEQ)
        {
            std::cerr << "ERROR: 'strings' is not a sequence!" << std::endl;
            return EXIT_FAILURE;
        }

        for (cv::FileNodeIterator it = n.begin(), it_end = n.end(); it != it_end; ++it) // Go through the node
            std::cout << (std::string)*it << std::endl;

        n = fs["Mapping"];
        std::cout << "Two " << (int)(n["Two"]) << "; ";
        std::cout << "One " << (int)(n["One"]) << "\n" << std::endl;

        MyData m;
        cv::Mat R, T;

        fs["R"] >> R;
        fs["T"] >> T;
        fs["MyData"] >> m;

        std::cout << "R = \n" << R << "\n" << std::endl;
        std::cout << "T = \n" << T << "\n" << std::endl;
        std::cout << "MyData = " << m << "\n" << std::endl;

        // Show default behavior for non-existing nodes
        std::cout << "Attempt to read NonExisting... (should initialize data structure with its default)" << std::endl;
        fs["NonExisting"] >> m;
        std::cout << "NonExisting = \n" << m << std::endl;

    }

    std::cout << "\nTip: try reading " << filename << " with a text editor to see serialized data." << std::endl;

    return EXIT_SUCCESS;
}
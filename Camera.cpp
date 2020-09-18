
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
using namespace cv;
using namespace std;


static void hello()
{
    cout
        << "\n-----------------------------------------" << endl
        << "Hello, this program makes Canny ege detection for your Veb camera video" << endl
        << "\nFor INCREASE threshold press I" << endl
        << "For DECREASE threshold press d" << endl
        << "Press ESC to EXIT" << endl
        << "\n\n-----------------------------------------" << endl
        << "Regards" << endl
        << "Dmitriy Utev" << endl
        << "-------------------------------------------" << endl
        << endl;
}
int main(int argc, char** argv)
{
    system("color 2");
    hello();
    Mat dst, detected_edges;
    int lowThreshold = 0;
    const int max_lowThreshold = 100;
    const int ratioo = 3;
    const int kernel_size = 3;
    const char* window_name = "Edge Map";
    Mat image, image_gray;
    VideoCapture cap(argc > 1 ? atoi(argv[1]) : 0);
    for (;;)
    {
        cap >> image;
        if (image.empty())
        {
            break;
        }
        cvtColor(image, image_gray, COLOR_BGR2GRAY);
        blur(image_gray, detected_edges, Size(3, 3));
        Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratioo, kernel_size);
        dst = Scalar::all(0);
        image.copyTo(dst, detected_edges);
        imshow(window_name, dst);
        char k = (char)waitKey(15);
        if (k == 73 or k == 105)
        {
            lowThreshold = lowThreshold + 10;
            if (lowThreshold > 100)
                lowThreshold = 100;
        }
        if (k == 68 or k == 100)
        {
            lowThreshold = lowThreshold - 10;
            if (lowThreshold < 0)
                lowThreshold = 0;
        }
        if (k == 27)
        {
            return EXIT_SUCCESS;
        }

    }
    
    return 0;
}
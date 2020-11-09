#include "opencv2/highgui.hpp"

#include <stdio.h>

using namespace cv;
using namespace std;

int main( int argc, const char** argv )
{
    const int NN = 500;

    namedWindow("image", 1);

    Mat image(NN, NN, CV_8UC3);

    for (int ii = 0; ii < NN; ++ii) {
        for (int jj = 0; jj < NN; ++jj) {
            image.at<Vec3b>(ii, jj) = Vec3b(0, ii % 256, jj % 256);
        }
    }

    imshow("image", image);
    waitKey(0);

    return 0;
}


#include <iostream>
#include <math.h>

#include <opencv2/highgui.hpp>
#include <opencv2/core/mat.hpp>
using namespace cv;

#include "robot.hh"
#include "cam.hh"

using std::cout;
using std::endl;

/*
To view the camera image in time, you could press CTRL-T in Gazebo
, choosing the Topic-"~/tankbot0/tankbot/camera_sensor/link/camera/image", 
then a Image Window will pop up, in order to view the Image in time.
*/

void
callback(Robot* robot)
{
    cout << "here2" <<endl;
    cam_show(robot->frame);

    if (!robot->frame.empty()) {
      cv::Vec3b pixel = robot->frame.at<Vec3b>(100, 400);
      cout << "pixel: " 
          << (int)pixel[0] << ","
          << (int)pixel[1] << ","
          << (int)pixel[2] << endl;
    }

    robot->set_vel(0.0, 0.0);
}

int
main(int argc, char* argv[])
{
  cout << "here1" <<endl;
  cam_init();

  cout << "making robot" << endl;
  Robot robot(argc, argv, callback);
  robot.do_stuff();

  return 0;
}

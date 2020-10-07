
#include <iostream>
#include <math.h>

#include "robot.hh"

using std::cout;
using std::endl;

// Maybe add some global state here
bool wall_follow = false;

void
do_wall_follow(Robot* robot, double range)
{
    if (robot->range < 1.0) {
        robot->set_vel(-5.0, 5.0);
        return;
    }

    if (robot->range < 1.7) {
        robot->set_vel(5.0, 5.0);
        return;
    }

    robot->set_vel(5.0, -5.0);
    wall_follow = false;

    // if (we're facing north or south)
    // we hit a doorway
}

void
callback(Robot* robot)
{
  double range = robot->range;
  if (wall_follow) {
    do_wall_follow(robot, range);
    return;
  }

  robot->set_vel(5.0, 5.0);
  wall_follow = true;
}

int
main(int argc, char* argv[])
{
    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    robot.do_stuff();

    // initialize your stuff here

    return 0;
}

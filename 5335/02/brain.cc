
#include <iostream>
#include <math.h>

#include "robot.hh"

using std::cout;
using std::endl;

const double goal_x = 20.0;
const double goal_y = 0.0;
bool done = false;

double
clamp(double xmin, double x, double xmax)
{
  if (x < xmin) {
    return xmin;
  }
  if (x > xmax) {
    return xmax;
  }
  return x;
}

void
callback(Robot* robot)
{
    /*
    cout << endl;
    cout << "robot x =" << robot->pos_x << endl;
    cout << "robot y =" << robot->pos_y << endl;
    */
    double dx = goal_x - robot->pos_x;
    double dy = goal_y - robot->pos_y;
    if (abs(dx) < 0.75 && abs(dy) < 0.75) {
        cout << "we win!" << endl;
        robot->set_vel(0.0);
        robot->set_turn(0.0);
        robot->done();
        return;
    }

    double ang = atan2(dy, dx);
    cout << "raw angle to goal =" << ang << endl;
    double da = ang - robot->pos_t;
    cout << "relative angle =" << da << endl;

    double turn = clamp(-0.5, -da, 0.5);
    cout << "planned turn =" << turn << endl;
    
    robot->set_vel(2.0);
    robot->set_turn(turn);
}

int
main(int argc, char* argv[])
{
    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    robot.do_stuff();

    return 0;
}

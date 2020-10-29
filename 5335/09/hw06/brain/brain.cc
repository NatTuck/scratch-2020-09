
#include <iostream>
#include <thread>
#include <mutex>
#include <math.h>

#include "robot.hh"
#include "viz.hh"

using std::cout;
using std::endl;
using std::mutex;
using std::lock_guard;

// fixme: needs mutex to be correct
mutex ang_lock;
float goal_ang = 0.0f;

float
ang_diff(float aa, float bb)
{
    float cc = aa - bb;
    while (cc > M_PI) {
        cc -= M_PI;
    }
    while (cc < -M_PI) {
        cc += M_PI;
    }
    return cc;
}

void
callback(Robot* robot)
{
  /*
    cout << "\n===" << endl;
    for (auto hit : robot->ranges) {
        if (hit.range < 100) {
            viz_hit(hit.range, hit.angle);
        }
        //cout << hit.range << "@" << hit.angle << endl;
    }
    */

    if (robot->ranges.size() < 5) {
        return;
    }

    float _lft = clamp(0.0, robot->ranges[2].range, 2.0);
    float fwd = clamp(0.0, robot->ranges[3].range, 2.0);
    float _rgt = clamp(0.0, robot->ranges[4].range, 2.0);
    
    float spd = fwd - 1.0;

    float tgt_ang;
    {
      lock_guard<mutex> _foo(ang_lock);
      tgt_ang = goal_ang;
    }
    
    float ang_err = ang_diff(robot->pos_t, tgt_ang);

    if (abs(ang_err) > M_PI/3.0) {
        robot->set_vel(2.0, -2.0);
    }
    else {
        robot->set_vel(spd + ang_err, spd - ang_err);
    }


    /*
    cout << "x,y,t = "
         << robot->pos_x << ","
         << robot->pos_y << ","
         << robot->pos_t << endl;
    robot->set_vel(robot->pos_t, -robot->pos_t);
    */
}

void
on_click(float xx, float yy)
{
    cout << "brain.cc: click callback" << endl;
    cout << "click @ " << xx << "," << yy << endl;

    lock_guard<mutex> _foo(ang_lock);
    goal_ang = atan2f(yy, xx);
    cout << "target angle = " << goal_ang << endl;
}

void
robot_thread(Robot* robot)
{
    robot->do_stuff();
}

int
main(int argc, char* argv[])
{
    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    std::thread rthr(robot_thread, &robot);

    return viz_run(argc, argv);
}

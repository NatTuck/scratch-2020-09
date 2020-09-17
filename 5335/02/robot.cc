#include <iostream>
#include <string>
#include <vector>

#include "robot.hh"

using std::cout;
using std::endl;
using std::string;
using std::vector;

using namespace gazebo;
using namespace gazebo::transport;

Robot::Robot(int argc, char* argv[], void (*cb)(Robot*))
    : on_update(cb), task_done(false)
{
    client::setup(argc, argv);
    node = NodePtr(new Node());
    node->Init();

    turn_pub = node->Advertise<msgs::Any>("~/teapot0/turn_cmd");
    turn_pub->WaitForConnection();

    vel_pub = node->Advertise<msgs::Any>("~/teapot0/vel_cmd");
    vel_pub->WaitForConnection();

    scan_sub = node->Subscribe(
        string("~/teapot0/teapot/rplidar_a2/link/laser/scan"),
        &Robot::on_scan,
        this,
        false
    );

    pose_sub = node->Subscribe(
        string("~/teapot0/pose"),
        &Robot::on_pose,
        this,
        false
    );

    cout << "robot created" << endl;
}

Robot::~Robot()
{
    client::shutdown();
    cout << "robot destroyed" << endl;
}

void
Robot::do_stuff()
{
    while (!task_done) {
        gazebo::common::Time::MSleep(10);
    }

    gazebo::common::Time::MSleep(100);
}

void
Robot::done()
{
    this->task_done = true;
}

void
Robot::set_vel(double vel)
{
    auto msg = msgs::ConvertAny(vel);
    vel_pub->Publish(msg);
}

void
Robot::set_turn(double turn)
{
    auto msg = msgs::ConvertAny(turn);
    turn_pub->Publish(msg);
}

void
Robot::on_scan(ConstLaserScanStampedPtr &msg)
{
    msgs::LaserScan scan = msg->scan();
    auto xs = scan.ranges();

    this->hits.clear();
    for (long ii = 0; ii < xs.size(); ++ii) {
        double range = xs[ii];
        double theta = scan.angle_min() + ii*scan.angle_step();
        this->hits.push_back(LaserHit(range, theta));
    }

    this->on_update(this);
}

void
Robot::on_pose(ConstPoseStampedPtr &msg)
{
    auto pos = msg->pose().position();
    this->pos_x = pos.x();
    this->pos_y = pos.y();

    auto rot = msg->pose().orientation();
    ignition::math::Quaternion<double> qrot(rot.w(), rot.x(), rot.y(), rot.z());
    this->pos_t = qrot.Yaw();

    this->on_update(this);
}

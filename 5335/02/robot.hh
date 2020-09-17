#ifndef ROBOT_HH
#define ROBOT_HH

#include <gazebo/gazebo_config.h>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo_client.hh>

class LaserHit {
  public:
    LaserHit()
        : range(0.0), angle(0.0)
    {
        // do nothing
    };

    LaserHit(float x, float t)
        : range(x), angle(t)
    {
        // do nothing
    }

    const float range;
    const float angle;
};

class Robot {
  public:
    void (*on_update)(Robot*);

    std::vector<LaserHit> hits;

    float pos_x;
    float pos_y;
    float pos_t;

    bool task_done;

    gazebo::transport::NodePtr node;
    gazebo::transport::PublisherPtr turn_pub;
    gazebo::transport::PublisherPtr vel_pub;
    gazebo::transport::SubscriberPtr scan_sub;
    gazebo::transport::SubscriberPtr pose_sub;

    Robot(int argc, char* argv[], void (*cb)(Robot*));
    ~Robot();

    void do_stuff();
    void done();

    void set_vel(double vel);
    void set_turn(double turn);

    void on_scan(ConstLaserScanStampedPtr &msg);
    void on_pose(ConstPoseStampedPtr &msg);
};

#endif

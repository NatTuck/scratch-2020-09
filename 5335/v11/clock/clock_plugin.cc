// Based on:
// https://github.com/osrf/gazebo/blob/gazebo11/plugins/ImuSensorPlugin.cc / .hh

#include <iostream>
using std::cout;
using std::endl;

#include "gazebo/common/Plugin.hh"
#include "gazebo/sensors/sensors.hh"
#include "gazebo/common/Events.hh"

using namespace gazebo;

class GZ_PLUGIN_VISIBLE ClockPlugin : public SensorPlugin
{
  public:
    ClockPlugin();
    virtual ~ClockPlugin();
    virtual void Load(sensors::SensorPtr _parent, sdf::ElementPtr _sdf);

  private:
    physics::WorldPtr world;
    physics::LinkPtr link;
};

GZ_REGISTER_SENSOR_PLUGIN(ClockPlugin)

/////////////////////////////////////////////////
ClockPlugin::ClockPlugin()
{
    cout << "create clock_plugin" << endl;
}

/////////////////////////////////////////////////
ClockPlugin::~ClockPlugin()
{
    cout << "destroy clock_plugin" << endl;
}

/////////////////////////////////////////////////
void
ClockPlugin::Load(sensors::SensorPtr parent, sdf::ElementPtr _sdf)
{
    cout << "load clock_plugin" << endl;

    this->world = physics::get_world(parent->WorldName());
    physics::EntityPtr entity = this->world->EntityByName(parent->ParentName());
    this->link = boost::dynamic_pointer_cast<physics::Link>(entity);

    if (!this->link) {
        gzthrow("Sensor parent is not a Link.");
    }
}

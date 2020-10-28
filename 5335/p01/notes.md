

# KSP Project Ideas

 - Mining mission to Tylo
 - Landing and Takeoff from Eve
 - General transfer script for transfers between two bodies with the same
   parent, that does single burn transfers even between different inclinations,
   using search might help.

KSP control without KerboScript

 - https://krpc.github.io/krpc/

# SLAM

Simultaneous Localization and Mapping


Localization:

 - Plan A: GPS
 
Other sensors: 

 - Wheel Encoders record how far wheels have turned
   - Problem: These aren't perfectly accurate
   - Problem: The errors just add up
 - An accelerometer measures how the robot has accelerated
   - Derivitive of acceleration is speed, sum of speed over time is position
   - Problem: These aren't perfectly accurate
   - Problem: The errors just add up
 - Magntometer can be used as compass to get heading.
   - Advantage: This is a globally correct reading.
 - Combining multiple sensors can give better results.
   - Kalman filter
   - Particle filter

More sensors: LIDAR, SONAR, Camera

 - These sensors let us see obstacles and build a map.
 - Once we have a map, we can figure out if the current sensor
   data matches our estimated position on the map.


## Project Ideas for Rover-type Robot

### Pure Gazebo

Alternate motion?

 - Flying robot?
   - Quadroter
   - Flapping wings?
 - Legged robot

What to do?

 - Solve a maze with SLAM
 - Destructive pathfinding - knock over walls
 - Robot ARM? 

More than one robot?

### Physical Robot, Probably with Gazebo Sim

Mapping and Navigation

 - Control Program?
   - Bluetooth to a computer?
   - Attach a phone to the robot with a USB cable?
     - Extra sensors!
 - SLAM?

Simple Motion Control

 - Balancing
 - + Climbing over obstacles

Stuff to do with a phone:

 - Voice commands
 - Camera
   - Follow a human
   - QR breadcrumbs 

Stuff with a remote PC:

 - Point a camera at the robot.

More than one robot?


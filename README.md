ios_simulator_sensors
=====================

A basic solution to allow the inclusion of sensors into the iOS 6 simulator. 

The way in which iOS deals with sensors has changed since iOS 5 and the old solution (https://github.com/HBehrens/accelerometer-simulator) will soon no longer works. I have updated this to work on the new iOS simulator.

This solution is simle to use and will not affect your program behaviour when it is deployed to an actual device. The simulator can either accept data streamed in from the actual device or from any script. I have also included a matlab script which I use to stream accelerometer and gyro information into the simulator. This data was captured using the Sensor Monitor application in the App store.

Usage:
====================

Just add the following files to your project:
	CMMotionManagerSim.h
	CMMotionManagerSim.m

The in the setting page, select your target, then select "Build Phases", expand "Compile Sources" and then double click on CMMotionManager.m and add the following compile option "-fno-objc-arc" without the quotes.

Now everywhere in your code where you refer to the CMMotionManager class, replace this reference with CMMotionMangerSim. Always use the CMMotionManagerSim class, even if you are compiling to the device. It will function as expected on the device.

When you want to send data to the device just send it over a UDP connection on port 10553, you can change this port number in the .m file by changing the "kAccelerometerSimulationPort" define.

The data format for each of the sensors packets is:

ACC: 0, timestamp, X, Y, Z
GYRO: 0, timestamp, X, Y, Z
MAG: 0, timestamp, X, Y, Z

where the timestamp has the format of time since 1 Jan 2001 00:00:00 not the normal Unix timestamp (time since 1970). Each packet is handled individually so if you wish to send data for 3 sensors you need to send 3 packets.

Contributions:
====================

Feel free to contribute to and distribute this code as you want. I will eventually rewrite it to use ARC but it is not nessesary at the moment.

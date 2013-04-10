ios_simulator_sensors
=====================

A basic solution to allow the inclusion of sensors into the iOS 6 simulator. 

The way in which iOS deals with sensors has changed since iOS 5 and the old solution (https://github.com/HBehrens/accelerometer-simulator) will soon no longer works. I have updated this to work on the new iOS simulator.

This solution is simle to use and will not affect your program behaviour when it is deployed to an actual device. The simulator can either accept data streamed in from the actual device or from any script. I have also included a matlab script which I use to stream accelerometer and gyro information into the simulator. This data was captured using the Sensor Monitor application in the App store.

Usage:
====================

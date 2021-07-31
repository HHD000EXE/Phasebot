# Zeroing the Legs
Before you start, please ensure the servos have distinct [servo IDs](docs/servo_id.md).

The HS1 servo has an internal concept of rotation angle. Before starting experiments, we must align the servo’s software angle with the physical angle of the leg.
1. uncomment the `zero()` function in `setup()`
2. comment out everything else in `setup()` and `loop()`
At this point, only the `zero()` function should run on startup.
3. connect and start the robot
The legs should move into their zero-ed position.
4. Find `cal` in `Legs.h` ([here](Phase_Space/libraries/Legs.h))
	- NOTE: this is bad practice. Blame Elijah for placing an implementation variable in the code.  If there are future robots, we will need to change this!
5. Adjust `cal` and restart the robot.
6. Repeat **5.** until all legs are aligned
	- current (2020 Aug 29) legs can rest on 2 points
	- zero all legs to rest both points on a level surface

![](https://github.com/Ipskie/PhaseBot/blob/master/docs/images/legs_flat.png?raw=true)
# Code Logic

##### Global Variables

- `gait` 
    - determines what [Gait](Phase_Space/libraries/Gait.h) robot adopts
- `OMEGA`
    - angular speed of the legs in RPM
- `PERIOD`
    - period of ideal leg rotation in seconds
    - derived from `OMEGA`

##### Code Logic

This is basically what PhaseBot is doing when started up:

1.  initialize connection to LSS Servos
2.  align legs to preset (e.g. bounding gait will have back legs 180 degrees out of phase with front legs)
    -   takes zeroing into account
3.  begin movement at hardcoded angular speed
4.  read in a new gait from the remote control
5.  adjust leg speed to approach correct offset for new gait
6.  repeat **4.** and **5.** indefinitely

##### BAUD Rate
Note: BAUD Rate for Arduino Serial Monitor should be [115200](https://www.robotshop.com/info/wiki/lynxmotion/view/lynxmotion-smart-servo/lss-communication-protocol/#HCommunicationSetup)
# PhaseBot

### Hardware
- Arduino Uno
- FlySky i6X Remote Control & Receiver
- [LSS HS1 Servo](https://www.robotshop.com/en/lynxmotion-smart-servo-lss-high-speed-hs1.html)

If you are setting up the servo’s for the first time, you will need to set their [servo IDs](docs/servo_id.md), and [zero the legs](docs/zero_legs.md).

### Test Section

this is for the tutorial

### Controlling the Robot

The power supply should be off and the arduino should be unplugged.

1.  Ensure the [wiring](docs/wiring.md) is correct.

2.  Turn on the power supply.
    All servos should flash the start up LED sequence ([red, yellow, green](https://www.robotshop.com/info/wiki/lynxmotion/view/lynxmotion-smart-servo/lss-button-menu/)).

3.  Plug in the Arduino.
    The robot should now start moving, and you can control it with the remote control.

The Robot's wire may get tangled in one of the legs. If this happens, press the button on the power supply to immediately kill power.

To reset and restart the robot, 

1.  Press the RESET button on the Arduino. 
2.  While the Arduino is restarting, turn on the power supply.



### Remote Control

Right Lead leg is the leading leg.

Left Lead leg is controlled by the left stick.

-   Middle position is 180 degrees out of phase

Right Hind leg is controlled by the right knob

-   Middle position is 180 degrees out of phase

Left Hind leg is controlled by the left knob

-   Middle position is 180 degrees out of phase

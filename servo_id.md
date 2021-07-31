### Hardware
You will need:

- [LSS Config](https://www.robotshop.com/info/wiki/lynxmotion/view/lynxmotion-smart-servo/lss-configuration-software/) for Windows
- an [LSS Adapter Board](https://www.robotshop.com/info/wiki/lynxmotion/view/servo-erector-set-system/ses-electronics/ses-modules/lss-adapter-board/)
- a power supply

### LSS Config Setup
1. Connect your computer to the Mini USB port on the LSS Adapter Board.
2. Connect yellow pins on the LSS Adapter Board to power supply. 
3. Supply power to the LSS Adapter Board. The green 5V power LED should turn on.
4. Connect LSS Servo to one of the 6 LSS ports on the LSS Adapter Board.

You should now be able to use the LSS Config software to connect to the servo.

The red and green USB-TX and USB-RX pins should be blinking regularly.

### Changing Servo ID
The most important function of the LSS Config software is changing the Servo's ID.
By default, the Servo ID number is 0.
1. Connect the servo to your computer's LSS Config via the steps above. You should be able to make the servo move by inputting an angle and pressing "Send".
2. Input the new servo ID in the LSS Config Software.
3. Press "Update", and wait to complete.

To verify, you can send a new angle and observe in the serial monitor (lower right hand side) the servo ID.

e.g. if I set the servo ID to **4**, and request a 3 degree angle, the command should be `#4D30`



Note: it is recommended that you label the servo with its ID number for future reference and other lab members

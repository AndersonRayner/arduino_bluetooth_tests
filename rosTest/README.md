# rosTest

Teensy software for publishing a ROS topic that can be sent via bluetooth (on Serial1) to the host computer.

## Running ROS
Use the launch file in `launch/`.  You may have to change the device port, which is defined when running `rfcomm` to connect the serial port to the bluetooth device.

## Notes for later
### General Notes
* Bluetooth chip must be configured as a slave device

###
### Starting the Bluetooth Serial on Linux
```
# rfcomm connect  <dev> <bdaddr> [channel]
sudo rfcomm connect /dev/rfcomm0 00:22:06:01:10:35 1 
```
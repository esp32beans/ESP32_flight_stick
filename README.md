# USB Flight Joystick for ESP32

This has only been tested on ESP32S3 boards. It should work on ESP32S2 boards.

The 3D joystick has the following controls.

Control |Description
--------|---------------
X       |10 bits, 0..1023
Y       |10 bits, 0..1023
Z       |8 bits, 0..255  
Throttle|8 bits, 0..255
Buttons |12 buttons
Hat     |8 way hat switch/direction pad

The HID report has been carefully chosen so it works with the Xbox Adaptive
Controller(XAC). All the other open source XAC joysticks I have seen use 8 bits
for X and Y. When used with XAC, only the X, Y, and 8 buttons are supported.
This is a limitation of the XAC.

Install this library by downloading a zip file from this repo. Use the IDE
"Add .zip library" option.

## Troubleshooting

Set "Tools->USB Mode" to "Hardware CDC and JTAG". This seems wrong but it
works when using ESP32 USB device libraries.

After uploading firmware, powering cycling and/or reseting the board is
required.

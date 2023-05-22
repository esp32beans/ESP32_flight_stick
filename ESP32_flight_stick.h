/*
MIT License

Copyright (c) 2023 esp32beans@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ESP32_FLIGHT_STICK_H_
#define ESP32_FLIGHT_STICK_H_

#include <Arduino.h>
#include "USBHID.h"
#if CONFIG_TINYUSB_HID_ENABLED

// Dpad directions
typedef uint8_t FSDirection_t;
#define FSJOYSTICK_DPAD_UP  0
#define FSJOYSTICK_DPAD_UP_RIGHT 1
#define FSJOYSTICK_DPAD_RIGHT 2
#define FSJOYSTICK_DPAD_DOWN_RIGHT 3
#define FSJOYSTICK_DPAD_DOWN 4
#define FSJOYSTICK_DPAD_DOWN_LEFT 5
#define FSJOYSTICK_DPAD_LEFT 6
#define FSJOYSTICK_DPAD_UP_LEFT 7
#define FSJOYSTICK_DPAD_CENTERED 0xF

enum FSBUTTONs {
  FSBUTTON_0 = 0,
  FSBUTTON_front = 0,
  FSBUTTON_1 = 1,
  FSBUTTON_side = 1,
  FSBUTTON_2,         // top large left
  FSBUTTON_3,         // top large right
  FSBUTTON_4,         // top small left
  FSBUTTON_5,         // top small right
  FSBUTTON_6,         // base buttons
  FSBUTTON_7,
  FSBUTTON_8,
  FSBUTTON_9,
  FSBUTTON_10,
  FSBUTTON_11,
};

// Flight sim joystick HID report layout
// Large joystick X, Y, Z (twist) axes
// 8 way hat switch
// 12 buttons (6 on the stick, 6 on the base)
// throttle slider
typedef struct __attribute__ ((packed)) {
  uint32_t x : 10;      // 0..512..1023
  uint32_t y : 10;      // 0..512..1023
  uint32_t hat : 4;
  uint32_t twist : 8;   // 0..127..255
  uint8_t buttons_a;
  uint8_t slider;       // 0..255
  uint8_t buttons_b;
} FSJoystick_Report_t;

class ESP32_flight_stick: public USBHIDDevice {
  public:
    ESP32_flight_stick(void);
    void begin(void);
    void end(void);
    void loop(void);
    bool write(void);
    bool write(void *report);
    void press(int button);
    void release(int button);
    inline void releaseAll(void) { _report.buttons_a = _report.buttons_b = 0;  }
    inline void buttons(uint16_t b) {
      _report.buttons_a = b & 0xFF;
      _report.buttons_b = (b & 0x0F00) >> 4;
    }
    inline void xAxis(int a) { _report.x = a; }
    inline void yAxis(int a) { _report.y = a; }
    inline void twist(uint8_t a) { _report.twist = a; }
    inline void slider(uint8_t a) { _report.slider= a; }
    inline void dPad(FSDirection_t d) { _report.hat = d; }
    void dPad(bool up, bool down, bool left, bool right);

    // internal use
    uint16_t _onGetDescriptor(uint8_t* buffer);
  private:
    USBHID hid;
    FSJoystick_Report_t _report;
    uint32_t startMillis;
};

#endif  // CONFIG_TINYUSB_HID_ENABLED
#endif  // ESP32_FLIGHT_STICK_H_

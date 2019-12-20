/*
 *
 * Project: https://github.com/dchote/fanatecWheelUSB
 * Author: Daniel Chote
 *
 * Modified from the Teensyduino Core Library and pulling in darknao's changes
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2013 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef FANATECjoystick_h_
#define FANATECjoystick_h_

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
  
#define LIGHTS_ENDPOINT 1
#define LIGHTS_SIZE 8
#define LIGHTS_INTERVAL 16
  
int fanatec_joystick_send(void);
extern uint8_t fanatec_joystick_data[32];

int fanatec_lights_recv(void *buffer, uint32_t timeout);
int fanatec_lights_available(void);

#ifdef __cplusplus
}
#endif

// C++ interface
#ifdef __cplusplus
class fanatec_joystick_class
{
  private:
    static uint8_t manual_mode;
  public:
    void begin(void) { }
    void end(void) { }
    
    void button(uint8_t button, bool val) {
        if (--button >= 88) return;
        if (button >= 80) {
            if (val) fanatec_joystick_data[10] |= (0x1 << (button-80));
            else fanatec_joystick_data[10] &= ~(0x1 << (button-80));
        } else if (button >= 72) {
            if (val) fanatec_joystick_data[9] |= (0x1 << (button-72));
            else fanatec_joystick_data[9] &= ~(0x1 << (button-72));
        } else if (button >= 64) {
            if (val) fanatec_joystick_data[8] |= (0x1 << (button-64));
            else fanatec_joystick_data[8] &= ~(0x1 << (button-64));
        } else if (button >= 56) {
            if (val) fanatec_joystick_data[7] |= (0x1 << (button-56));
            else fanatec_joystick_data[7] &= ~(0x1 << (button-56));
        } else if (button >= 48) {
            if (val) fanatec_joystick_data[6] |= (0x1 << (button-48));
            else fanatec_joystick_data[6] &= ~(0x1 << (button-48));
        } else if (button >= 40) {
            if (val) fanatec_joystick_data[5] |= (0x1 << (button-40));
            else fanatec_joystick_data[5] &= ~(0x1 << (button-40));
        } else if (button >= 32) {
            if (val) fanatec_joystick_data[4] |= (0x1 << (button-32));
            else fanatec_joystick_data[4] &= ~(0x1 << (button-32));
        } else if (button >= 24) {
            if (val) fanatec_joystick_data[3] |= (0x1 << (button-24));
            else fanatec_joystick_data[3] &= ~(0x1 << (button-24));
        } else if (button >= 16) {
            if (val) fanatec_joystick_data[2] |= (0x1 << (button-16));
            else fanatec_joystick_data[2] &= ~(0x1 << (button-16));
        } else if (button >= 8) {
            if (val) fanatec_joystick_data[1] |= (0x1 << (button-8));
            else fanatec_joystick_data[1] &= ~(0x1 << (button-8));
        } else {
            if (val) fanatec_joystick_data[0] |= (0x1 << (button));
            else fanatec_joystick_data[0] &= ~(0x1 << (button));
        }
        if (!manual_mode) fanatec_joystick_send();
    }

    void X(unsigned int val) {
        fanatec_joystick_data[11] = val & 0xFF;
        if (!manual_mode) fanatec_joystick_send();
    }

    void Y(unsigned int val) {
        fanatec_joystick_data[12] = val & 0xFF;
        if (!manual_mode) fanatec_joystick_send();
    }

    void clutch1(unsigned int val) {
        fanatec_joystick_data[13] = val & 0xFF;
        if (!manual_mode) fanatec_joystick_send();
    }

    void clutch2(unsigned int val) {
        fanatec_joystick_data[14] = val & 0xFF;
        if (!manual_mode) fanatec_joystick_send();
    }

    inline void hat(int val) {
        fanatec_joystick_data[15] = val & 0xFF;
        if (!manual_mode) fanatec_joystick_send();
    }

    void setWheel(unsigned int val) {
        fanatec_joystick_data[29] = val & 0xFF;
        if (!manual_mode) fanatec_joystick_send();
    }

    void useManualSend(bool mode) {
        manual_mode = mode;
    }
    void send_now(void) {
        fanatec_joystick_send();
    }

    int available(void) {return fanatec_lights_available(); }
    int recv(void *buffer, uint16_t timeout) { return fanatec_lights_recv(buffer, timeout); }
};

fanatec_joystick_class fJoystick;
uint8_t fanatec_joystick_class::manual_mode = 0;

#endif // __cplusplus

#endif // FANATECjoystick_h_
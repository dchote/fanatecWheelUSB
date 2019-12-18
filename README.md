# fanatecWheelUSB
USB controller adapter based on the TeensyLC to allow direct USB support for Fanatec Wheel Rims.

This firmware can convert any Fanatec CSW Steering Wheel to a **standalone USB version**, so you can use it with any other wheel base, like an OpenSimWheel (OSW), or SimXperience Accuforce.

## Supported Hardware
This firmware has been developed and tested on a **Teensy LC** but should work with any other compatible hardware.  
The only requirement so far, is at least 1 SPI connectivity available.

### Shopping List
#### USB version
- Fanatec CSW rim (obviously)
- [Teensy LC](https://www.pjrc.com/teensy/teensyLC.html) : **~12$**

### Pinout & schematics
#### Fanatec Plug
![Fanatec Round Plug](http://i.imgur.com/yLSG0Jsm.jpg)

1. MISO
2. MOSI
3. GND
4. 5v
5. GND
6. SCK
7. 3v3
8. CS
9. USB charge 5v*
10. -
11. DataPort1*
12. USB charge GND*
13. DataPort2*

** These pin are only used on the Universal Hub and don't need to be connected for this conversion*

#### Matching pin for Formula / BMW / Porsche ####
![Porsche plug pinout](http://i.imgur.com/WazqNZlm.jpg)

#### Matching pin for Universal Hub / CSL P1 ####
![UNI Hub pinout](http://i.imgur.com/pC5L8Lum.jpg)

#### Wiring Schematics
![Wiring schematics](https://phunk.me/Y86946)
This is the same schematics for Bluetooth and USB version.  
Just forget about the Adafruit Power Boost (upper left) and the Bluegiga WT12 (bottom right) for the USB version.  
There is also room for 8 extra buttons on pin 2 to 9 (common ground) if you need more inputs.

## Compatible Wheels
All CSW / CSL rims are working with this conversion. That includes:

- BMW M3 GT2
- Formula Black/Carbon
- Porsche 918 RSR
- Universal Hub (**both version**)
- CSL P1 (both version)

## Special note for the Universal Hub and Extra buttons ##
The Universal HUB brings you no more than 38 buttons (46 with the extra). The Windows Control Panel will only show you 32, but don't worry, every modern DirectX games can go up to 128.

If you need to test all of them, I suggest you to use [JoystickTest](http://www.planetpointy.co.uk/joystick-test-application/) as it can see them all.

## Software/Driver Required
This is detected has a HID device on Windows, so no specific drivers are required.  
It's is fully compatible with Fanaleds, which is required to get all feedback indicator working (LEDs, display and motors, if any).  
Alternatively, you can use SLIMax Manager Pro, which is free if used with any Fanatec wheel.

## Supported wheel features
Well... Everything.

## Original Project
This is a fork of @darknao's btClubSportWheel project found here: https://github.com/darknao/btClubSportWheel

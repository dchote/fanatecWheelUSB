# fanatecWheelUSB
USB controller adapter based on the TeensyLC/Teensy3 to allow direct USB support for Fanatec Wheel Rims.

This firmware can convert any Fanatec CSW Steering Wheel to a **standalone USB version**, so you can use it with any other wheel base, like an OpenSimWheel (OSW), or SimXperience Accuforce.

## Supported Hardware
This firmware has been developed and tested on a **Teensy LC** and **Teensy 3.2** but should work with any other compatible hardware.  
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

## Building
Currently the Makefile is setup to build on MacOS, building will eventually be done using a container and Github Actions.
Please ensure you have the latest Arduino IDE and Teensyduino (https://www.pjrc.com/teensy/td_download.html) installed.

You will need to copy the files from `core_files` in to your teensy3 cores folder (`hardware/teensy/avr/cores/teensy3`). Please create a copy of the existing files so you can revert if needed.

To build in the Arduino IDE you will need to edit `hardware/teensy/avr/boards.txt` and add the following:
```
teensy35.menu.usb.fanatec=Fanatec CSW
teensy35.menu.usb.fanatec.build.usbtype=FANATEC_CSW
teensy31.menu.usb.fanatec=Fanatec CSW
teensy31.menu.usb.fanatec.build.usbtype=FANATEC_CSW
teensy30.menu.usb.fanatec=Fanatec CSW
teensy30.menu.usb.fanatec.build.usbtype=FANATEC_CSW
teensyLC.menu.usb.fanatec=Fanatec CSW
teensyLC.menu.usb.fanatec.build.usbtype=FANATEC_CSW
``` 
Open in the project in the Arduino IDE and configure the following under the `Tools` menu.
- Board: `Teensy LC` or `Teensy 3.2/3.1`
- USB Type:  `Fanatec CSW`.  
- CPU Speed: `24mhz`
- Optimize: `Smallest Code`


The project should then build.

## Original Project
This is a fork of @darknao's btClubSportWheel project found here: https://github.com/darknao/btClubSportWheel

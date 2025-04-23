# Matoha Plastell Parser

[Plastell documentation](https://matoha.com/documentation)

## Plastell Raspberry Pi / Test rig
![Test rig photo](images/Plastell_test_rig.png)

Connect via USB

Plastell is implemented with an ESP32 and the USB cable presents as USB/CDC/Serial
Toggling DTR pin, will start the Plastell unit into logging mode.

We then parse the logging with a Python script, which is started with a udev rule on USB insertion.
Sample logs [here](plastel_log_sample.txt)

The python script 'plastell.py' is started automatically each time the Plastell unit is plugged into the Raspberry Pis USB port with a udev rule; [udev rule](udev-rules.txt)

![Raspbery Pi Parts](images/RaspberryPi3_parts.png)

Pinout for serial output.
Serial output via 4 pin JST-PH connector 3.3v , 9600 baud
 - Black = Ground
 - White = TX
 - Yellow = RX
![UART photo](images/SerialPortPins.png)

Written as proof of concept for Kiwifil New Zealand

By Matt Way of Econode NZ April 2025

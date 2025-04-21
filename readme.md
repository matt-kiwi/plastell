#Matoha Plastell Parser

[Plastell documentation](https://matoha.com/documentation)

Connect via USB

Plastell is implemented with an ESP32 and the USB cable presents as USB/CDC/Serial
Toggling DTR pin, will start the Plastell unit into logging mode.

We then parse the logging with a Python script, which is started with a udev rule on USB insertion.
Sample logs [here](udev-rules.txt)

Written as proof of concept for Kiwifil New Zealand

By Matt Way of Econode NZ

#!/usr/bin/env python3
from gpiozero import LED
import serial
import re
import time
global lastLine

lastLine = ""

#Threshold of what we include as a valid threshold
certaintyThreshold = 0.5

led_red = LED(22)
led_yellow = LED(23)
led_green = LED(24)

# Arduino serial port
serialOutPort = '/dev/ttyS0'

# plasTellPort = '/dev/cu.usbmodem14201'
plasTellPort = '/dev/ttyACM0'

def LED_Plastic( msgPrefix ):
    led_green.off()
    led_red.off()
    led_yellow.off()
    if msgPrefix == 1:
        led_green.on()
        return
    if msgPrefix == 2:
        led_yellow.on()
        return
    led_red.on()

def Bills_LED_Dance():
    for i in range(1, 3):
        led_green.on()
        led_red.off()
        led_yellow.off()
        time.sleep(0.5)
        led_green.off()
        led_yellow.on()
        time.sleep(0.5)
        led_yellow.off()
        led_red.on()
        time.sleep(0.5)
        led_red.off()

def parsePlastic(buff):
    global lastLine
    # Work out if this is a spit line then rebuild it.
    if "Top hit" in lastLine:
        buff = lastLine + ' ' + buff
    res = re.search(r'^MatohaMain:.*Top hit (.*) \((\d\.\d\d)\).', buff)
    if res:
        plasticType = res.group(1).replace(' or ','/')
        certainty = float(res.group(2))
        # msgPrefix 0=Start, 1=High certainty PLA, 2=High certainty PETG, 3=No read / false
        msgPrefix = 3
        # Work out go / no go and if PLA/PET
        if certainty >= certaintyThreshold and 'PLA' in plasticType:
            msgPrefix = 1
        if certainty >= certaintyThreshold and 'PETG' in plasticType:
            msgPrefix = 2

        msg =  f"{msgPrefix}{plasticType} {certainty}\n"
        print( "Found:: "+msg)
        serOut.write( msg.encode() )
        LED_Plastic(msgPrefix)


def stripLogPrefix(line):
    logStrip = re.compile(r'^W \(\d*\) ')
    return logStrip.sub('',line)

def escape_ansi(line):
    ansi_escape =re.compile(r'(\x9B|\x1B\[)[0-?]*[ -\/]*[@-~]')
    return ansi_escape.sub('', line)

def logLine(line):
    print( line )

##
## Start processing here
##
print(f"Connecting to device ({plasTellPort}). Ctrl + C to exit.")


serOut = serial.Serial(serialOutPort, 9600, timeout=1)
time.sleep(2)
serOut.write(b'0Start\n')
Bills_LED_Dance()

with serial.Serial(plasTellPort, 115200, timeout=1) as ser:
    # Reset the device
    ser.setRTS(True)
    ser.setDTR(False)
    ser.setRTS(False)

    # Read the serial port and print the output until terminated by Ctrl+C
    while 1:
        try:
            line = ser.readline().decode("utf-8").strip()
            if line:
                line = stripLogPrefix(escape_ansi(line))
                logLine( line )
                if line.endswith(")."):
                    parsePlastic(line)
                lastLine = line
        except UnicodeDecodeError:
            pass


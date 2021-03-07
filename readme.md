# Introduction
The idea comes from Pedro ON7WP who was trying to use an older Icom transceiver for remote control with Icom's RS-BA1 software.
The Icom IC275 is a VHF allmode rig, but lacks TX/RX switching via the CI-V commands.
However, RS-BA1 sends the TX command regardless the transceiver. It uses the 0x00 addres (all transceivers) to send the TX commando.

Pedro's Github : https://github.com/on7wp/ICOM-CI-V-Arduino-Monitor

# String in detail
I just monitor the data sent from the host (computer) : 
- TX = FE FE 00 E0 1C 00 01 FD
- RX = FE FE 00 E0 1C 00 00 FD

# Serial library
One of my goals was to eliminate the use of an older RS232 port. The CI-V port is 5V TTL compatible. You can build the level converter with
the famous MAX232 and a USB <> RS232 adaptor. But the Arduino has already the hardware. By creating a second serial port in code you can eliminate both MAX232 and USB adaptor.

But I ran into problems when I tried to echo both devices to each other. Apparantly the standard Software Serial library is interrupt driven or something like that.
I think i got timing issues. I used AltSoftSerial to have a working software serial port with better timing. 

**Attention** : Read the site, the ports this library uses are locked on D8 (rxd) and D9 (txd) for the Arduino Nano.

# Interface
![](https://github.com/ON3JT/Arduino-CI-V/blob/master/info/interface.jpg)

# Other uses
This code is also tested with HRD v5.24.0.36 and my Icom IC756. Remote control works as normal. TX is not available (blame HRD :-)).
Omnirig, hmm, I made a custom ini file, seems to work with the client programm, but fails in real use (JS8call for example).


# Resources
More details can be found :
- https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
- https://github.com/darkbyte-ru/ICOM-CI-V-cat
- https://www.qsl.net/on7eq/projects/arduino_icom_ci-v_proxy.htm
- https://arduino.stackexchange.com/questions/77230/issues-with-arduino-uno-printing-repeated-double-on-serial-monitor
- https://create.arduino.cc/projecthub/ddufault/external-s-meter-on-icom-radios-with-ci-v-port-d4e783

******

# Introduction
The idea comes from Pedro ON7WP whos was trying to use an older Icom transceiver for remote controle with Icom's RS-BA1 software.
The Icom IC275 is a VHF allmode rig, but lacks TX/RX switching via the CI-V commands.
However, RS-BA1 sends the TX command regardless the transceiver. It uses the 0x00 addres (all transceivers) to send the TX commando.

# TX string in detail

# Serial library
One of my goals was to eliminate the use of an older RS232 port. The CI-V port is 5V TTL compatible. You can build the level converter with
the famous MAX232 and a USB <> RS232 adaptor. But the Arduino has already the hardware. By creating a second serial port in code you can eliminate 
both MAX232 and USB adaptor.

But I ran into problems when I tried to echo both devices to each other. Apparantly the standard Software Serial library is interrupt driven or something like that.
I think i got timing issues.

# Interface
![](https://github.com/ON3JT/Arduino-CI-V/info/interface.jpg)

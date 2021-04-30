# FPC-024
Flytech FCP-024 / FT8501101 8255 ISA board sample code and docs

# Warning in the uswer manual there is an error CN1 pin 22 and 21 are swapped:

# pin 22 is PC6

# pin 21 is PC7

![FCP-024 photo ](/fpc-024.jpg)

I bought this card in 1998 and never use it, now I have time for play with it.

The card has two 8255 system interface and one 8253 timer.

There are 16 leds connected to the A ports of the two 8255.

I putted it in an old pc that has ISA bus and write some c user space code.

In the pdf manual you can find bord adresses and info.

# Direct port acess

On the 8255_direct_port_acess directory there are some direct port access program from userspace.

## Program that need root privileges

On the 8255_[12]_[ABC] directory you can find programs that blink single pin using out and inp funtions.

On the 8255 there are some program that blink all leds and power off all leds with out and inp functions.

## Program that should work withouth root privileges

On the devport directory there is a program that use the /dev/port device, you can run it without root privileger but you must:

1. change /dev/port permission to allow group write, sudo chmod g+w /dev/port
2. add you user to kmem group
3. add the cap_sys_rawio to your program, see devport.sh for info

if you have problems run it with root privileges...

## To compile all program

1. chmod +x compile.sh
2. chmod +x devport/devport.sh 
3. ./compile.sh

# Comedi linux driver and library

In the comedi directory you will find instructions to install comedi and comedilib from https://github.com/Linux-Comedi and how use it with the board. 

## Tested with slackware 14.2 on a pentium pc with isa bus.

# FPC-024
Flytech FCP-024 8255 ISA board sample code and docs

I bought this card in 1998 and never use it, now I have time for play with it.
The card has two 8255 system interface and one 8253 timer.
There are 16 leds connected to the A ports of the two 8255.
I putted it in an odl pc that has ISA bus and write some c code.

In the pdf manual you can find bord adresses and info.

Program that need root privileges:
On the 8255_[12]_[ABC] directory you can find prorams that blink single ports using out adn inp funtions.
On the 8255 there are some program that blink all leds and power off all leds with out and inp functions.

Program that should work withouth root privileges:
On the devport directory there is a program that use the /dev/port device, you can run it without root privileger but you must
1. change /dev/port permission to allow group write, sudo chmod g+w /dev/port
2. add you user to kmem group
3. add the cap_sys_rawio to your program, see devport.sh for info
if you have problems run it with root privilege...

To compile all program
1. chmod +x compile.sh
2. chmod +x devport/devport.sh 


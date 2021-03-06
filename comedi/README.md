# Download and install comedi drivers and comedilib library.

These drivers are for data acquisition cards that use 8255 and some others chip.

With these driver and library you can setup the three 8255 port on mode 0 as input or output, and power on/of sigle pins or read them.

I installed them from sources in a slackware 14.2 32 bit PC.

I prefer slackware 14.2 because the mainboard must have an isa bus, and is old.

## Installation of comedi kernel modules

Install the slackware and all buid tools.

Mount the slackware cd and nstall the package k/kernel-source-4.4.14_smp-noarch-1.txz

Copy the files from /usr/src/linux-4.4.14/ to your home

```cp /usr/src/linux-4.4.14 /home/yourhome```

copy your kernel config on /home/yourhome/linux-4.4.14

```zcat /proc/config.gz > /home/yourhome/linux-4.4.14/.config```

in that directory run

```make oldconfig```

```make modules_prepare```

download the comedi package from https://github.com/Linux-Comedi/comedi/ to your home and unzip it in

```/home/yourhome/linux-4.4.14/comedi-master```

from that directory run the

```./autogen.sh```

then you can set port A of the first 8255 as uotput

```./dio 1 -s 0 -c 0```

and power on the first led

```./outp 1 -s 0 -c 0```

then read the comedilib manual and go...
then run the configure script

```./configure --with-linuxdir=/home/yourhome/linux-4.4.14/```

and compile the modules with

```make```

install them with

```sudo make install```

## Instalaltion of comedilib

download the comedilib package from https://github.com/Linux-Comedi/comedilib/ to your home and unzip it in

```/home/yourhome/linux-4.4.14/comedi-master```

from that directory run the

```./autogen.sh```

then configure the package with

```./configure --with-udev-hotplug=/lib --sysconfdir=/etc```

and compile the library with

```make```

install them with

```sudo make install```

## Load the module and test it

load the comedi module with the commands

```sudo modprobe comedi comedi_num_legacy_minors=1```

that create the device driver

```/dev/comedi0```

and then load the 8255 module

```sudo modprobe 8255```

then configure the board with

```sudo comedi_config /dev/comedi0 8255 0x1B0,0x1B4```

my board has two 8255 at adresses **0x1B0,0x1B4**, check your board config

go to /home/yourhome/comedilib-master/demo and run some test programs

```./board_info```

```overall info:
  version code: 0x00074c
  driver name: 8255
  board name: 8255
  number of subdevices: 2
subdevice 0:
  type: 5 (digital I/O)
  flags: 0x00030000
  number of channels: 24
  max data value: 1
  ranges:
    all chans: [0,5]
  command:
    not supported
subdevice 1:
  type: 5 (digital I/O)
  flags: 0x00030000
  number of channels: 24
  max data value: 1
  ranges:
    all chans: [0,5]
  command:
    not supported
```

you can set first 8255 port A as output

```./dio 1 -s 0 -c 0```

and power on the first pin of port A
 
```./outp 1 -s 0 -c 0```

and power off it

```./outp 0 -s 0 -c 0```

and read comedilib documentatio going next!

Remember that pin numbers goes from 0 to 23, 

Note that you can only change port direction input or outpub by group of ports, all these command has the same effect

```
./dio 1 -s 0 -c 0
./dio 1 -s 0 -c 1
./dio 1 -s 0 -c 2
./dio 1 -s 0 -c 3
./dio 1 -s 0 -c 4
./dio 1 -s 0 -c 5
./dio 1 -s 0 -c 6
./dio 1 -s 0 -c 7
```

set pin 0 t0 7 to output, **8** pin group

```
./dio 1 -s 0 -c 8
   ...
   ```

set pin 8 t0 15 to output, **8** pin group

```
./dio 1 -s 0 -c 16
   ...
   ```

set pin 16 t0 19 to output, **4** pin group

```
./dio 1 -s 0 -c 20
   ...
   ```

set pin 20 t0 23 to output, **4** pin group

## Auto load module

edit the file

```/etc/rc.d/rc.modules.local```

for on boot module loading, appending

```
/sbin/modprobe comedi
/sbin/modprobe 8255
```

add the file

```/etc/modprobe.d/comedi.conf```

for on boot /dev/comedi0 creation, with content

```options comedi comedi_num_legacy_minors=1```

edit file

```/etc/rc.d/rc.local```

for on boot board setup, appending

```/usr/local/sbin/comedi_config /dev/comedi0 8255 0x1B0,0x1B4```

reboot, and your board will be ready

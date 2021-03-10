/*
* example.c: very simple example of port I/O
*
* This code does nothing useful, just a port write, a pause,
* and a port read. Compile with `gcc âˆ’O2 âˆ’o example example.c',
* and run as root with `./example'.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>
#include <time.h>

/* first 8255 */
#define I8255PORT1A 0x1B0
#define I8255PORT1B 0x1B1
#define I8255PORT1C 0x1B2
#define I8255CONTROL1 0x1B3

/* second 8255 */
#define I8255PORT2A 0x1B4
#define I8255PORT2B 0x1B5
#define I8255PORT2C 0x1B6
#define I8255CONTROL2 0x1B7 /* lp1 */

/* 8253 */
#define I8253COUNTER1 0x1B8
#define I8253COUNTER2 0x1B9
#define I8253COUNTER3 0x1BA
#define I8253CONTROL 0x1BB /* lp1 */

#define DELAY 100000

#define PORTS 12

#define CONTROLBITS 0b10000000 // mode 0 all outputs
//#define CONTROLBITS 0b10000010 // mode 0 port AC output port B input


int main()
{
	/* Get access to the ports */
	if (ioperm(I8255PORT1A, PORTS, 1)) {
		perror("ioperm"); 
		exit(1);
	}
	/* Set the data signals (D0ˆ’7) of the port to all low (0) */
	outb(CONTROLBITS, I8255CONTROL1);
	outb(0, I8255PORT1A);
	 
	outb(CONTROLBITS, I8255CONTROL2);
	outb(0, I8255PORT2A);

	/* Sleep for a while (100 ms) */
//	usleep(100000);
	/* Read from the status port (BASE+1) and display the result */
	printf("status of PORT1A: %d\n", inb(I8255PORT1A));
	printf("status of PORT1B: %d\n", inb(I8255PORT1B));
	printf("status of PORT1C: %d\n", inb(I8255PORT1C));
	printf("status of CONTROL1: %d\n", inb(I8255CONTROL1));

	printf("status of PORT2A: %d\n", inb(I8255PORT2A));
        printf("status of PORT2B: %d\n", inb(I8255PORT2B));
        printf("status of PORT2C: %d\n", inb(I8255PORT2C));
        printf("status of CONTROL2: %d\n", inb(I8255CONTROL2));

	printf("status of I8253COUNTER1: %d\n", inb(I8253COUNTER1));
        printf("status of I8253COUNTER2: %d\n", inb(I8253COUNTER2));
        printf("status of I8253COUNTER3: %d\n", inb(I8253COUNTER3));
        printf("status of I8253CONTROL: %d\n", inb(I8253CONTROL));
	
	/* We don't need the ports anymore */
	if (ioperm(I8255PORT1A, PORTS, 0)) {
		perror("ioperm");
		exit(1);
	}
	exit(0);
}
/* end of example.c */

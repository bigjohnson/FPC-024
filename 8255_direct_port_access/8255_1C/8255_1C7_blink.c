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
#define I8255_1_PORT_A 0x1B0
#define I8255_1_PORT_B 0x1B1
#define I8255_1_PORT_C 0x1B2
#define I8255_1_CONTROL 0x1B3

/* second 8255 */
#define I8255_2_PORT_A 0x1B4
#define I8255_2_PORT_B 0x1B5
#define I8255_2_PORT_C 0x1B6
#define I8255_2_CONTROL 0x1B7 /* lp1 */

/* 8253 */
#define I8253_COUNTER_1 0x1B8
#define I8253_COUNTER_2 0x1B9
#define I8253_COUNTER_3 0x1BA
#define I8253_CONTROL 0x1BB /* lp1 */

#define DELAY 100000

#define PORTS 12

#define CONTROLBITS 0b10000000 // mode 0 all outputs
//#define CONTROLBITS 0b10000010 // mode 0 port AC output port B input


int main()
{
	/* Get access to the ports */
	if (ioperm(I8255_1_PORT_A, PORTS, 1)) {
		perror("ioperm"); 
		exit(1);
	}
	/* Set the data signals (D0ˆ’7) of the port to all low (0) */
	outb(CONTROLBITS, I8255_1_CONTROL);
	outb(0, I8255_1_PORT_A);
	outb(0, I8255_1_PORT_B);
        outb(0, I8255_1_PORT_C);
 
	outb(CONTROLBITS, I8255_2_CONTROL);
	outb(0, I8255_2_PORT_A);
	outb(0, I8255_2_PORT_B);
        outb(0, I8255_2_PORT_C);
	while(1) {
			outb(128, I8255_1_PORT_C);
			usleep(DELAY);
			outb(0, I8255_1_PORT_C);
                        usleep(DELAY);
	
	}

	/* Sleep for a while (100 ms) */
//	usleep(100000);
	/* Read from the status port (BASE+1) and display the result */
	printf("status of PORT1A: %d\n", inb(I8255_1_PORT_A));
	printf("status of PORT1B: %d\n", inb(I8255_1_PORT_B));
	printf("status of PORT1C: %d\n", inb(I8255_1_PORT_C));
	printf("status of CONTROL1: %d\n", inb(I8255_1_CONTROL));

	printf("status of PORT2A: %d\n", inb(I8255_2_PORT_A));
        printf("status of PORT2B: %d\n", inb(I8255_2_PORT_B));
        printf("status of PORT2C: %d\n", inb(I8255_2_PORT_C));
        printf("status of CONTROL2: %d\n", inb(I8255_2_CONTROL));

	printf("status of I8253_COUNTER_1: %d\n", inb(I8253_COUNTER_1));
        printf("status of I8253_COUNTER_2: %d\n", inb(I8253_COUNTER_2));
        printf("status of I8253_COUNTER_3: %d\n", inb(I8253_COUNTER_3));
        printf("status of I8253_CONTROL: %d\n", inb(I8253_CONTROL));
	
	/* We don't need the ports anymore */
	if (ioperm(I8255_1_PORT_A, PORTS, 0)) {
		perror("ioperm");
		exit(1);
	}
	exit(0);
}
/* end of example.c */

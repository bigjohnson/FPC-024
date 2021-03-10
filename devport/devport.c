/*
 *   LQr_jr.c   ---  peek tool for IO
 */
#include    <stdio.h>
#include    <stdlib.h>
//#include    <sys/types.h>
//#include    <sys/stat.h>
#include    <fcntl.h>
#include    <unistd.h>
#include    <time.h>

/* first 8255 */
#define I8255PORT1A 0x1B0
#define I8255PORT1B 0x1B1
#define I8255PORT1C 0x1B2
#define I8255CONTROL1 0x1B3

/* second 8255 */
#define I8255PORT2A 0x1B4
#define I8255PORT2B 0x1B5
#define I8255PORT2C 0x1B6
#define I8255CONTROL2 0x1B7

/* 8253 */
#define I8253COUNTER1 0x1B8
#define I8253COUNTER2 0x1B9
#define I8253COUNTER3 0x1BA
#define I8253CONTROL 0x1BB

#define CONTROLBITS 0b10000000 // mode 0 all outputs
//#define CONTROLBITS 0b10000010 // mode 0 port AC output port B input

#define DELAY 100000

void scrivi (int iofd, unsigned char ioByte, unsigned int ioAddr) {
        printf("writing %02X at ioAddr %04X\n", ioByte, ioAddr);
	off_t status = lseek( iofd, ioAddr, SEEK_SET );
        if ( status >= 0 ) {
            printf("lseek status for %04X is %04X\n", ioAddr, status);
        } else {
            printf("lseek error for %04X\n", ioAddr);
            exit(2);
        }
        status = write( iofd, &ioByte, 1);
        if ( status < 0 ) {
            printf("write error for %04X\n", ioAddr);
            exit(3);
        } else {
            printf("write %d byte at address %04X\n", status, ioAddr);
        }
	printf("\n");
}

int main( int argc, char *argv[] ){

int iofd;
unsigned char ioByte;
//unsigned int ioAddr = 0x1B0;
off_t status;

//    sscanf( argv[1], "%X", &ioAddr );
    iofd = open( "/dev/port", O_RDWR );
    if ( iofd >= 0 ) {
        scrivi(iofd, CONTROLBITS, I8255CONTROL1);
        scrivi(iofd, 0, I8255PORT1A);
        scrivi(iofd, 0, I8255PORT1B);
        scrivi(iofd, 0, I8255PORT1C);
	scrivi(iofd, CONTROLBITS, I8255CONTROL2);
        scrivi(iofd, 0, I8255PORT2A);
        scrivi(iofd, 0, I8255PORT2B);
        scrivi(iofd, 0, I8255PORT2C);

        for (unsigned int i=1; i <= 32768; i<<=1) {
             scrivi(iofd, i, I8255PORT1A);
             scrivi(iofd, i>>8, I8255PORT2A);
             usleep(DELAY);
        }

        scrivi(iofd, 0, I8255PORT2A);
        exit(0);
    } else {
	printf("Error cannot open /dev/port\nYour user in kmem group\nAnd you must enable cap_sys_rawio on devport program!\nAnd also /dev/port must be writable by group\nOr simply run as root...\n");
	exit(1);
    }
}

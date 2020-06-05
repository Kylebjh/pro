//-------| lib/main.h |-------//
#ifndef	MAIN_H
#define	MAIN_H 


#include <stdio.h>		// printf(), scanf(), fprintf()
#include <fcntl.h>		// open()
#include <unistd.h>		// close(), off_t , usleep()
#include <sys/mman.h>	// mmap(), munmap()
#include <stdlib.h> 	// exit()
#include <string.h>		// strlen()


#include "ieb.h"
#include "led.h"
#include "dot.h"
#include "fnd.h"
#include "clcd.h"
#include "keypad.h"



typedef enum {
	FALSE = 0,
	TRUE  = 1
} truth_t;

typedef enum {
	ERROR	= -1,
	SUCCESS	= 0
} error_t;

typedef union {
	unsigned char all;
	struct {
		unsigned char  led : 1;
		unsigned char  dot : 1;
		unsigned char  fnd : 1;
		unsigned char clcd : 1;
		unsigned char exit : 1;
	};
} seclection_t;

int main();
short * mapper(off_t offset, int prot);
void unmapper();
void emergency_closer();

truth_t logic();
void select_mode();
void input_mode();


#endif

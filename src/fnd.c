//-------| src/fnd.c |-------//
#include "fnd.h"


static unsigned short fnd_hexadecimal[16] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F  // 3
};

static short * fnd[MAX_FND];

void init_fnd(short * address[]) {
	   int i;
	   for( i=0; i<MAX_FND; i++ ) {
		      fnd[i] = address[i];
	   }
}

void fnd_clear() {
	 int i;
	 for(i=0; i<MAX_FND; i++){
		    *fnd[i] = 0;
	}
}

void fnd_all() {
	  int i;
	  for(i=0; i<MAX_FND; i++){
		    *fnd[i] = 0xFF;
	  }
}

void fnd_write(int hexadecimal, int fnd_num) {
	 *fnd[fnd_num] = fnd_hexadecimal[hexadecimal];
}

void fnd_hexa_number(unsigned long number) {
	 int i;
	 for(i=0; i<MAX_FND; i++){
		   fnd_write( (short)((number-1) & 0xF), i);
		   number = number >> 4;
	}
}

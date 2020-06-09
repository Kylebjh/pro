//-------| lib/keypad.h |-------//
#ifndef	KEYPAD_H
#define	KEYPAD_H

#include <stdio.h>
#include <string.h>
#include "led.h"

#define MAX_KEY_COL 4
#define MAX_KEY_ROW 4

void init_keypad(short * address_out, short * address_in);
int keypad_read(int * key_value);

#endif

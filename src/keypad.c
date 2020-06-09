#include "keypad.h"

static short * keypad_out, *keypad_in;

void init_keypad(short * address_out, short * address_in) {
	keypad_out = address_out;
	keypad_in = address_in;
}

int keypad_read(int * key_value) {
	int col, row, key_count = 0;
	short key_temp;

	for (col = 0; col < MAX_KEY_COL; col++) {
		*keypad_out = (int)pow(2,3-col);//1000 >> i 도 맞는방법//
		key_temp = *keypad_in;

		for (row = 0; row < MAX_KEY_ROW; row++) {
			if ((key_temp >> row) & 1) == 1 ){
			*key_value = row * 4 + col + 1;
			key_count++;
		}
	}
		return key_count;
}

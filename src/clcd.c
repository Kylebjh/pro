//-------| src/clcd.c |-------//

// clcd.c for double up
// 20150426 hunbeom shin

#include "clcd.h"

static short * clcd_cmd, * clcd_data;

void init_clcd(short * address_cmd, short * address_data) {
    
    int D = 1, C = 0, B = 0;
    int DL = 1, N = 1, F = 0;

    clcd_cmd  = address_cmd;
    clcd_data = address_data;

    clcd_clear_display();
    clcd_return_home();
    clcd_display_control(D, C, B);
    clcd_function_set(DL, N, F);
}
    
void clcd_write_cmd(int cmd) {
    *clcd_cmd = (short)cmd; usleep(CLCD_CMD_US);
}

void clcd_write_data(int data) {
    *clcd_data = (short)data; usleep(CLCD_DATA_US);
}

void clcd_clear_display() {
    clcd_write_cmd(0x01); usleep(CLCD_RETURN_US);
}

void clcd_return_home() {
    clcd_write_cmd(0x02); usleep(CLCD_RETURN_US);
}

void clcd_entry_mode_set(int ID, int S) {
    int cmd = 1 << 2;
    if( ID != 0 ) { cmd |= (1 << 1); }
    if( S  != 0 ) { cmd |= (1 << 0); }
    clcd_write_cmd(cmd);
}

void clcd_display_control(int D, int C, int B) {
    int cmd = 1 << 3;
    if( D != 0 ) { cmd |= (1 << 2); }
    if( C != 0 ) { cmd |= (1 << 1); }
    if( B != 0 ) { cmd |= (1 << 0); }
    clcd_write_cmd(cmd);

}

void clcd_shift(int SC, int RL) {
    int cmd = 1 << 4;
    if( SC != 0 ) { cmd |= (1 << 3); }
    if( RL != 0 ) { cmd |= (1 << 2); }
    clcd_write_cmd(cmd);
}

void clcd_function_set(int DL, int N, int F) {
    int cmd = 1 << 5;
    if( DL != 0 ) { cmd |= (1 << 4); }
    if( N  != 0 ) { cmd |= (1 << 3); }
    if( F  != 0 ) { cmd |= (1 << 2); }
    clcd_write_cmd(cmd);
}

void clcd_set_DDRAM(int address) {
    int cmd = 1 << 7;
    cmd |= address;
    clcd_write_cmd(cmd);
}
    
void clcd_write_string(char str[]) {
    int i;
    for( i=0; (str[i] != 0) ; i++) {
        clcd_write_data(str[i]);
    }
}


// clcd_startgame(int chips) : clcd code for start game
// upper line : double up game
// lower line : high : x (chips)
void clcd_startgame(int total_chips) {

    clcd_clear_display();
    int i;
//////////////////////////"                "
    char upper_string[] = "double up game";
    char lower_string[] = "tot : ";
    char total_chips_string[4];

    sprintf(total_chips_string,"%d",total_chips);

    // upper line setting
    clcd_entry_mode_set(1, 0);
    clcd_set_DDRAM(0x00);
    // upper line writing
    clcd_write_string(upper_string);

    // lower line setting
    clcd_entry_mode_set(1, 0);
    clcd_set_DDRAM(0x40);
    // lower line writing
    clcd_write_string(lower_string);

    // lower line chip writing
    clcd_write_string(total_chips_string);

}

// clcd_ingame_before_bet(int yourcard, int hiscard, int chips) : clcd code before betting
// upper line : up(1),down(2)(A)
// lower line : tot : X temp : X
void clcd_ingame_before_bet(int total_chips, int temp_chips) {

    clcd_clear_display();
    int i;
//////////////////////////"                "
    char upper_string[] = "up(1),down(2)(A)";
    char total_chips_string[4];
    char temp_chips_string[4];

    sprintf(total_chips_string,"%d",total_chips);
    sprintf(temp_chips_string,"%d",temp_chips);

    // upper line setting
    clcd_entry_mode_set(1, 0);
    // upper line writing
    clcd_write_string(upper_string);

    // lower line setting
    clcd_entry_mode_set(1, 0);
    clcd_set_DDRAM(0x40);
    // lower line writing
    clcd_write_string("tot:");
    clcd_write_string(total_chips_string);
    clcd_write_string(" temp:");
    clcd_write_string(temp_chips_string);

}

// clcd_ingame_after_bet(int yourcard, int hiscard, int chips) : clcd code after betting
// upper line : your : xx his : xx
// lower line : chips : x (chips)
void clcd_ingame_after_bet(int yourcard, int hiscard, int total_chips, int temp_chips) {

    clcd_clear_display();
    int i;
//////////////////////////"                "
    char ycard_string[1];
    char hcard_string[1];
    char total_chips_string[4];
    char temp_chips_string[4];

    sprintf(total_chips_string,"%d",total_chips);
    sprintf(temp_chips_string,"%d",temp_chips);


switch(yourcard) {
	case 1 :
	sprintf(ycard_string,"%s", "1");
	break;
	case 2 :
	sprintf(ycard_string,"%s", "2");
	break;
	case 3 :
	sprintf(ycard_string,"%s", "3");
	break;
	case 4 :
	sprintf(ycard_string,"%s", "4");
	break;
	case 5 :
	sprintf(ycard_string,"%s", "5");
	break;
	case 6 :
	sprintf(ycard_string,"%s", "6");
	break;
	case 7 :
	sprintf(ycard_string,"%s", "7");
	break;
	case 8 :
	sprintf(ycard_string,"%s", "8");
	break;
	case 9 :
	sprintf(ycard_string,"%s", "9");
	break;
	case 10 :
	sprintf(ycard_string,"%s", "J");
	break;
	case 11 :
	sprintf(ycard_string,"%s", "Q");
	break;
	case 12 :
	sprintf(ycard_string,"%s", "K");
	break;
	case 13 :
	sprintf(ycard_string,"%s", "A");
	break;

	default :
	sprintf(ycard_string,"%s", "E");

}

switch(hiscard) {
	case 1 :
	sprintf(hcard_string,"%s", "1");
	break;
	case 2 :
	sprintf(hcard_string,"%s", "2");
	break;
	case 3 :
	sprintf(hcard_string,"%s", "3");
	break;
	case 4 :
	sprintf(hcard_string,"%s", "4");
	break;
	case 5 :
	sprintf(hcard_string,"%s", "5");
	break;
	case 6 :
	sprintf(hcard_string,"%s", "6");
	break;
	case 7 :
	sprintf(hcard_string,"%s", "7");
	break;
	case 8 :
	sprintf(hcard_string,"%s", "8");
	break;
	case 9 :
	sprintf(hcard_string,"%s", "9");
	break;
	case 10 :
	sprintf(hcard_string,"%s", "J");
	break;
	case 11 :
	sprintf(hcard_string,"%s", "Q");
	break;
	case 12 :
	sprintf(hcard_string,"%s", "K");
	break;
	case 13 :
	sprintf(hcard_string,"%s", "A");
	break;

	default :
	sprintf(hcard_string,"%s", "E");

}

    // upper line setting
    clcd_entry_mode_set(1, 0);
    // upper line writing
    clcd_write_string("your:");
    clcd_set_DDRAM(0x00 + 5);
    clcd_write_string(ycard_string);
    clcd_set_DDRAM(0x00 + 6);
    clcd_write_string(" his:");
    clcd_set_DDRAM(0x00 + 11);
    clcd_write_string(hcard_string);

    // lower line setting
    clcd_entry_mode_set(1, 0);
    clcd_set_DDRAM(0x40);
    // lower line writing
    clcd_write_string("tot:");
    clcd_set_DDRAM(0x40 + 4);
    clcd_write_string(total_chips_string);
    clcd_set_DDRAM(0x40 + 5);
    clcd_write_string(" temp:");
    clcd_set_DDRAM(0x40 + 11);
    clcd_write_string(temp_chips_string);

}

// clcd_ingame_bet(int chips) : clcd code during betting
// upper line : up(1) down(2)
// lower line : chips :
void clcd_ingame_bet(int chips) {

    clcd_clear_display();
    int i;
//////////////////////////"                "
    char upper_string[] = "up(1),down(2)(A)";
    char lower_string[] = "chips : ";
    char chips_string[7];

    sprintf(chips_string,"%d",chips);


    // upper line setting
    clcd_entry_mode_set(1, 0);
    // upper line writing
    clcd_write_string(upper_string);

    // lower line setting
    clcd_entry_mode_set(1, 0);
    clcd_set_DDRAM(0x40);
    // lower line writing
    clcd_write_string(lower_string);

    // lower line chip writing
    clcd_set_DDRAM(0x40 + strlen( lower_string ) );
    clcd_write_string(chips_string);

}

// clcd_invaild_input() : clcd code for invaild input
// upper line : invaild input !!
// lower line : type again    !!
void clcd_invaild_input() {

    clcd_clear_display();
    int i;
//////////////////////////"                "
    char upper_string[] = "invaild input !!";
    char lower_string[] = "type again    !!";

    // upper line setting
    clcd_entry_mode_set(1, 0);
    // upper line writing
    clcd_write_string(upper_string);

    // lower line setting
    clcd_entry_mode_set(1, 0);
    clcd_set_DDRAM(0x40);
    // lower line writing
    clcd_write_string(lower_string);

}




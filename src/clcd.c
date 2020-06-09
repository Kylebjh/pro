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


// clcd_startgame(int total_chips, int temp_chips) : clcd code for start game
// upper line : Double up game
// lower line : tot: x temp:x
void clcd_startgame(int total_chips, int temp_chips) {

    clcd_clear_display();
    int i;
//////////////////////////"                "
    char upper_string[] = "Double up game";
    char total_chips_string[4];
    char temp_chips_string[4];

    sprintf(total_chips_string,"%d",total_chips);

    sprintf(temp_chips_string,"%d",temp_chips);

    // upper line setting
    clcd_entry_mode_set(1, 0);
    clcd_set_DDRAM(0x00);
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

// clcd_ingame_before_bet(int yourcard, int hiscard, int chips) : clcd code before betting
// upper line : up1, down 2 (A)
// lower line : tot : X temp : X
void clcd_ingame_before_bet(int yourcard, int hiscard, int total_chips, int temp_chips) {

    clcd_clear_display();
    int i;
//////////////////////////"                "
    char ycard_string[1];
    char hcard_string[1];

    char total_chips_string[4];
    char temp_chips_string[4];


switch(yourcard) {
	case 1 :
	sprintf(ycard_string,"%s", "A");
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

	default :
	sprintf(ycard_string,"%s", "E");

}

switch(hiscard) {
	case 1 :
	sprintf(hcard_string,"%s", "A");
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

	default :
	sprintf(hcard_string,"%s", "E");

}

    // upper line setting
    clcd_entry_mode_set(1, 0);

    // upper line writing
    clcd_write_string("!!!!");
    clcd_set_DDRAM(0x00 + 4);
    clcd_write_string(" you:");
    clcd_set_DDRAM(0x00 + 4 + 5);
    clcd_write_string(ycard_string);
    clcd_set_DDRAM(0x00 + 4 + 5 + 1);
    clcd_write_string(" his:");
    clcd_set_DDRAM(0x00 + 4 + 5 + 1 + 5);
    clcd_write_string("?");

    sprintf(total_chips_string,"%d",total_chips);
    sprintf(temp_chips_string,"%d",temp_chips);

    // lower line setting
    clcd_entry_mode_set(1, 0);
    clcd_set_DDRAM(0x40);
    // lower line writing
    clcd_write_string("tot:");
    clcd_write_string(total_chips_string);
    clcd_write_string(" temp:");
    clcd_write_string(temp_chips_string);
}


// clcd_ingame_win(int yourcard, int hiscard, int chips) : clcd code win
// upper line : WIN! your : x his : x
// lower line : tot: temp:
void clcd_ingame_win(int yourcard, int hiscard, int total_chips, int temp_chips) {

    clcd_clear_display();
    int i;
//////////////////////////"                "
    char ycard_string[1];
    char hcard_string[1];
    char total_chips_string[4];
    char temp_chips_string[4];


switch(yourcard) {
	case 1 :
	sprintf(ycard_string,"%s", "A");
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

	default :
	sprintf(ycard_string,"%s", "E");

}

switch(hiscard) {
	case 1 :
	sprintf(hcard_string,"%s", "A");
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

	default :
	sprintf(hcard_string,"%s", "E");

}

    // upper line setting
    clcd_entry_mode_set(1, 0);

    // upper line writing
    clcd_write_string("WIN!");
    clcd_set_DDRAM(0x00 + 4);
    clcd_write_string(" you:");
    clcd_set_DDRAM(0x00 + 4 + 5);
    clcd_write_string(ycard_string);
    clcd_set_DDRAM(0x00 + 4 + 5 + 1);
    clcd_write_string(" his:");
    clcd_set_DDRAM(0x00 + 4 + 5 + 1 + 5);
    clcd_write_string(hcard_string);

    sprintf(total_chips_string,"%d",total_chips);
    sprintf(temp_chips_string,"%d",temp_chips);

    // lower line setting
    clcd_entry_mode_set(1, 0);
    clcd_set_DDRAM(0x40);
    // lower line writing
    clcd_write_string("tot:");
    clcd_write_string(total_chips_string);
    clcd_write_string(" temp:");
    clcd_write_string(temp_chips_string);
}

// clcd_ingame_lose(int yourcard, int hiscard, int chips) : clcd code lose
// upper line : LOSE you : x his : x
// lower line : tot: temp:
void clcd_ingame_lose(int yourcard, int hiscard, int total_chips, int temp_chips) {

    clcd_clear_display();
    int i;
//////////////////////////"                "
    char ycard_string[1];
    char hcard_string[1];
    char total_chips_string[4];
    char temp_chips_string[4];


switch(yourcard) {
	case 1 :
	sprintf(ycard_string,"%s", "A");
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

	default :
	sprintf(ycard_string,"%s", "E");

}

switch(hiscard) {
	case 1 :
	sprintf(hcard_string,"%s", "A");
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

	default :
	sprintf(hcard_string,"%s", "E");

}

    // upper line setting
    clcd_entry_mode_set(1, 0);
    // upper line writing
    clcd_write_string("LOSE");
    clcd_set_DDRAM(0x00 + 4);
    clcd_write_string(" you:");
    clcd_set_DDRAM(0x00 + 4 + 5);
    clcd_write_string(ycard_string);
    clcd_set_DDRAM(0x00 + 4 + 5 + 1);
    clcd_write_string(" his:");
    clcd_set_DDRAM(0x00 + 4 + 5 + 1 + 5);
    clcd_write_string(hcard_string);

    sprintf(total_chips_string,"%d",total_chips);
    sprintf(temp_chips_string,"%d",temp_chips);

    // lower line setting
    clcd_entry_mode_set(1, 0);
    clcd_set_DDRAM(0x40);
    // lower line writing
    clcd_write_string("tot:");
    clcd_write_string(total_chips_string);
    clcd_write_string(" temp:");
    clcd_write_string(temp_chips_string);
}

// clcd_ingame_stopkeep(int total_chips, int temp_chips) : clcd code stop keep
// upper line : stop1 keep2 (A)
// lower line : tot : X temp : X
void clcd_ingame_stopkeep(int total_chips, int temp_chips) {

    clcd_clear_display();
    int i;
//////////////////////////"                "
    char upper_string[] = "stop1 keep2 (A)";
    char total_chips_string[4];
    char temp_chips_string[4];

    sprintf(total_chips_string,"%d",total_chips);

    sprintf(temp_chips_string,"%d",temp_chips);

    // upper line setting
    clcd_entry_mode_set(1, 0);
    clcd_set_DDRAM(0x00);
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

// clcd_gameover(int total_chips, int temp_chips) : clcd code for game over
// upper line : Game Over :)
// lower line : score : x
void clcd_gameover(int total_chips) {

    clcd_clear_display();
    int i;
//////////////////////////"                "
    char upper_string[] = "Game Over :)";
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
    clcd_write_string("score : ");
    clcd_write_string(total_chips_string);

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




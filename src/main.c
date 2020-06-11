#include "main.h"

static off_t IEB_DOT[MAX_DOT] = {
	IEB_DOT1,
	IEB_DOT2,
	IEB_DOT3,
	IEB_DOT4,
	IEB_DOT5
};
static off_t IEB_FND[MAX_FND] = {
	IEB_FND0,
	IEB_FND1,
	IEB_FND2,
	IEB_FND3,
	IEB_FND4,
	IEB_FND5,
	IEB_FND6,
	IEB_FND7
};

static int fd;
static int map_counter = 0;
static void * map_data[100];
static seclection_t sel; 

short * mapper(off_t offset, int prot) {
	map_data[map_counter] = mmap(NULL, sizeof(short), prot, MAP_SHARED, fd, offset);
	if ( map_data[map_counter] == MAP_FAILED ) {
		fprintf(stderr, "Cannot do mmap()");
		emergency_closer();
	}
	return (short *)map_data[map_counter++];
}

void unmapper() {
	int i;
	for( i=0; i<map_counter; i++) {
		munmap(map_data[i], sizeof(short));
	}
	map_counter = 0;
}

void emergency_closer() {
	unmapper();
	close(fd);
	exit(EXIT_FAILURE);
}

truth_t logic() {
	if( sel.exit == 1 ) {
		return FALSE; 
	}

	return TRUE;
}

// 1~12 generation, A23456789JQK
int gen_randNum(){
	int random = 0;
	random = (rand()%12) + 1 ;

	return random;
}

int main(int argc, char* argv[]){
	int i;
	short * led, * dot[MAX_DOT], * fnd[MAX_FND];
	short * clcd_cmd, * clcd_data, * keypad_out, * keypad_in;
	int answer = 0;		// his card
	int bet_cost = 0;	// not using
	int best_score = 0;	// total score
	int score = 1;		// temp score
	int life = 3;		// life
	int cur_num = 0;	// your card
	
	fd = open("/dev/mem", O_RDWR|O_SYNC);
	if (fd == -1) {
		fprintf(stderr, "Cannot open /dev/mem file");
		exit(EXIT_FAILURE);
	}
	
	led = mapper(IEB_LED, PROT_WRITE);
	for( i=0; i<MAX_DOT; i++ ) {
		dot[i] = mapper(IEB_DOT[i], PROT_WRITE);
	}
	for( i=0; i<MAX_FND; i++ ) {
		fnd[i] = mapper(IEB_FND[i], PROT_WRITE);
	}
	clcd_cmd  = mapper(IEB_CLCD_CMD, PROT_WRITE);
	clcd_data = mapper(IEB_CLCD_DATA, PROT_WRITE);
	//keypad_out = mapper(IEB_KEY_W, PROT_WRITE);
	//keypad_in = mapper(IEB_KEY_R, PROT_READ);

	init_led(led);
	init_dot(dot);
	init_fnd(fnd);
	init_clcd(clcd_cmd, clcd_data);
	//init_keypad(keypad_out,keypad_in);

int flag_main = 1;

while( flag_main == 1 ) {

//초기상태

	// led blink
	led_blink_all();
	dot_write(0); //dot 깜
	usleep(100);
	dot_clear(); //dot 빡
				
	// clcd
	clcd_startgame(best_score, score);

	answer = gen_randNum();// answer 난수 생성

// loop for differnt randNum Selection (cur_num != answer)
num_sel:
		answer = gen_randNum();// answer 난수 생성

		while(1){
			cur_num = gen_randNum();// cur_num 난수 생성
			if(cur_num != answer) break; //정답과 다른 숫자가 선택되면 탈출
		}
				
		// fnd life
		fnd_hexa_number(life);		
		
		// clcd start game
		clcd_ingame_before_bet(cur_num, answer, best_score, score);

		// dot cur_num
		dot_write(cur_num);

// loop for game keep going
	int val_keephold = 0; // val_keephold 변수가 keypad.c함수내의 key_value변수와 동일한 역할.
	int flag_keephold =1;
	int key_count;
	
	do {
		printf("keep going(1) & stop(2) : "); 
		key_count = keyboard_read(&val_keephold);
		//key_count = keypad_read(&val_keephold);

		if (key_count > 1){ flag_keephold = 1;}
		else if ( val_keephold == 1 ) { flag_keephold = 0;}
		else if ( val_keephold == 2 ) {
			best_score += score;
			score = 0;
			flag_keephold = 0;
		}
		else {flag_keephold = 1;}       
	}while( flag_keephold == 1 );

		// clcd start game
		clcd_ingame_before_bet(cur_num, answer, best_score, score);

//게임중

	

	if(life > 0){ //목숨이 남아있을때

// loop for game up down

	int val_updown = 0;
	int flag_updown = 1;
	key_count = 0; // key_count 초기화

		do {
			printf("!!!! choose up(1) & down(2) : "); //입력 받고
			key_count = keyboard_read(&val_updown);
			//key_count = keypad_read(&val_updown);

			if (key_count > 1){ flag_updown = 1;}
			else if ( ( val_updown == 1 ) || ( val_updown == 2 )) { flag_updown = 0;}
			else {flag_updown = 1;}

		}while( flag_updown == 1 );

		if(val_updown == 1){//up

			// led blink
			led_blink_all();

			if(answer > cur_num){//맞으면
				score *= 2;

				// clcd
				clcd_ingame_win(cur_num, answer, best_score, score);

				usleep(100000);

				// led up
				led_up_shift();

				goto num_sel;

			} else {//틀리면
				life -= 1;

				// clcd
				clcd_ingame_lose(cur_num, answer, best_score, score);

				usleep(100000);

				// led down
				led_down_shift();

				goto num_sel;

			}

		}else if(val_updown == 2){//down

			// led blink
			led_blink_all();

				if(answer < cur_num){// win
					score *= 2;

					// clcd
					clcd_ingame_win(cur_num, answer, best_score, score);

					usleep(100000);

					// led up
					led_up_shift();

					goto num_sel;

				} else {//틀리면
					life -= 1;

					// clcd
					clcd_ingame_lose(cur_num, answer, best_score, score);

					usleep(100000);

					// led down
					led_down_shift();

					goto num_sel;

				}
		}
	} else { // game over

		//clcd
		clcd_gameover(best_score);

		// led blink
		led_blink_all();

		usleep(50000);

		flag_main = 0;

	}
}

	unmapper();
	close(fd);
	return 0;
}

		

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

int gen_randNum(){
	int random = 0;
	random = rand()%9;

	return random;
}

int main(int argc, char* argv[]){
	int i;
	short * led, * dot[MAX_DOT], * fnd[MAX_FND];
	short * clcd_cmd, * clcd_data, * keypad_out, * keypad_in;
	int answer = 0;
	int bet_cost = 0;
	int best_score = 9;
	int score = 1;//////////////////////
	int life = 3;//////////////////////
	int cur_num = 0;/////////////////////
	
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

	init_led(led);
	init_dot(dot);
	init_fnd(fnd);
	init_clcd(clcd_cmd, clcd_data);

	sel.all = 0;
	while( logic() == TRUE ) {
		//게임 시작 전
		switch(sel.all){
			case 0://초기상태면

				// led blink
				led_blink_all();
				dot_write(0); //dot 깜
				usleep(100);
				dot_clear(); //dot 빡

				score = 1;
				life = 3;
				
				// clcd
				clcd_clcd_startgame(best_score, score);

				answer = gen_randNum();//난수 생성
				sel.all = 2;
				break;

			case 2: //sel.all 이 2이면
				while(1){
					dot_write(answer);//답 출력

					while(1){
						cur_num = gen_randNum();//난수 생성	
						if(cur_num != answer) break; //정답과 다른 숫자가 선택되면 탈출
					}
					
					fnd_hexa_number(life);//현재 선택 카드 출력
					clcd_clcd_startgame(cur_num);

				}
				
				sel.all = 3;

			case 3: //게임중
				dot_write(answer);//답 출력
				clcd_clcd_startgame(cur_num);
				fnd_hexa_number(life);

				// clcd
				clcd_ingame_before_bet(best_score, score)

				int val = 0;
				while(1)
				{ 
					if(life > 0){ //목숨이 남아있을때
					printf("choose up(1) & down(2) : "); //입력 받고
					scanf("%d", &val);

					if(val == 1){//up

						// led blink
						led_blink_all();

						if(answer > cur_num){//맞으면
							score *= 2;

							// clcd
							clcd_ingame_win(cur_num, answer, best_score, score)
							// led up
							led_up_shift();

						}else{//틀리면
							life -= 1;

							// clcd
							clcd_ingame_lose(cur_num, answer, best_score, score)
							// led down
							led_down_shift();
						}
					}else if(val == 2){//down

						// led blink
						led_blink_all();

						if(answer < cur_num){// win
							score *= 2;

							// clcd
							clcd_ingame_win(cur_num, answer, best_score, score)
							// led up
							led_up_shift();

						}else{//틀리면
							life -= 1;

							// clcd
							clcd_ingame_lose(cur_num, answer, best_score, score)
							// led down
							led_down_shift();
						}

					
					

					if(life == 0){ // game over

					// led blink
					led_blink_all();

					//clcd
					clcd_gameover(best_score);

					printf("Do you want to one More? Y ");
					char re = 0x00;
					scanf("%s",&re);
					if(re == 0x59){
						sel.all = 0;
					}else{
						sel.all = 1;
					}

					break;
				}

				
				break;
		}
	}

	unmapper();
	close(fd);
	return 0;
}
				
		

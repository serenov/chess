#include"../include.h"
char status[64];
short turnd(short turn){ if(turn == 0) return 8; return 16;}
void count(short b[], short possible[], short turn, short depth){
	if(depth > 3) return;
	static int cnt = 0;
	static int co = 0;
	short pss[35], kp[2], captured = none;
	for(short i = 0; i < 35; i++) pss[i] = possible[i];
	kp[0] = kpos[0];
	kp[1] = kpos[1];
	for(short i = 0; i < 64; i++){
		if(b[i] != none){
			if((b[i] & turnd(turn)) >= 8){
				pss[34] = -1;
				pss[0] = picker(b, i, pss);
				cnt += pss[0];
	//			printf("for i = %d, of depth %d, count %d, board[6] is\n", i, depth, cnt);
				for(short j = 1; j <= pss[0]; j++){
				       	if(b[pss[j]] != none){ captured = b[pss[j]];
				       		co++;	
						printf("for i = %d, of depth %d, count %d, captured by %d at %d\n", i, depth, cnt, i, pss[j]);
							if(depth == 3)display(b, status); printf("***\n");
						}
					movmkr(pss[j], b, i, pss);
					count(b, pss, !turn, depth + 1);
					b[i] = b[pss[j]];
					b[pss[j]] = captured;
					captured = none;
					kpos[0] = kp[0];
					kpos[1] = kp[1];		
				}
			}
		}
	}
	//printf("%d, %d\n", cnt, co);
}
int main(){
	short board[64], possible[35];
	possible[34] = -1;
	for(short i = 0; i < 64; i++) board[i] = none;
	for(short i = 0; i < 64; i++) status[i] = ' ';
	fen(string, board, possible + 28);
	count(board, possible, 1, 0);
	return 0;
}


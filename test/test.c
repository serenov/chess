#include"../include.h"
short turnd(short turn){ if(turn == 0) return 8; return 16;}
void count(short board[], short possible[], short turn, short depth){
	if(depth > 1) return;
	static short cnt = 0;
	short b[64], pss[6], kp[2], captured = none;
	short off = (turn == 0)? 1: -1;
	for(short i = 0; i < 64; i++) b[i] = board[i];
	for(short i = 0; i < 6; i++) pss[i] = possible[i + 28];
	kp[0] = kpos[0];
	kp[1] = kpos[1];
	for(short i = 0; i < 64; i++){
		if(b[i] != none){
			if(b[i] > 23);
			else if((b[i] & turnd(turn)) >= 8){
				possible[0] = picker(b, i, possible);
				cnt += possible[0];
				printf("for i = %d, of depth %d, count %d, board[6] is %d\n", i, depth, cnt, board[6]);
				for(short j = 1; j <= possible[0]; j++){
				       	if(b[possible[j]] != none) captured = b[possible[j]];
					movmkr(possible[j], b, i, possible);
					count(b, possible, !turn, depth + 1);
					b[i] = b[possible[j]];
					b[possible[j]] = captured;
					captured = none;
					for(short k = 0; k < 6; k++) possible[k + 28] = pss[k];
					if((board[possible[j]] % 8) == 6)if(possible[j] == (i + off * 2)) b[i + 8 * off] = none;
					kp[0] = kpos[0];
					kp[1] = kpos[1];		
				}
			}
		}
	}
	printf("%d\n", cnt);
}
int main(){
	short board[64], possible[34];
	for(short i = 0; i < 64; i++) board[i] = none;
	fen(string, board, possible + 28);
	count(board, possible, 0, 0);
	return 0;
}


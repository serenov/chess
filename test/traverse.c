#include"../include.h"
short turnd(short turn){ if(turn == 0) return 8; return 16;}
short offsetd(short turn){ if(turn == 0) return 8; return -8;}
short checkmate(short board[], short color, short *possible){
	for(short i = 0; i < 64; i++){
		if((board[i] & color) >= 8){
			if(picker(board, i, possible)) return 0;
		}
	}
	return 1;
}
void undo(short *pos, short *prevpos, short *kp, short *capturedpiece){
	*prevpos = *pos;
	*pos = *capturedpiece;
        *capturedpiece = none;
        kpos[0] = *kp;
        kpos[1] = *(kp + 1);
}
void init(short *kp){
        *kp = kpos[0];
        *(kp + 1) = kpos[1];
}
int count = 0;
char status[64];
void traverse(short board[], short *possible, short turn, short depth){
	short kp[2];
        short tpossible[35], capturedpiece = none;
        init(kp); 
	if(kingthreat(board, kp[turn])){if(checkmate(board, turnd(turn), tpossible)) return;}
        if(depth > 4) return;
        for(short i = 0; i < 7; i++){ tpossible[i + 28] = *(possible + i);}
        for(short i = 0; i < 64; i++){
                if(board[i] != none){
                        if((board[i] & turnd(turn)) >= 8){
                                tpossible[0] = picker(board, i, tpossible);
                                if(depth == 0)count += tpossible[0];
                                for(short j = 1; j <= tpossible[0]; j++){
                                        if(board[tpossible[j]] != none)capturedpiece = board[tpossible[j]];
                                        movmkr(tpossible[j], board, i, tpossible);
                                        traverse(board, tpossible + 28, !turn, depth + 1);
                                        undo(board + tpossible[j], board + i, kp, &capturedpiece);
					tpossible[34] = -1;
		//			tpossible[34] = *(possible + 6);
				}
			}
                }
        }
}
int main(){
        short board[64], possible[35];
        for(short i = 0; i < 64; i++){board[i] = none; status[i] = ' ';}
        for(short i = 28; i < 34; i++) possible[i] = 1;
	possible[34] = -1;
        fen(string, board, possible + 28);
        traverse(board, possible + 28, 0, 0);
        printf("%d\n", count);
        return 0;
}

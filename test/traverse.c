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
void init(short *kp){
        *kp = kpos[0];
        *(kp + 1) = kpos[1];
}void dinit(short *kp){
        kpos[0] = *kp;
        kpos[1] = *(kp + 1);
}
void FDecide(short board[], short *flag, short i, short tpossible, short list[], short turn){
        list[0] = i;
        list[1] = tpossible;
        *flag = 0; list[2] = board[tpossible];
        if(board[i] % 8 == 6){
                if(i + offsetd(turn, 1) == tpossible || i + offsetd(turn, 2) == tpossible)if(board[tpossible] == none){*flag = 1; list[2] = (turn == 0)? -8: 8; }
        }
        else if(board[i] % 8 == 1){ if(i + 2 == tpossible || i - 2 == tpossible){ *flag = 2; list[2] = (i + 2 == tpossible)? 1: -1;}}
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
                                        FDecide(board, &flag, i, tpossible[j], list, turn);
                                        movmkr(tpossible[j], board, i, tpossible);
                                        traverse(board, tpossible + 28, !turn, depth + 1);
                                        undo(board, list, flag);
                                        dinit(kp);
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

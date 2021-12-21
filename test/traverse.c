#include"../include.h"
short turnd(short turn){ if(turn == 0) return 8; return 16;}
void undo(short *pos, short *prevpos, short *enpassant, short *kp, short *capturedpiece){
        *prevpos = *pos;
        *pos = *capturedpiece;
        *capturedpiece = none;
        *enpassant = -1;
        kpos[0] = *kp;
        kpos[1] = *(kp + 1);
}
void init(short *kp){
        *kp = kpos[0];
        *(kp + 1) = kpos[1];
}
short count = 0;
void traverse(short board[], short *possible, short turn, short depth){
        if(depth > 0) return;
        short kp[2], tpossible[35], capturedpiece = none;
        init(kp);
        for(short i = 0; i < 7; i++) tpossible[i + 28] = *(possible + i);
        for(short i = 0; i < 64; i++){
                if(board[i] != none){
                        if((board[i] & turnd(turn)) >= 8){
                                tpossible[0] = picker(board, i, tpossible);
                                for(short j = 1; i < tpossible[0]; j++){
                                        count++;
                                        if(board[tpossible[j]] != none) capturedpiece = board[tpossible[j]];
                                        movmkr(tpossible[j], board, i, tpossible);
                                        traverse(board, tpossible + 28, !turn, depth + 1);
                                        undo(board + tpossible[j], board + i, tpossible + 34, kp, &capturedpiece);
                                }
                        }
                }
        }
}
int main(){
        short board[64], possible[35];
        for(short i = 0; i < 64; i++) board[i] = none;
        fen(string, board, possible + 28);
        traverse(board, possible + 28, 0, 0);
        printf("%d\n", count);
        return 0;
}

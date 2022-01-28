short turnd(short turn){ if(turn == 0) return 8; return 16;}
short offsetd(short turn, short flag){
        if(flag == 0){if(turn == 0) return 8; return 16;} else if(flag == 1){ if(turn == 0) return 9; return -9;}
        else{ if(turn == 0) return 7; return -7;}
}
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
}
void dinit(short *kp){
        kpos[0] = *kp;
        kpos[1] = *(kp + 1);
}
int count = 0;
void FDecide(short board[], short *flag, short i, short tpossible, short list[], short turn, short *possible, short j){
        list[0] = i;
        list[1] = tpossible;
        *flag = 0; list[2] = board[tpossible];
        if(board[i] % 8 == 6){
                if(i + offsetd(turn, 1) == tpossible || i + offsetd(turn, 2) == tpossible){if(board[tpossible] == none){*flag = 1; list[2] = (turn == 0)? -8: 8; }}
		if(*(possible + 13) == -2){
			*flag = 3;
			*(possible + 14) = 8 + turn * 8 + ((j - 1) % 4) + 2;
		}
        }
        else if(board[i] % 8 == 1){ if(i + 2 == tpossible || i - 2 == tpossible){*flag = 2; list[2] = (i + 2 == tpossible)? 1: -1;}}
}
short eval(short board[])
{
	short v[] = { 0, 100, 8, 5, 3, 3, 1};
        short score = 0;
        for(short i = 0; i < 64; i++){
                score += (board[i] > 16)? -v[board[i] % 8]: v[(board[i] % 8)];
        }
        return score;
}
short traverse(short board[], short *possible, short turn, short depth, short *mov){
        short kp[2];
        short tpossible[35], capturedpiece = none, flag, list[3];
       	short tt = (turn == 0)? 1: -1, r = -tt * 100, rtemp;
        init(kp);
        if(kingthreat(board, kp[turn])){if(checkmate(board, turnd(turn), tpossible))return -tt * 100;}
	if(stalemate(board, turn)) return 0;
        if(depth > LIMIT) return eval(board);
        for(short i = 0; i < 7; i++){ tpossible[i + 28] = *(possible + i);}
        for(short i = 0; i < 64; i++){
                if(board[i] != none){
                        if((board[i] & turnd(turn)) >= 8){
                                tpossible[0] = picker(board, i, tpossible);
                             	//if(depth == LIMIT)count += tpossible[0];
                                for(short j = 1; j <= tpossible[0]; j++){
                                        FDecide(board, &flag, i, tpossible[j], list, turn, tpossible, j);
                                        movmkr(tpossible[j], board, i, tpossible);
//					if(depth == 0){display(board, status); printf("score %d, depth %d, from %d to %d, count %d, r value %d\n", eval(board), depth, i, tpossible[j], count, r);}
                                        rtemp = traverse(board, tpossible + 28, !turn, depth + 1, mov);
					//if(depth == 0)printf("%d\n", rtemp);
					if( tt * rtemp >= tt * r){
						r = rtemp;
						if(depth == 0) { *mov = i; *(mov + 1) = tpossible[j];}
					}
                                        undo(board, list, flag);
                                        dinit(kp);
                                        for(short i = 0; i < 7; i++){ tpossible[i + 28] = *(possible + i);}
					if(flag == 3){ tpossible[13] = -2;}
                                }
				tpossible[13] = 0;
                        }
                }
        }
	return r;
}
/*int main(){
        short board[64], possible[35], move[2];
        for(short i = 0; i < 64; i++){board[i] = none;}
        for(short i = 28; i < 34; i++) possible[i] = 1;
        possible[34] = -1;
        fen(string, board, possible + 28);
        traverse(board, possible + 28, 1, 0, move);
        printf("count: %d %d\n", move[0], move[1]);
        return 0;
}*/

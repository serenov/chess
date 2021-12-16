#include<stdio.h>
#define string "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"
void display(short b[]);
void fen(char *a, short b[], short *list);
short linemove(short board[], short pos, short* possible);
short queenmove(short board[], short pos, short* possible);
short knightmove(short board[], short pos, short *possible);
short pawnmove(short board[], short pos, short* possible);
short kingmove(short board[], short pos, short* possible);
short diagonalmove(short board[], short pos, short *possible);
void arra(short arr[]);
short const none = 0;
short const K = 9, Q = 10, R = 11, B = 12, N = 13, P = 14;
short const k = 17, q = 18, r = 19, b =  20, n = 21, p = 22;
short kpos[2];
short kingthreat(short board[], short pos){
	short possible[14];
	possible[0] = diagonalmove(board, pos, possible);
	for(short i = 1; i <= possible[0]; i++){
		if(board[possible[i]] % 8 == 2 || board[possible[i]] % 8 == 4 || board[possible[i]] % 8 == 1) return 1;
		if(board[possible[i]] % 8 == 6){
			if(board[pos] > 16) if(possible[i] == pos - 9 || possible[i] == pos - 7) return 1;
			if(possible[i] == pos + 9 || possible[i] == pos + 7) return 1;	
		}
	}
	possible[0] = linemove(board, pos, possible);
	for(short i = 1; i <= possible[0]; i++){
		if(board[possible[i]] % 8 == 2 || board[possible[i]] % 8 == 3) return 1;	
	}
	possible[0] = knightmove(board, pos, possible);
	for(short i = 1; i <= possible[0]; i++){
		if(board[possible[i]] % 8 == 5) return 1;	
	}
	return 0;
}
short nonemove(short board[], short pos, short *possible){
	return 0;
}
short picker(short board[], short pos, short* possible){
	short (*piecesmove[])(short*, short, short*) = {nonemove, kingmove, queenmove, linemove, diagonalmove, knightmove, pawnmove};
	*possible = (*piecesmove[board[pos]%8])(board, pos, possible);
	return *possible;
}
void movmkr(short destpos, short board[], short pos, short* possible){
	static short enpos = 0;
	if(board[enpos] > 22) board[enpos] = 0;
	if((board[pos] % 8) == 6){ if(pos < 16 || pos > 47){if(destpos == (pos + 16)){ board[pos + 8] = 24; enpos = pos + 8; }else if(destpos == (pos - 16)){ board[pos - 8] = 25; enpos = pos - 8;}}
		if(destpos == enpos){if(board[pos] > 16) board[destpos + 8] = none; else board[destpos - 8] = none;} 
	}
	else if((board[pos] % 8) == 1){if(board[pos] > 16){if(!*(possible + 32)) *(possible + 32) = 1; kpos[1] = destpos;} else{ if(!*(possible + 29)) *(possible + 29) = 1; kpos[0] = destpos;}
		if(destpos == pos - 2){board[pos - 1] = board[pos - 4]; board[pos - 4] = none;}		
		if(destpos == pos + 2){board[pos + 1] = board[pos + 3]; board[pos + 3] = none;}		
	}
	else if((board[pos] % 8) == 3){
		if(board[pos] > 16){
			if(pos == 56) if(!*(possible + 31)) *(possible + 31) = 1;
			if(pos == 63) if(!*(possible + 33)) *(possible + 33) = 1;
		}
		else{
			if(pos == 0) if(!*(possible + 28)) *(possible + 28) = 1;
			if(pos == 7) if(!*(possible + 30)) *(possible + 30) = 1;
		}	
	}
	board[destpos] = board[pos];
	board[pos] = none;
}
short psmkr(short board[], short pos, short destpos){
	short b[64], kp[2];
	kp[0] = kpos[0];
	kp[1] = kpos[1];
	for(short i = 0; i < 64; i++) b[i] = board[i];
	b[destpos] = b[pos];
	b[pos] = none;
	if(board[pos] > 16){if(b[destpos] == k) kp[1] = destpos; return kingthreat(b, kp[1]);}
	if(b[destpos] == K) kp[0] = destpos;
	return kingthreat(b, kp[0]);
}
short turnd(short turn){
	if(turn == 0) return 8;
	return 16;
}
short checkmate(short board[], short kpos, short *possible){
	if(kingthreat(board, kpos)){
		for(short i = 0; i < 64; i++){
			if(!picker(board, i, possible)){
				return 1;	
			}
		}
	}
	return 0;
}
void search(short board[], short poss[], short turn){
	static long int count = 0;
	static short depth = 0;
	short capturedpiece;
	short possible[34], b[64], kp[2];
	kp[0] = kpos[0];
	kp[1] = kpos[1];
	for(short i = 28; i < 34; i++)possible[i] = poss[i];
	for(short i = 0; i < 64; i++)b[i] = board[i];
	if(depth > 2 || checkmate(b, kpos[turn], possible)) return;
	for(short i = 0; i < 64; i++){
		if(b[i] != none){		
			if((b[i] & turnd(turn)) >= 8){
				//printf("%d for depth %d\n", i, depth);
				possible[0] = picker(b, i, possible);
				count += possible[0];
				for(short j = 1; j <= possible[0]; j++){
					depth++;
					capturedpiece = b[possible[j]];
					movmkr(possible[j], b, i, possible);
					search(b, possible, !turn);
					b[i] = b[possible[j]];
					b[possible[j]] = capturedpiece;
					kpos[0] = kp[0], kpos[1] = kp[1];
					depth--;
				}		
			}
		}		
	}
	printf("count is %ld\n", count);
}

short main(){
/*	
	short board[64], po[34];
	char status[64];
	for(short i = 0; i < 64; i++) status[i] = ' ';
	for(int i = 0; i < 64; i++) board[i] = none;
	fen(string, board, po + 28);
	disply(board, status);
	picker(board, 6, po);
	arra(po);
	return 0;
*/
//	game();
	short board[64], possible[34];
	for(short i = 0; i < 64; i++) board[i] = none;
	fen(string, board, possible + 28);
	search(board, possible, 0);
}
void fen(char *a, short bo[], short* list){
	for(int i = 56; i > -1;){
		if(*a > 97){
			if(*a == 'p') bo[i] = p;
			else if(*a == 'n') bo[i] = n;
			else if(*a == 'b') bo[i] = b;
			else if(*a == 'r'){ bo[i] = r; if(i == 0) *(list) = 1; if(i == 7) *(list + 2) = 1;}
			else if(*a == 'q') bo[i] = q;
			else {bo[i] = k; kpos[1] = i; if(i == 4) *(list + 4) = 1;}
			i++;
		}
		else if(*a > 65){
			if(*a == 'P') bo[i] = P;
			else if(*a == 'N') bo[i] = N;
			else if(*a == 'B') bo[i] = B;
			else if(*a == 'R'){ bo[i] = R; if(i == 56) *(list + 3) = 1; if(i == 63) *(list + 5) = 1;}
			else if(*a == 'Q') bo[i] = Q;
			else {bo[i] = K; kpos[0] = i; if(i == 60) *(list + 1) = 1;}
			i++;
		}
		else if(*a > 48){
			for(int j = 1; j <= (*a - 48); j++){ bo[i] = none; i++;}
		}
		else i = i - 16;
		a++;
	}
}
short inspect(short board[], short pos, short color){
	if(board[pos] == none || board[pos] == 24 || board[pos] == 25) return 1;
	if((board[pos] & color) < 8) return 2;
	return 0;
}
short queenmove(short board[], short pos, short* possible){
	int count = linemove(board, pos, possible);
	possible += count;
	count += diagonalmove(board, pos, possible);
       return count;	
}
short pawnmove(short board[], short pos, short* possible){
	short offset[5], count = 0;
	possible++;
	short color = (board[pos] > 16)? -1: 1;
	short list(short pos, short *off){
		short count = 0;
		off++;
		if(color == 1){
			if(pos / 8 < 8 && board[pos + 8] == none){ 
				*off = 8; off++; count++;
				if(pos / 8 == 1 && board[pos + 16] == none){ *off = 16; off++; count++;}
			}
			if(pos % 8 > 0){
				if(inspect(board, pos + 7, board[pos]) == 2 || board[pos + 7] == 25){
					*off = 7; off++; count++;
				}
			}
			if(pos % 8 < 7){
				if(inspect(board, pos + 9, board[pos]) == 2 || board[pos + 9] == 25){
					*off = 9; off++; count++;
				}
			}
		}
		else{
			if(pos / 8 > -1 && board[pos - 8] == none){ 
				*off = -8; off++; count++;
				if(pos / 8 == 6 && board[pos - 16] == none){ *off = -16; off++; count++;}
			}
			if(pos % 8 > 0){
				if(inspect(board, pos - 9, board[pos]) == 2 || board[pos - 9] == 24){
					*off = -9; off++; count++;
				}
			}
			if(pos % 8 < 7){
				if(inspect(board, pos - 7, board[pos]) == 2 || board[pos - 7] == 24){
					*off = -7; off++; count++;
				}
			}
		}
		return count;
	}
	offset[0] = list(pos, offset);
	for(short i = 1; i <= offset[0]; i++){
		if(!psmkr(board, pos, pos + offset[i])){
			*possible = pos + offset[i];
			count++; possible++;
		}
	}
	return count;
}
/*	
short pawnmove(short board[], short pos, short* possible){
	short count = 0;
	possible++;
	if(board[pos] > 16){
		if(board[pos - 8] == none){*possible = pos - 8; possible++; count++;
			if(pos > 47){if(board[pos - 16] == none){*possible = pos - 16; possible++; count++;}}}
		if(pos % 8 > 0)if(inspect(board, pos - 9, board[pos]) == 2 || board[pos - 9] == 24){*possible = pos - 9; possible++; count++;}
		if(pos % 8 < 7)if(inspect(board, pos - 7, board[pos]) == 2 || board[pos - 7] == 24){*possible = pos - 7; possible++; count++;}
	}
	else{
		if(board[pos + 8] == none){*possible = pos + 8; possible++; count++;
			if(pos < 16){if(board[pos + 16] == none){*possible = pos + 16; possible++; count++;}}}
		if(pos % 8 > 0)if(inspect(board, pos + 7, board[pos]) == 2 || board[pos + 7] == 25){*possible = pos + 7; possible++; count++;}
		if(pos % 8 < 7)if(inspect(board, pos + 9, board[pos]) == 2 || board[pos + 9] == 25){*possible = pos + 9; possible++; count++;}
	}
	return count;
}*/
short castling(short board[], short pos, short *ismoved, short offset){
        if(*ismoved);
        else if(*(ismoved + offset));
        else{
                if(offset == -1)if(board[pos - 2] == none);
                else if(offset == 1)if(board[pos + 2] == none && board[pos + 3] == none);
                else return 0;
                return 1;
        }
        return 0;
}
short kingmove(short board[], short pos, short *possible){
        short offset[9], count = 0;
        possible++;
        short color = (board[pos] > 16)? 32: 29;
        short list(short pos, short *off){
                short count = 0;
                off++;
                if(pos / 8 < 7){
                        *off = 8; off++; count++;
                        if(pos % 8 > 0){ *off = 7; off++; count++;}
                        if(pos % 8 < 7){ *off = 9; off++; count++;}
                }
                if(pos / 8 > 0){
                        *off = -8; off++; count++;
                        if(pos % 8 > 0){ *off = -9; off++; count++;}
                        if(pos % 8 < 7){ *off = -7; off++; count++;}
                }
                if(pos % 8 > 0){ *off = -1; off++; count++;}
                if(pos % 8 < 7){ *off = 1; off++; count++;}
		return count;
        }
        offset[0] = list(pos, offset);
        for(short i = 1; i <= offset[0]; i++){
                if(inspect(board, pos + offset[i], board[pos])){
                        if(!(psmkr(board, pos, pos + offset[i]))){
                                *possible = pos + offset[i];
                                count ++; possible++;
                                if(castling(board, pos, possible + color - count - 1, offset[i])){
                                        if(!psmkr(board, pos, pos + 2 * offset[i])){
                                                *possible = pos + 2 * (offset[i]);
                                                count ++; possible++;
                                        }
                                }
                        }
                }
        }
        return count;
}
short diagonalmove(short board[], short pos, short *possible){
	short offs[] = {-9, 9, -7, 7, 0};
	short tmp, count = 0, *offset = offs;
	short boundary(short offset){
		short i = 0;
		if( offset == 9 || offset == 7){
			if( offset == 9){
				if(pos % 8 < pos / 8) i = pos / 8 - pos % 8;
				return 7 - pos % 8 - i;
			}
			if(pos % 8 > (7 - pos / 8)) i = (pos / 8) - ( 7 - (pos % 8));
			return pos % 8 - i;
		}
		if(offset == -9){
			if(pos % 8 > pos / 8) i = pos % 8 - pos / 8;
			return pos % 8 - i;
			
		}
		if(pos % 8 < (7 - pos / 8)) i = (7 - pos / 8) - pos % 8;
		return 7- pos % 8 - i;
	}
	possible++;
	for(; *offset != 0; offset++){
		tmp = boundary(*offset);
		for(short i = 1; i <= tmp; i++){
			if(board[pos] % 8 != 1){
				if(inspect(board, pos + i * (*offset), board[pos])){
					if(!psmkr(board, pos, pos + i * (*offset))){ 
						*possible = pos + i * (*offset); possible++; count++;}
					if(inspect(board, pos + i * (*offset), board[pos]) == 2) break;
				}
				else break;
			}
			else{
				if(inspect(board, pos + i * (*offset), board[pos]) == 2){ 
					*possible = pos + i * (*offset); possible++; count++;
					break;
				}
				else if(!inspect(board, pos + i * (*offset), board[pos]))break;
			}
		}
	}
	return count;
}
short linemove(short board[], short pos, short* possible){
	short count = 0;
	short offs[] = {-1, 1, 8, -8, 0};
	short tmp, *offset = offs;
	short boundary(short offset){
		if( offset == -1 || offset == 1){
			if(offset == -1) return pos % 8;
			else return (7 - (pos % 8));
		}
		if(offset == 8) return 7 - (pos/8);
		return pos / 8;
	}
	possible++;
	for(; *offset != 0; offset++){
		tmp = boundary(*offset);
		for(short i = 1; i <= tmp; i++){
			if(board[pos] % 8 != 1){
				if(inspect(board, pos + i * (*offset), board[pos])){
					if(!psmkr(board, pos, pos + i * (*offset))){ 
						*possible = pos + i * (*offset); possible++; count++;}
					if(inspect(board, pos + i * (*offset), board[pos]) == 2) break;
				}
				else break;
			}
			else{
				if(inspect(board, pos + i * (*offset), board[pos]) == 2){ 
					*possible = pos + i * (*offset); possible++; count++;
					break;
				}
				else if(!inspect(board, pos + i * (*offset), board[pos]))break;
			}
		}
	}
	return count;
}
short knightmove(short board[], short pos, short *possible){
	short offset[9];
	possible++;
	short count = 0;
	short list(short pos, short *off){
		short count = 0;
		off++;
		if(pos % 8 > 0){
			if(pos / 8 < 6){ *off = 15; off++; count++;}
			if(pos / 8 > 1){*off = -17; off++; count++;}
			if(pos % 8 > 1){
				if(pos / 8 < 7){ *off = 6; off++; count++;}
				if(pos / 8 > 0 ){ *off = -10; off++; count++;}
			}
		}
		if(pos % 8 < 7){
			if(pos / 8 < 6){ *off = 17; off++; count++;}
			if(pos / 8 > 1){*off = -15; off++; count++;}
			if(pos % 8 < 6){
				if(pos / 8 < 7){ *off = 10; off++; count++;}
				if(pos / 8 > 0 ){ *off = -6; off++; count++;}
			}
		}
		return count;
	}
	offset[0] = list(pos, offset);
	for(short i = 1; i <= offset[0]; i++){
		if(board[pos] % 8 == 5){
			if(inspect(board, pos + offset[i], board[pos])){
				if(!psmkr(board, pos, pos + offset[i])){
					*possible = pos + offset[i];
					possible++;
					count++;
				}
			}
		}
		else{
			if(inspect(board, pos + offset[i], board[pos]) == 2){
				*possible = pos + offset[i];
				possible++;
				count++;
			}
		}
	}
	return count;
}
void arra(short arr[28]){
	for(int i = 1; i <= arr[0]; i++){
	       printf("%d\n", arr[i]);
	}
}	

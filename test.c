#include<stdio.h>
#define string "8/2P5/Pq4NK/1p3Ppp/2P3k1/p5p1/5R2/r5b1"
void display(short b[]);
void fen(char *a, short b[]);
short linemove(short board[], short pos, short* possible);
short queenmove(short board[], short pos, short* possible);
short knightmove(short board[], short pos, short *possible);
short pawnmove(short board[], short pos, short* possible);
short kingmove(short board[], short pos, short* possible);
short diagonalmove(short board[], short pos, short *possible);
void arra(short arr[]);
#include"display.c"
short const none = 0;
short const K = 9, Q = 10, R = 11, B = 12, N = 13, P = 14;
short const k = 17, q = 18, r = 19, b =  20, n = 21, p = 22;
short kpos[2];
short kingthreat(short board[], short pos){
	short possible[14];
	possible[0] = diagonalmove(board, pos, possible);
	for(short i = 1; i <= possible[0]; i++){
		if(board[possible[i]] % 8 == 2 || board[possible[i]] % 8 == 4) return 1;
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
void picker(int value, short board[], short pos, short* possible){
	short (*piecesmove[])(short*, short, short*) = {kingmove, queenmove, linemove, diagonalmove, knightmove, pawnmove};
	*possible = (*piecesmove[value%8])(board, pos, possible);
}
void movmkr(short destpos, short board[], short pos, short* possible){
	static short enpos = 0;
	if(board[enpos] > 22) board[enpos] = 0;
	if(board[pos] % 8 == 6) if(pos < 16 && pos > 47){ if(destpos == (pos + 16)){ board[pos + 8] = 24; enpos = pos + 8; }else if(destpos == (pos - 16)){ board[pos - 8] = 25; enpos = pos - 8;}}
	else if(board[pos] % 8 == 1){if(board[pos] > 16){if(!*(possible + 32)) *(possible + 32) = 1; kpos[1] = destpos;} else{ if(!*(possible + 29)) *(possible + 29) = 1; kpos[0] = destpos;}
		if(destpos == pos - 2){board[pos - 1] = board[pos - 3]; board[pos + 4] = none;}		
		if(destpos == pos + 2){board[pos + 1] = board[pos + 4]; board[pos + 4] = none;}		
	}
	else if(board[pos] % 8 == 3){
		if(board[pos] > 16){
			if(pos == 56) if(!*(possible + 31)) *(possible + 31) = 1;
			if(pos == 63) if(!*(possible + 33)) *(possible + 33) = 1;
		}
		else{
			if(pos == 0) if(!*(possible + 28)) *(possible + 29) = 1;
			if(pos == 7) if(!*(possible + 30)) *(possible + 30) = 1;
		}	
	}
}
short psmkr(short board[], short pos, short destpos){
	short b[64], kp[2];
	kp[0] = kpos[0];
	kp[1] = kpos[1];
	for(short i = 0; i < 64; i++) b[i] = board[i];
	b[destpos] = b[pos];
	b[pos] = none;
	if(board[pos] > 16){if(board[destpos] == k) kp[1] = destpos; return kingthreat(b, kp[1]);}
	if(board[destpos] == K) kp[0] = destpos;
	return kingthreat(b, kp[0]);
}
void main(){
	short board[64], po[28];
	char status[64];
	for(short i = 0; i < 64; i++) status[i] = ' ';
	for(int i = 0; i < 64; i++) board[i] = none;
	fen(string, board);
	disply(board, status);
	po[0] = knightmove(board, 46, po);
	arra(po);
	printf("%d", kingthreat(board, 47));
}
void fen(char *a, short bo[]){
	for(int i = 56; i > -1;){
		if(*a > 97){
			if(*a == 'p') bo[i] = p;
			else if(*a == 'n') bo[i] = n;
			else if(*a == 'b') bo[i] = b;
			else if(*a == 'r') bo[i] = r;
			else if(*a == 'q') bo[i] = q;
			else {bo[i] = k; kpos[1] = i;}
			i++;
		}
		else if(*a > 65){
			if(*a == 'P') bo[i] = P;
			else if(*a == 'N') bo[i] = N;
			else if(*a == 'B') bo[i] = B;
			else if(*a == 'R') bo[i] = R;
			else if(*a == 'Q') bo[i] = Q;
			else {bo[i] = K; kpos[0] = i;}
			i++;
		}
		else if(*a > 48){
			for(int j = 1; j <= (*a - 48); j++) bo[j] = none;
			i = i + (*a - 48);
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
}
short kingmove(short board[], short pos, short* possible){
	short count = 0, *ismoved = possible + 28;
	possible++;
	short castling(short v, short start){
		ismoved += start;	
		for(int i = 1; i < 3; i++){ if(*ismoved) return 0; ismoved++;}
		if(v == 1) if(board[pos + 2] == none) return 1;
		if(*(ismoved - 3)) return 0;
		if(board[pos - 2] == none && board[pos - 3] == none) return 1;
		return 0;
	}
	if(pos % 8 >= 1){
		if(inspect(board, pos - 1, board[pos])){*possible = pos - 1; possible++; count++;
			if(board[pos] & 16 == 16){
				if(castling(-1, 4)){ *possible = pos - 2; possible++; count++; *possible = pos - 3; possible++; count++;}
			}
			else{
				if(castling(-1, 2)){ *possible = pos - 2; possible++; count++; *possible = pos - 3; possible++; count++;}
			}
		}
		if(inspect(board, pos + 7, board[pos])){if(pos + 7 < 64){*possible = pos + 7; possible++; count++;}}		
		if(inspect(board, pos - 9, board[pos])){if(pos - 9 > 0){*possible = pos - 9; possible++; count++;}}		
	}
	if(7 - (pos % 8) >= 1){
		if(inspect(board, pos + 1, board[pos])){*possible = pos + 1; possible++; count++;
			if(board[pos] & 16 == 16){
				if(castling(1, 4)){ *possible = pos + 2; possible++; count++;}	
			}
			else{
				if(castling(1, 2)){ *possible = pos + 2; possible++; count++;}	
			}
		}		
		if(inspect(board, pos - 7, board[pos])){if(pos - 7 > -1)*possible = pos - 7; possible++; count++;}
		if(inspect(board, pos + 9, board[pos])){if(pos + 9 < 64){*possible = pos + 9; possible++; count++;}}
	}
	if(inspect(board, pos + 8, board[pos])){if(pos + 8 < 64){*possible = pos + 8; possible++; count++;}}
	if(inspect(board, pos - 8, board[pos])){if(pos - 8 > -1){*possible = pos - 8; possible++; count++;}}
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
					if(psmkr(board, pos, pos + i * (*offset))){ 
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
					if(psmkr(board, pos, pos + i * (*offset))){ 
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
			if(!psmkr(board, pos, pos + offset[i])){
				*possible = pos + offset[i];
				possible++;
				count++;
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
/*short knightmove(short board[], short pos, short *possible){
	short count = 0;
	possible++;
	if(pos % 8 >= 1){
		if(pos % 8 >= 2){
			if(inspect(board, pos + 6, board[pos])){if(pos + 6 < 64){if(psmkr(board, pos, pos + i * (*offset))){*possible = pos + 6; possible++; count++;}}}
			if(inspect(board, pos - 10, board[pos])) {if(pos - 10 > -1){ if(psmkr(board, pos, pos + i * (*offset))){*possible = pos - 10; possible++; count++;}}}
		}
		if(inspect(board, pos + 15, board[pos])){ if(pos + 15 < 64){if(psmkr(board, pos, pos + i * (*offset))){*possible = pos + 15; possible++; count++;}}}
		if(inspect(board, pos - 17, board[pos])){if(pos - 15 > -1){ if(psmkr(board, pos, pos + i * (*offset))){*possible = pos - 17; possible++; count++;}}}
	}	
	if(7 - (pos % 8) >= 1){
		if(7 - (pos % 8) >= 2){
			if(inspect(board, pos - 6, board[pos])) {if(pos - 6 > -1){if(psmkr(board, pos, pos + i * (*offset))){*possible = pos - 6; possible++; count++;}}}
			if(inspect(board, pos + 10, board[pos])) {if(pos + 10 < 64){if(psmkr(board, pos, pos + i * (*offset))){*possible = pos + 10; possible++; count++;}}}
		}
		if(inspect(board, pos - 15, board[pos])) {if(pos - 15 > -1){if(psmkr(board, pos, pos + i * (*offset))){*possible = pos - 15; possible++; count++;}}}
		if(inspect(board, pos + 17, board[pos])) {if(pos + 17 < 64){if(psmkr(board, pos, pos + i * (*offset))){*possible = pos + 17; possible++; count++;}}}
	}
	return count;
}*/
void arra(short arr[28]){
	for(int i = 1; i <= arr[0]; i++){
	       printf("%d\n", arr[i]);
	}
}	

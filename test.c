#include<stdio.h>
#define string "r1b1k1nr/p2p1pNp/n2B4/1p1NP2P/6P1/3p1Q2/P1P1K3/q5b1"
void display(short b[]);
void fen(char *a, short b[]);
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
void main(){
	short board[64], po[28], tmp;
	for(int i = 0; i < 64; i++) board[i] = none;
	fen(string, board);
	po[0] = pawnmove(board, 12, po);
	arra(po);
}
void fen(char *a, short bo[]){
	for(int i = 56; i > -1;){
		if(*a > 97){
			if(*a == 'p') bo[i] = p;
			else if(*a == 'n') bo[i] = n;
			else if(*a == 'b') bo[i] = b;
			else if(*a == 'r') bo[i] = r;
			else if(*a == 'q') bo[i] = q;
			else bo[i] = k;
			i++;
		}
		else if(*a > 65){
			if(*a == 'P') bo[i] = P;
			else if(*a == 'N') bo[i] = N;
			else if(*a == 'B') bo[i] = B;
			else if(*a == 'R') bo[i] = R;
			else if(*a == 'Q') bo[i] = Q;
			else bo[i] = K;
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
	if(board[pos] == none) return 1;
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
		if(pos % 8 > 0)if(inspect(board, pos - 9, board[pos]) == 2){*possible = pos - 9; possible++; count++;}
		if(pos % 8 < 7)if(inspect(board, pos - 7, board[pos]) == 2){*possible = pos - 7; possible++; count++;}
	}
	else{
		if(board[pos + 8] == none){*possible = pos + 8; possible++; count++;
			if(pos < 16){if(board[pos + 16] == none){*possible = pos + 16; possible++; count++;}}}
		if(pos % 8 > 0)if(inspect(board, pos + 7, board[pos]) == 2){*possible = pos + 7; possible++; count++;}
		if(pos % 8 < 7)if(inspect(board, pos + 9, board[pos]) == 2){*possible = pos + 9; possible++; count++;}
	}
	return count;
}
short kingmove(short board[], short pos, short* possible, short* ismoved){
	short count = 0;
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
		if(inspeact(board, pos - 1, board[pos])){*possible = pos - 1; possible++; count++;
			if(board[pos] & 16 = 16){
				if(castling(-1, 4){ *possible = pos - 2; possible++; count++; *possible = pos - 3; possible++; count++;}
			}
			else{
				if(castling(-1, 2){ *possible = pos - 2; possible++; count++; *possible = pos - 3; possible++; count++;}
			}
		}
		if(inspect(board, pos + 7, board[pos])){if(pos + 7 < 64){*possible = pos + 7; possible++; count++;}}		
		if(inspect(board, pos - 9, board[pos])){if(pos - 9 > 0){*possible = pos - 9; possible++; count++;}}		
	}
	if(7 - (pos % 8) >= 1){
		if(inspect(board, pos + 1, board[pos])){*possible = pos + 1; possible++; count++;
			if(board[pos] & 16 = 16){
				if(castling(1, 4){ *possible = pos + 2; possible++; count++;}	
			}
			else{
				if(castling(1, 2){ *possible = pos + 2; possible++; count++;}	
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
		int i = 0;
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
			if(inspect(board, pos + i * (*offset), board[pos])){
				*possible = pos + i * (*offset); possible++; count++;
				if(inspect(board, pos + i * (*offset), board[pos]) == 2) break;
			}
			else break;
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
		if(offset == 8) return 64;
		return 0;
	}
	possible++;
	for(; *offset != 0; offset++){
		tmp = boundary(*offset);
		for(short i = 1; i <= tmp; i++){
			if(inspect(board, pos + i * (*offset), board[pos])){ 
				*possible = pos + i * (*offset); possible++; count++;
				if(inspect(board, pos + i * (*offset), board[pos]) == 2) break;	
			}
			else break;
		}
	}
	return count;
}
short knightmove(short board[], short pos, short *possible){
	short count = 0;
	possible++;
	if(pos % 8 >= 1){
		if(pos % 8 >= 2){
			if(inspect(board, pos + 6, board[pos])){if(pos + 6 < 64){*possible = pos + 6; possible++; count++;}}
			if(inspect(board, pos - 10, board[pos])) {if(pos - 10 > -1){ *possible = pos - 10; possible++; count++;}}
		}
		if(inspect(board, pos + 15, board[pos])){ if(pos + 15 < 64){*possible = pos + 15; possible++; count++;}}
		if(inspect(board, pos - 17, board[pos])){if(pos - 15 > -1){ *possible = pos - 17; possible++; count++;}}
	}	
	if(7 - (pos % 8) >= 1){
		if(7 - (pos % 8) >= 2){
			if(inspect(board, pos - 6, board[pos])) {if(pos - 6 > -1){*possible = pos - 6; possible++; count++;}}
			if(inspect(board, pos + 10, board[pos])) {if(pos + 10 < 64){*possible = pos + 10; possible++; count++;}}
		}
		if(inspect(board, pos - 15, board[pos])) {if(pos - 15 > -1){*possible = pos - 15; possible++; count++;}}
		if(inspect(board, pos + 17, board[pos])) {if(pos + 17 < 64){*possible = pos + 17; possible++; count++;}}
	}
	return count;
}
void arra(short arr[28]){
	for(int i = 1; i <= arr[0]; i++){
	       printf("%d\n", arr[i]);
	}
}	

// This code is authored by serenov. Feel free to edit.
#define Q_MAX 27
#define R_MAX 14
#define B_MAX 13
#define K_MAX 8
#define N_MAX 8
short inspect(short board[], short pos, short color){
	if(color > 8) color = 8;
	else color = 0;
	if(board[pos] == none) return 1;
	else if(color < board[pos] ) return 0;  
	return 1;
}
void linemove(short board[], short pos, short* possible){
	short const offs[] = {-1, 1, 8, -8, 0};
	short tmp, *offset = offs;
	short count = 0;
	short boundary(short offset){
		if( offset = -1 || offset = 1){
			if(offset = -1) return pos % 8;
			else return (7 - (pos % 8));
		}
		if(offset = 8) return 7 - (pos/8);
		return pos/8;
	}
	possible++;
	for(; *offset != 0; offset++){
		tmp = boundary(*offset);
		for(short i = 1; i <= tmp; i++){
			if(inspect(board[pos], pos + i * (*offset), board[pos])){ 
				*possible = pos + i * (*offset); possible++; count++;
			}
		}
	}
	*(possible - count - 1) = count; 
}
void diagonalmove(short board[], short pos, short *possible){
	short const offs[] = {-9, 9, -7, 7, 0};
	short tmp, count = 0, *offset = offs;
	short boundary(short offset){
		if( offset = -9 || offset = 7) return pos % 8;
		return (7 - (pos % 8));
	}
	for(; *offset != 0; offset++){
		tmp = boundary(*offset);
		for(short i = 1; i <= tmp; i++){
			if(inspect(board[pos], pos + i * (*offset), board[pos])){
				*possible = pos + i * (*offset); possible++; count++;
			}
		}
	}
	*(possible - count - 1) += count;
}
void knightmove(short board[], short pos, short possible[]){
	//short const offset[] = {-15, 15, -17, 17, -6, 6, -10, 10};
	short count = 0;
	if(pos % 8 >= 1){
		if(pos % 8 >= 2){
			if(inspect(board[pos], pos + 6), board[pos]) {if(pos + 6 < 64){*possible = pos + 6; possible++; count++;}}
			if(inspect(board[pos], pos - 10, board[pos])) {if(pos - 15 > -1){ *possible = pos - 10; possible++; count++;}}
		}
		if(inspect(board[pos], pos + 15, board[pos])){ if(pos + 15 < 64){*possible = pos + 15; possible++; count++;}}
		if(inspect(board[pos], pos - 17, board[pos])){if(pos - 15 > -1){ *possible = pos - 17; possible++; count++}}
	}	
	if(7 - (pos % 8) >= 1){
		if(7 - (pos % 8) >= 2){
			if(inspect(board[pos], pos - 6, board[pos])) {if(pos - 6 > -1){*possible = pos - 6; possible++; count++;}}
			if(inspect(board[pos], pos + 10, board[pos])) {if(pos + 10 < 64){*possible = pos + 10; possible++; count++;}}
		}
		if(inspect(board[pos], pos - 15, board[pos])) {if(pos - 15 > -1){*possible = pos - 15; possible++; count++;}}
		if(inspect(board[pos], pos + 17, board[pos])) {if(pos + 17 < 64){*possible = pos + 17; possible++; count++}}
	}
	possible[27] = count;
}
void kingmove(short board[], short pos, short possible[]){
	short count = 0;
	if(pos % 8 >= 1){
		if(inspect(board[pos], pos - 1, board[pos])){*possible = pos - 1; possible++; count++;}
		if(inspect(board[pos], pos + 7, board[pos])){if(pos + 7 < 64){*possible = pos + 7; possible; count++;}}		
		if(inspect(board[pos], pos - 9, board[pos])){if(pos - 9 > 0){*possible = pos - 9; possible; count++;}}		
	}
	if(7 - (pos % 8) >= 1){
		if(inspect(board[pos], pos + 1, board[pos])){*possible = pos + 1; possible++; count++;}
		if(inspect(board[pos], pos - 7, board[pos])){if(pos - 7 > -1)*possible = pos + 1; possible++; count++;}
		if(inspect(board[pos], pos + 9, board[pos])){if(pos + 9 < 64){*possible = pos + 9; possible++; count++;}}
	}
	if(inspect(board[pos], pos + 8, board[pos])){if(pos + 8 < 64){*possible = pos + 8; possible++; count++;}}
	if(inspect(board[pos], pos - 8, board[pos])){if(pos - 8 > -1){*possible = pos + 1; possible++; count++;}}
	possible[27] = count;
}
void pawnmove(short board[], short pos, short possible[]){
	short count = 0;
	if(board[pos] > 8){
		if(inspect(board[pos], pos - 8, board[pos])){*possible = pos - 8; possible++; count++}
		if(pos > 47){if(inspect(board[pos], pos - 16, board[pos])){*possible = pos - 16; possible++; count++}}
	}
	else{
		if(inspect(board[pos], pos + 8, board[pos])){*possible = pos + 8; possible++; count++}
		if(pos < 16){if(inspect(board[pos], pos + 16, board[pos])){*possible = pos + 16; possible++; count++}}
	}
	possible[27] = count;
}
			

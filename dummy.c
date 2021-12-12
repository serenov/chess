void knightmove(short board[], short pos, short *possible){
	short offset[9];
	possible++;
	short list(short pos, short *off){
		short count = 0;
		off++;
		if(pos % 8 > 0){
			if(pos / 8 < 6){ *off = 15; off++; count++;}
			if(pos / 8 > 1){*off = -17; off++; count++;}
			if(pos % 8 > 1){
				if(pos / 8 < 7){ *off = 6; off++; count++;}
				if(pos / 8 > 0 ){ *off = -9; off++; count++;}
			}
		}
		if(pos % 8 < 7){
			if(pos / 8 < 6){ *off = 17; off++; count++;}
			if(pos / 8 > 1){*off = -15; off++; count++;}
			if(pos % 8 < 6){
				if(pos / 8 < 7){ *off = 9; off++; count++;}
				if(pos / 8 > 0 ){ *off = -6; off++; count++;}
			}
		}
		return count;
	}
	offset[0] = list(pos, offset);
	for(i = 1; i <= offset[0]; i++){
		if(kingthreat(board, pos, *possible = pos + offset[i];
	}
	return offset[0];
}
short castling(short board[], short pos, short *ismoved, short offset){
	if(*ismoved);
	else if(*(ismoved + offset));
	else{ 
		if(offset == -1)if(board[pos - 2] == none);
		else if(offset == 1)if(board[pos + 2] == none && board[pos + 3] == none);
		else return 0;
		return 1;
	}
	return 0

}
int pawnmove(short board[], short pos, short *possible){
	short offset[9], count = 0;
	possible++
	short color = (board[pos] > 16)? 32: 29;
	short list(short pos, short *off){
		short count = 0;
		off++;
	}
}
int kingmove(short board[], short pos, short *possible){
	short offset[9], count = 0;
	possible++
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
			if(!psmkr(board, pos, pos + offset[i])){
				*possible = pos + offset[i];
				count ++; possible++;
				if(castling(board, pos, possible + color - count, offset[i])){
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
int pawnmove(short board[], short pos, short *possible){
	short offset[5], count = 0;
	possible++
	short color = (board[pos] > 16)? -1: 1;
	short list(short pos, short *off){
		short count = 0;
		off++;
		if(color == 1){
			if(pos / 8 < 8 && baord[pos + 8] == none){ 
				*off = 8; off++; count++;
				if(pos / 8 == 1 && board[pos + 16] == none){ *off = 16; off++; count++;}
			}
			if(pos % 8 > 0){
				if(inspect(board, pos + 7, board[pos]) == 2 || board[pos] == 25){
					*off = 7; off++; count++;
				}
				if(inspect(board, pos + 9, board[pos]) == 2 || board[pos] == 25){
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
				if(inspect(board, pos - 7, board[pos]) == 2 || board[pos] == 24){
					*off = -7; off++; count++;
				}
				if(inspect(board, pos - 9, board[pos]) == 2 || board[pos] == 24){
					*off = -9; off++; count++;
				}
			}
		}
		return count;
	}
	offset[0] = list(pos, offset);
	for(short i = 1; i <= offset[0]; i++){
		if(!posmkr(board, pos, pos + offset[i])){
			*possible = pos + offset[i];
			count++; possible++;
		}
	}
	return count;
}

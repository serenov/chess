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
short listp(short board[], short pos, short *off, short color){
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
short pawnmove(short board[], short pos, short* possible){
	short offset[5], count = 0;
	possible++;
	short color = (board[pos] > 16)? -1: 1;
	offset[0] = listp(board, pos, offset, color);
	for(short i = 1; i <= offset[0]; i++){
		if(!psmkr(board, pos, pos + offset[i])){
			*possible = pos + offset[i];
			count++; possible++;
		}
	}
	return count;
}
short castling(short board[], short pos, short *ismoved, short offset){
	if(*ismoved);
	else if(*(ismoved + offset));
	else{
		if(offset == -1){
			if(board[pos - 2] == none);
		}
		else if(offset == 1){
			if((board[pos + 2] == none) && (board[pos + 3] == none));
		}
		else return 0;
		return 1;
	}
	return 0;
}
short listk(short pos, short *off){
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
short kingmove(short board[], short pos, short *possible){
        short offset[9], count = 0;
        possible++;
        short color = (board[pos] > 16)? 32: 29;
        offset[0] = listk(pos, offset);
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
short boundaryd(short pos, short offset){
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
short diagonalmove(short board[], short pos, short *possible){
	short offs[] = {-9, 9, -7, 7, 0};
	short tmp, count = 0, *offset = offs;
	possible++;
	for(; *offset != 0; offset++){
		tmp = boundaryd(pos, *offset);
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
short boundaryl(short pos, short offset){
	if( offset == -1 || offset == 1){
		if(offset == -1) return pos % 8;
		else return (7 - (pos % 8));
	}
	if(offset == 8) return 7 - (pos/8);
	return pos / 8;
}
short linemove(short board[], short pos, short* possible){
	short count = 0;
	short offs[] = {-1, 1, 8, -8, 0};
	short tmp, *offset = offs;
	possible++;
	for(; *offset != 0; offset++){
		tmp = boundaryl(pos, *offset);
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
short listn(short pos, short *off){
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
short knightmove(short board[], short pos, short *possible){
	short offset[9];
	possible++;
	short count = 0;
	offset[0] = listn(pos, offset);
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
short nonemove(short board[], short pos, short *possible){
	return 0;
}
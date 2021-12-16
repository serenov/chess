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
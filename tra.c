void search(short board[], short list[], short turn, short depth){
	short possible[34], kp[2], captured = none;
	static short count = 0;
	kp[0] = kpos[0];
	kp[1] = kpos[1];
	for(short i = 0; i < 64; i++){
		if(board[i] != none){
			if((board[i] & turnd(turn)) >= 8){
				possible[0] = picker(board, i, possible);
				count += possible[0];
				for(short j = 1; j <= possible[0]; j++){
					if(board[possible[j]] != none) captured = board[possible[j]];
					movmkr(possible[j], board, i, possible);
					search(board, possible + 28, !turn, depth + 1);
					board[i] = board[possible[j]];
					board[possible[j]] = captured;
					captured = none;
					kpos[0] = kp[0];
					kpos[1] = kp[1];
				}	
			}
		}
	}
}

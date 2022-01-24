short stalemate(short board[], short turn){
	short possible[34], color = (turn == 0)? 8: 16;
	for(short i = 0; i < 64; i++){
		if((board[i] & color) >= 8){
			if(possible[0] = picker(board, i, possible) > 0) return 0;
		}
	}	
	return 1;
}

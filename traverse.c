short search(){
	static short count = 0;
	for(short i = 0; i < 64; i++){
		if(board[i] != none){
			possible[0] = picker(baord, i, possible);
			for(short j = 1; j <= possible[0]; j++){
				movmkr(possible[j], board, i, possible);
				board[i] = board[possible[j]];
				board[possible[j]] = none;
			}		
		}	
	}
}

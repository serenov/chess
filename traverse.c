short turnd(short turn){
	if(turn == 0) return 8;
	return 16;
}
short checkmate(short board[], short kpos){
	if(kingthreat(board, kpos)){
		for(short i = 0; i < 64; i++){
			if(picker(board, i, possible))
		}
	}
}
void search(short board[], short turn){
	static short count = 0;
	static short depth = 0;
	if(depth == 8 || checkmate()) return;
	int b[64];
	for(short i = 0; i < 64; i++)b[i] = board[i];
	for(short i = 0; i < 64; i++){
		if(board[i] != none){		
			if(board[i] & turnd(turn) >= 8){
				possible[0] = picker(baord, i, possible);
				count += possible[0];
				for(short j = 1; j <= possible[0]; j++){
					depth++;
					movmkr(possible[j], board, i, possible);
					search(b, !turn)
					board[i] = board[possible[j]];
					board[possible[j]] = none;
				}		
			}
		}		
	}
	if(depth == 1) printf("%d\n", depth);
}

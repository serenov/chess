short turnd(short turn){
	if(turn == 0) return 8;
	return 16;
}
short checkmate(short board[], short kpos, short *possible){
	printf("checkpoint 2.5\n");
	if(kingthreat(board, kpos)){
		for(short i = 0; i < 64; i++){
			if(!picker(board, i, possible)){
				return 1;	
				printf("checkpoint 3\n");
			}
		}
	}
	return 0;
}
void search(short board[], short poss[], short turn){
	static int count = 0;
	static short depth = 0;
	short possible[34], b[64], kp[2];
	kp[0] = kpos[0], kp[1] = kpos[1];
	printf("checkpoint 1\n");
	for(short i = 28; i < 34; i++)possible[i] = poss[i];
	for(short i = 0; i < 64; i++)b[i] = board[i];
	if(depth == 1 || checkmate(b, kpos[turn], possible)) return;
	for(short i = 0; i < 64; i++){
		if(board[i] != none){		
			if((board[i] & turnd(turn)) >= 8){
				possible[0] = picker(board, i, possible);
				count += possible[0];
				for(short j = 1; j <= possible[0]; j++){
					depth++;
					movmkr(possible[j], board, i, possible);
					printf("checkpoint 2\n");
					search(b, possible, !turn);
					board[i] = board[possible[j]];
					board[possible[j]] = none;
					kpos[0] = kp[0], kpos[1] = kp[1];
				}		
			}
		}		
	}
	if(depth == 1) printf("%d\n", depth);
}

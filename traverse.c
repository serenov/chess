short turnd(short turn){
	if(turn == 0) return 8;
	return 16;
}
void search(short board[], short* list, short turn, short depth){
	if(depth > 2 ) return;
        short possible[34], captured = none, kp[2];
        static int count = 0, check = 0;
	for(short i = 28; i < 34; i++) possible[i] = *(list + i); 
        kp[0] = kpos[0];
        kp[1] = kpos[1];
	char status[64];
	for(short i = 0; i < 64; i++) status[i] = ' ';
	if(kingthreat(board, kpos[turn])){
		check++;
		for(short i = 0; i < 64; i++){
			if((board[i] & turnd(turn)) >= 8){
				if(!picker(board, i, possible)) return;
			}
						
		}
	}
<<<<<<< HEAD
	for(short i = 0; i < 64; i++){
                if(board[i] != none){
                        if((board[i] & turnd(turn)) >= 8){
                                possible[0] = picker(board, i, possible);
                                count += possible[0];
                                for(short j = 1; j <= possible[0]; j++){
                                        if(board[possible[j]] != none){ check++; captured = board[possible[j]];}
                                        movmkr(possible[j], board, i, possible);
					printf("at depth %d", depth);
					disply(board, status);
					printf(" ***************\n");
                                        search(board, possible, !turn, depth + 1);
                                        board[i] = board[possible[j]];
                                        board[possible[j]] = captured;
					captured = none;
                                        kpos[0] = kp[0];
                                        kpos[1] = kp[1];
                                }
                        }
                }
        }
	printf("%d %d\n", count, check);
=======
	return 0;
}
void search(short board[], short poss[], short turn){
	static long int count = 0;
	static short depth = 0;
	short capturedpiece = none;
	short possible[34], b[64], kp[2];
	kp[0] = kpos[0], kp[1] = kpos[1];
	for(short i = 28; i < 34; i++)possible[i] = poss[i];
	for(short i = 0; i < 64; i++)b[i] = board[i];
	if(depth > 2 || checkmate(b, kpos[turn], possible)) return;
	for(short i = 0; i < 64; i++){
		if(board[i] != none){		
			if((board[i] & turnd(turn)) >= 8){
				printf("%d for depth %d\n", i, depth);
				possible[0] = picker(board, i, possible);
				count += possible[0];
				for(short j = 1; j <= possible[0]; j++){
					depth++;
					if(board[i] & board[possible[j]] < 8){ capturedpiece = board[possible[j]];}
					movmkr(possible[j], board, i, possible);
					search(b, possible, !turn);
					board[i] = board[possible[j]];
					board[possible[j]] = capturedpiece;
					kpos[0] = kp[0], kpos[1] = kp[1];
					depth--;
				}		
			}
		}		
	}
	printf("count is %ld\n", count);
>>>>>>> 6b4b89b28de08403b84ba965542059efc6402480
}


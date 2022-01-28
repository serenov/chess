char* t(short turn){ if(turn == 0) return "WHITE"; return "BLACK";}
short d(short turn){if(turn == 0) return 8; return 16;}
void decode(short possible[], char status[], char c){ for(short i = 1; i <= possible[0]; i++) status[possible[i]] = c;}

short io(short board[], char status[], short possible[], short turn, short *checkmate){
    short pos, destpos, move[2];
    
    if(turn == 1){
	traverse(board, possible + 28, turn, 0, move);
    	printf("%d %d\n", move[0], move[1]);
	picker(board, move[0], possible);
    	movmkr(move[1], board, move[0], possible);
	//scanf("%hd", move);
	goto jump;
    }
    display(board, status);
    printf("PICK A PIECE: ");
    scanf("%hd", &pos);

    //	checks for appropriate input.
    if((d(turn) & board[pos]) < 8){
	    system(CLEAR);
	    printf("INVALID SELECTION\n"); 
	    return 0;
    }
    
    //	marks all the possible squares. 
    picker(board, pos, possible);
    decode(possible, status, '*');
    
    //	For promotions.
    if(board[pos] % 8 == 6) if(possible[0] >= 4)
	    if(possible[13] == -2){
		    
		    printf("2 for queen 3 for rook 4 for bishop 5 for knight.\nstrictly type the numbers given: "); 
		    scanf("%hd", possible + 14); 
		    
		    possible[14] = 8 + 8 * turn + possible[14];
	   
	    }

    system(CLEAR);
    
    display(board, status);
    printf("PICK A MARKED SQUARE: ");
    scanf("%hd", &destpos);
    
   //	checks if the selected sqare is marked.
    if(status[destpos] == '*')movmkr(destpos, board, pos, possible);
    else{system(CLEAR); printf("INVALID SQUARE\n"); decode(possible, status, ' '); return 0;}
    
    decode(possible, status, ' ');
    system(CLEAR);
    //	for check or checkmate.
jump:
    if(kingthreat(board, kpos[!turn])){
        for(short i = 0; i < 64; i++){
            if((board[i] & d(!turn)) < 8);
            else{
            	if(picker(board, i, possible)){printf("CHECK ON %s'S KING!\n", t(!turn)); return 1;}
            }
        }
        *checkmate = 1;	
    }

    return 1;

}
void game(){
	short checkmate = 0, board[64], possible[35], mov = 0, turn;
	char status[64];
	for(short i = 0; i < 64; i++) {board[i] = none; status[i] = ' ';}
	for(short i = 28; i < 33; i++) possible[i] = 1;
	fen(string, board, possible + 28); 
		system(CLEAR);
	do{
		turn = mov % 2;
		printf("IT'S %s'S TURN\n", t(turn));
		mov += io(board, status, possible, turn, &checkmate);
	}while(!(checkmate || stalemate(board, !turn)));

	display(board, status);

	if(checkmate == 1)printf("CHECKMATE! %s IS VICTORIOUS!\n", t(turn));
	else printf("DRAW BY STALEMATE!\n");
}

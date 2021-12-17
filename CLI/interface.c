char* t(short turn){ if(turn == 0) return "WHITE"; return "BLACK";}
short d(short turn){if(turn == 0) return 8; return 16;}
short decode(short possible[], char status[], char c){ for(short i = 1; i <= possible[0]; i++) status[possible[i]] = c;}
short io(short board[], char status[], short possible[], short turn, short *checkmate){
    short pos, destpos;
    display(board, status);
    printf("PICK A PIECE: ");
    scanf("%hd", &pos);
    if((d(turn) & board[pos]) < 8){system("clear"); printf("INVALID SELECTION\n"); return 0;}
    picker(board, pos, possible);
    decode(possible, status, '*');
    system("clear");
    display(board, status);
    printf("PICK A MARKED SQUARE: ");
    scanf("%hd", &destpos);
    if(status[destpos] == '*')movmkr(destpos, board, pos, possible);
    else{system("clear"); printf("INVALID SQUARE\n"); decode(possible, status, ' '); return 0;}
    decode(possible, status, ' ');
    system("clear");
    if(kingthreat(board, kpos[!turn])){
        for(short i = 0; i < 64; i++){
            if((board[i] & d(!turn)) < 8);
                else{
                    if(picker(board, i, possible)){printf("CHECK ON %s'S KING!\n", t(!turn)); return 1;
                }
            }
        }
        *checkmate = 1;	
    }
    return 1;

}
void game(){
	short checkmate = 0, board[64], possible[34], mov = 0, turn;
	char status[64];
	for(short i = 0; i < 63; i++) {board[i] = none; status[i] = ' ';}
	fen(string, board, possible + 28); 
		system("clear");
	do{
		turn = mov % 2;
		printf("IT'S %s'S TURN\n", t(turn));
		mov += io(board, status, possible, turn, &checkmate);
	}while(!checkmate);
	display(board, status);
	printf("CHECKMATE! %s IS VICTORIOUS!\n", t(turn));
}
#include<stdlib.h>
void game(){
	short checkmate = 0, board[64], possible[34], mov = 0, turn;
	char status[64];
	for(short i = 0; i < 63; i++) {board[i] = none; status[i] = ' ';}
	fen(string, board, possible + 28); 
	char* t(short turn){ if(turn == 0) return "WHITE"; return "BLACK";}
	short d(short turn){if(turn == 0) return 8; return 16;}
	short decode(char c){ for(short i = 1; i <= possible[0]; i++) status[possible[i]] = c;}
	short io(short turn){
		short pos, destpos;
		disply(board, status);
		printf("PICK A PIECE: ");
		scanf("%hd", &pos);
		if((d(turn) & board[pos]) < 8){system("clear"); printf("INVALID SELECTION\n"); return 0;}
		picker(board, pos, possible);
		decode('*');
		system("clear");
		disply(board, status);
		printf("PICK A MARKED SQUARE: ");
		scanf("%hd", &destpos);
		if(status[destpos] == '*')movmkr(destpos, board, pos, possible);
		else{system("clear"); printf("INVALID SQUARE\n"); decode(' '); return 0;}
		decode(' ');
		system("clear");
		printf("%d\n", board[22]);
		if(kingthreat(board, kpos[!turn])){
			printf("CHECK ON %s KING!", t(!turn));
			for(short i = 0; i < 64; i++){
				if((board[i] & d(!turn)) < 8);
			       	else{
					if(picker(board, i, possible)) return 1;
				}
			}
			checkmate = 1;	
		}
		return 1;

	}
	system("clear");
	do{
		turn = mov % 2;
		printf("IT'S %s'S TURN\n", t(turn));
		mov += io(turn);
	}while(!checkmate);
	disply(board, status);
	printf("CHECKMATE! %s IS VICTORIOUS!\n", t(turn));
}
		

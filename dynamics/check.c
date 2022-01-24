short de(short piece){
	if(piece > 16) return 1;
	return 0;
}
short kingthreat(short board[], short pos){
	short possible[14];
	possible[0] = diagonalmove(board, pos, possible);
	for(short i = 1; i <= possible[0]; i++){
		if(board[possible[i]] % 8 == 2 || board[possible[i]] % 8 == 4) return 1;
		if(board[possible[i]] % 8 == 1 ){
			if(possible[i] == pos + 9 || possible[i] == pos - 9 || possible[i] == pos + 7 || possible[i] == pos - 7) return 1;
		}
		if(board[possible[i]] % 8 == 6){
			if(board[pos] > 16){ if(possible[i] == pos - 9 || possible[i] == pos - 7) return 1;}
			else {if(possible[i] == pos + 9 || possible[i] == pos + 7) return 1;}
		}
	}
	possible[0] = linemove(board, pos, possible);
	for(short i = 1; i <= possible[0]; i++){
		if(board[possible[i]] % 8 == 2 || board[possible[i]] % 8 == 3) return 1;	
		if(board[possible[i]] % 8 == 1 ){
			if(possible[i] == pos + 8 || possible[i] == pos - 8 || possible[i] == pos + 1 || possible[i] == pos - 1) return 1;
		}
	}
	possible[0] = knightmove(board, pos, possible);
	for(short i = 1; i <= possible[0]; i++){
		if(board[possible[i]] % 8 == 5) return 1;	
	}
	/*possible[0] = listk(pos, possible);
	for(short i = 1; i <= possible[0]; i++){
		if(board[possible[i]] % 8 == 1) return 1;	
	}*/
	return 0;
}

void input(){
	while(!checkmate()){
		short pos, destpos;
		printf("PICK A PIECE: ");
		scanf("%d", &pos);
		picker(board, pos, possible);
		printf("PICK A MARKED SQUARE: ");
		scanf("%d", &destpos);
		movmkr(destpos, board, pos, possible);
	}
}
		

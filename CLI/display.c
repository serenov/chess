char dcd(int value){
    char Wpieces[] = {' ','K', 'Q', 'R', 'B', 'N', 'P'}, Bpieces[] = {' ', 'k', 'q', 'r', 'b', 'n', 'p'};
    if(value > 23) return ' ';
    if(value < 16){
        return Wpieces[value % 8];
    }
    return Bpieces[value % 8];
}
void unit(short board[], short start, char status[]){
    printf("------------------------------------------------\n");
    printf("|%02d%c  |%02d%c  |%02d%c  |%02d%c  |%02d%c  |%02d%c  |%02d%c  |%02d%c  |\n", start, status[start], start + 1, status[start + 1], start + 2, status[start + 2], start + 3, status[start + 3], start + 4, status[start + 4], start + 5, status[start + 5], start + 6, status[start + 6], start + 7, status[start + 7]);
    printf("|  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |\n", dcd(board[start]), dcd(board[start + 1]), dcd(board[start + 2]), dcd(board[start + 3]), dcd(board[start + 4]), dcd(board[start + 5]), dcd(board[start + 6]), dcd(board[start + 7]));
    printf("|     |     |     |     |     |     |     |     |\n");
    printf("------------------------------------------------\n");
}
void display(short b[], char status[]){
	for(int i = 56; i >= 0; i = i - 8){
        unit(b, i, status);
	}
}	
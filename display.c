void unit(short board[], short start, char status[]){
    char decode(int value){
        char Wpieces[] = {' ','K', 'Q', 'R', 'B', 'N', 'P'}, Bpieces[] = {' ', 'k', 'q', 'r', 'b', 'n', 'p'};
        if(value > 23) return ' ';
        if(value < 16){
            return Wpieces[value % 8];
        }
        return Bpieces[value % 8];
    }
    printf("------------------------------------------------\n");
    printf("|%02d%c  |%02d%c  |%02d%c  |%02d%c  |%02d%c  |%02d%c  |%02d%c  |%02d%c  |\n", start, status[start], start + 1, status[start + 1], start + 2, status[start + 2], start + 3, status[start + 3], start + 4, status[start + 4], start + 5, status[start + 5], start + 6, status[start + 6], start + 7, status[start + 7]);
    printf("|  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |\n", decode(board[start]), decode(board[start + 1]), decode(board[start + 2]), decode(board[start + 3]), decode(board[start + 4]), decode(board[start + 5]), decode(board[start + 6]), decode(board[start + 7]));
    printf("|     |     |     |     |     |     |     |     |\n");
    printf("------------------------------------------------\n");
}
void disply(short b[], char status[]){
	for(int i = 56; i >= 0; i = i - 8){
        unit(b, i, status);
	}
}	
/*void fen(char *a, short bo[]){
	for(int i = 56; i > -1;){
		if(*a > 97){
			if(*a == 'p') bo[i] = p;
			else if(*a == 'n') bo[i] = n;
			else if(*a == 'b') bo[i] = b;
			else if(*a == 'r') bo[i] = r;
			else if(*a == 'q') bo[i] = q;
			else bo[i] = k;
			i++;
		}
		else if(*a > 65){
			if(*a == 'P') bo[i] = P;
			else if(*a == 'N') bo[i] = N;
			else if(*a == 'B') bo[i] = B;
			else if(*a == 'R') bo[i] = R;
			else if(*a == 'Q') bo[i] = Q;
			else bo[i] = K;
			i++;
		}
		else if(*a > 48){
			for(int j = 1; j <= (*a - 48); j++){ bo[i] = none; i++;}
		}
		else i = i - 16;
		a++;
	}
}
int main(){
    short board[64];
    char status[64];
    for(int i = 0; i < 64; i++) status[i] = ' ';
    fen(string, board);
    display(board, status);
    return 0;
}*/


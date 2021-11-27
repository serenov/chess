#include<stdio.h>
#define string "r1b1k1nr/p2p1pNp/n2B4/1p1NP2P/6P1/3p1Q2/P1P1K3/q5b1"
void display(short b[]);
void fen(char *a, short b[]);
short const none = 0;
short const K = 1, Q = 2, R = 3, B = 4, N = 5, P = 6;
short const k = 9, q = 10, r = 11, b =  12, n = 13, p = 14;
void main(){
	short board[64];
	for(int i = 0; i < 64; i++) board[i] = none;
	fen(string, board);
	display(board);
}
void fen(char *a, short bo[]){
	for(int i = 56; i > -1;){
		printf("%d  ", i);
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
			for(int j = 1; j <= (*a - 48); j++) bo[j] = none;
			i = i + (*a - 48);
		}
		else i = i - 16;
		a++;
	}
	printf("\n");
}
void display(short b[]){
	for(int i = 56; i >= 0; i = i - 8){
		for(int j = 1; j < 9; j++){
			printf("%d\t", b[(i + j)- 1]);
		}
		printf("\n");
	}
}	


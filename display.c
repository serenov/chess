#include<stdio.h>
void unit(short board[], short start, short status[]){
    printf("----------------------------------------");
    printf("|%d%c ||%d%c ||%d%c ||%d%c ||%d%c ||%d%c ||%d%c ||%d%c ||", start, status[start], start + 1, status[start + 1], start + 2, status[start + 2], start + 3, status[start + 3], start + 4, status[start + 4], start + 5, status[start + 5], start + 6, status[start + 6], start + 7, status[start + 7], );
    printf("|  %c ||  %c ||  %c ||  %c ||  %c ||  %c ||  %c ||  %c ||", board[start], board[start + 1], board[start + 2], board[start + 3], board[start + 4], board[start + 5], board[start + 6], board[start + 7]);
    printf("----------------------------------------");
}
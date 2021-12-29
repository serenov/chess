void revertEnpassant(short *board, short *list){
        short capturedpiece = (*(list + 2) > 0)? P: p;
        *(board + *(list + 1) + *(list + 2)) = capturedpiece;
        *(board + *list) = *(board + *(list + 1));
        *(board + *(list + 1)) = none;
}
void revertCastle(short *board, short *list){
        short kingoffs = (*list > 0)? -2: 2;
        short rookoffs = (kingoffs > 0)? -3: 2;
        *(board + kingoffs) = *(board);
        *(board) = none;
        *(baord + rookoffs) = *(board - *(list));
        *(baord - *(list)) = none;
}
void revertRegular(short *board, short *list){
        *(board + *list) = *(board + *(list + 1));
        *(board + *(list + 1)) = *(list + 2);
}
void undo(short *board, short *list, short flag){
	short (*revert[])(short*, short*) = {revertReg, revertEn, revertcastle};
        (*revert[flag])(board, list);
}

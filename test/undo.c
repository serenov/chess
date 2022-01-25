void revertEnpassant(short *board, short *list){
        short capturedpiece = (*(list + 2) > 0)? P: p;
        *(board + *(list + 1) + *(list + 2)) = capturedpiece;
        *(board + *list) = *(board + *(list + 1));
        *(board + *(list + 1)) = none;
}
void revertCastle(short *board, short *list){
        short rookoffs = (*(list + 2) > 0)? *list + 3: *list - 4;
        short kingoffs = (*(list + 2) > 0)? *list + 2: *list - 2;
        *(board + rookoffs) = *(board + *list + *(list + 2));
        *(board + *list + *(list + 2)) = none;
        *(board + *list) = *(board + kingoffs);
        *(board + kingoffs) = none;
}
void revertRegular(short *board, short *list){
        *(board + *list) = *(board + *(list + 1));
        *(board + *(list + 1)) = *(list + 2);
}
void revertPromotion(short *board, short *list){
	*(board + *(list + 1)) = (*(list + 1) > 55)? P: p;
	revertRegular(board, list);
}
void undo(short *board, short *list, short flag){
        void (*revert[])(short*, short*) = {revertRegular, revertEnpassant, revertCastle, revertPromotion};
        (*revert[flag])(board, list);
}

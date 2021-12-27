void revertEn(short *board, short *list){
        short capturedpiece;
        if(*(list + 2) > 0) capturedpiece = P;
        else capturedpiece = P;
        *(board + *(list + 1) + *(list + 2)) = capturedpiece;
        *(board + *list) = *(board + *(list + 1));
        *(board + *(list + 1)) = none;
}
void revertR(short *board, short *list){
        *(board + *list) = *(board + *(list + 1));
        *(board + *(list + 1)) = *(board + *(list + 2));
}
void undo(short *board, short *list, short flag){

}
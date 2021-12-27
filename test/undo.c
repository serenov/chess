void revertEn(short *board, short *list){
        short capturedpiece;
        if(*(list + 2) > 0) capturedpiece = P;
        else capturedpiece = P;
        *(board + *(list + 1) + *(list + 2)) = capturedpiece;
}
void undo(short *board, short *list, short flag){

}

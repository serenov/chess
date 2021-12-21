short turnd(short turn){ if(turn == 0) return 8; return 16;}
void undo(short *pos, short *prevpos, short *enpassant){
        *prevpos = *pos;
        *pos = none;
        *enpassant = -1;
}
void init(short *kp){
        *kp = kpos[0];
        *(kp + 1) = kpos[1];
}
void traverse(short board[], short *possible, short turn, short depth){
        short tpossible[35], capturedpiece = none;
        for(short i = 0; i < 7; i++) tpossible[i + 28] = *(possible + i);
        for(short i = 0; i < 64; i++){
                if(board[i] != none){
                        if((board[i] & turnd(turn)) >= 8){
                                tpossible[0] = picker(board, i, tpossible);
                                for(short j = 1; i < tpossible[0]; j++){
                                        init(kp);
                                        if(board[tpossible[j]] != none) capturedpiece = board[tpossible[j]];
                                        mvmkr(tpossible[j], board, i, tpossible);
                                        traverse(board, possible, !turn, depth + 1);
                                        undo(board + tpossible[j], board + i, tpossible + 34);
                                }
                        }
                }
        }
}

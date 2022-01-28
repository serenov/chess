short turnd(short turn);
short checkmate(short board[], short color, short *possible);
void init(short *kp);
void dinit(short *kp);
void FDecide(short board[], short *flag, short i, short tpossible, short list[],  short turn, short *possible, short j);
short eval(short board[]);
short traverse(short board[], short *possible, short turn, short depth, short *mov);


short inspect(short board[], short pos, short color);
short kingmove(short board[], short pos, short *possible);
short queenmove(short board[], short pos, short* possible);
short linemove(short board[], short pos, short* possible);
short diagonalmove(short board[], short pos, short *possible);
short knightmove(short board[], short pos, short *possible);
short pawnmove(short board[], short pos, short* possible);
short nonemove(short board[], short pos, short *possible);
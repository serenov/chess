#include<stdio.h>
#include<stdlib.h>
//#define string "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R"
//#define string "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R"
#define string "6k1/8/7K/8/8/8/8/5Q2"
//#define string "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"
//#define string "b4K2/8/p1k5/4Q3/P7/8/5B2/8"
#include"pieces.h"
#include"fen.h"
#include"moves.h"
#include"dynamics/check.h"
#include"dynamics/stalemate.h"
#include"dynamics/movedyn.h"
#include"CLI/display.h"
#include"CLI/interface.h"
#include"fen.c"
#include"moves.c"
#include"dynamics/check.c"
#include"dynamics/stalemate.c"
#include"dynamics/movedyn.c"
#include"CLI/display.c"
#include"CLI/interface.c"

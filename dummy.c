void knightmove(short board[], short pos, short *possible){
	short offset[9];
	possible++;
	short list(short pos, short *off){
		short count = 0;
		off++;
		if(pos % 8 > 0){
			if(pos / 8 < 6){ *off = 15; off++; count++;}
			if(pos / 8 > 1){*off = -17; off++; count++;}
			if(pos % 8 > 1){
				if(pos / 8 < 7){ *off = 6; off++; count++;}
				if(pos / 8 > 0 ){ *off = -9; off++; count++;}
			}
		}
		if(pos % 8 < 7){
			if(pos / 8 < 6){ *off = 17; off++; count++;}
			if(pos / 8 > 1){*off = -15; off++; count++;}
			if(pos % 8 < 6){
				if(pos / 8 < 7){ *off = 9; off++; count++;}
				if(pos / 8 > 0 ){ *off = -6; off++; count++;}
			}
		}
		return count;
	}
	offset[0] = list(pos, offset);
	for(i = 1; i <= offset[0]; i++){
		if(kingthreat(board, pos, *possible = pos + offset[i];
	}
	return offset[0];
}

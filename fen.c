void fen(char *a, short bo[], short* list){
	for(int i = 56; i > -1;){
		if(*a > 97){
			if(*a == 'p') bo[i] = p;
			else if(*a == 'n') bo[i] = n;
			else if(*a == 'b') bo[i] = b;
			else if(*a == 'r'){ bo[i] = r; if(i == 56) *(list + 3) = 0; if(i == 63) *(list + 5) = 0;}
			else if(*a == 'q') bo[i] = q;
			else {bo[i] = k; kpos[1] = i; if(i == 60) *(list + 4) = 0;}
			i++;
		}
		else if(*a > 65){
			if(*a == 'P') bo[i] = P;
			else if(*a == 'N') bo[i] = N;
			else if(*a == 'B') bo[i] = B;
			else if(*a == 'R'){ bo[i] = R; if(i == 0) *(list) = 0; if(i == 7) *(list + 2) = 0;}
			else if(*a == 'Q') bo[i] = Q;
			else {bo[i] = K; kpos[0] = i; if(i == 4) *(list + 1) = 0;}
			i++;
		}
		else if(*a > 48){
			for(int j = 1; j <= (*a - 48); j++){ bo[i] = none; i++;}
		}
		else i = i - 16;
		a++;
	}
}

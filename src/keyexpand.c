#include "hw6.h"


void caculateRcon(unsigned char rcon[][4], int length){
	int i = 1;
	
	for(i = 0; i < 4; i++){
		rcon[0][i] = 0x00;
	}
	
	rcon[0][0] = 0x01;
	
	for(i = 1; i < length; i++){
		rcon[i][0] = polyProduct(rcon[i - 1][0], 0x02);
		rcon[i][1] = rcon[i][2] = rcon[i][3] = 0x00;
	}
}

void leftRotWord(unsigned char a[], int length){
	unsigned char t = a[0];
	int i = 0;
	for(i = 0; i < length - 1; i++){
		a[i] = a[i + 1];
	}
	a[length - 1] = t;
}

void byteArrayXOR(unsigned char result[], unsigned char src1[], unsigned char src2[], int length){
	int i = 0;
	
	for(i = 0 ; i < length; i++){
		result[i] = src1[i] ^ src2[i];
	}
}

void subWord(unsigned char temp[], int length){
	int i = 0;
	
	for(i = 0; i < length; i++){
		temp[i] = S[temp[i]];
	}
}

void byteArrayCopy(unsigned char a[], unsigned char b[], int length){
	int i = 0;
	for(i = 0; i < length; i++){
		a[i] = b[i];
	}
}

void keyExpansion(unsigned char key[], unsigned char w[][4], int nk){
	int i = 0;
	int j = 0;
	unsigned char temp[4];
	unsigned char Rcon[NB * (NR + 1) / NK - 1][4];
	
	for(i = 0; i < nk; i++){
		for(j = 0; j < 4; j++){
			w[i][j] = key[i * 4 + j];
		}
	}
	
	caculateRcon(Rcon, 10);
	for(i = nk; i < NB * (NR + 1); i++){
		byteArrayCopy(temp, w[i - 1], 4);
		if(i % NK == 0){
			leftRotWord(temp, 4);
			subWord(temp, 4);
			byteArrayXOR(temp, temp, Rcon[i / nk - 1], 4);
		}
		else{
			if(nk > 6 && ((i % nk) == 4)){
				subWord(temp, 4);
			}
		}
		byteArrayXOR(w[i], w[i - nk], temp, 4);
	}
}

void printWord(unsigned char w[][4], int length){
	int i = 0;
	int j = 0;
	for(i = 0; i < length; i++){
		
		if(i < 10){
			fprintf(stdout, "w[ %d]: ", i);
		}
		else{
			fprintf(stdout, "w[%d]: ", i);
		}
		
		for(j = 0; j < 4; j++){
			fprintf(stdout, "%02x", w[i][j]);
		}
		
		putchar('\n');
	}
}

void keyexpand(unsigned char key[]){
	unsigned char w[NB * (NR + 1)][4];
	keyExpansion(key, w, NK);
	printWord(w, NB * (NR + 1));
}

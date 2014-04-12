#include "hw6.h"


void arrayCopy1DTo2D(unsigned char state[][4], unsigned char in[], int row, int col){
	int i = 0;
	int j = 0;
	
	for(i = 0; i < col; i++){
		for(j = 0; j < row; j++){
			state[j][i] = in[i * 4 + j];
		}
	}
}

void addRoundKey(unsigned char state[][4], unsigned char w[]){

}

void subBytes(unsigned char state[][4]){

}

void shiftRows(unsigned char state[][4]){

}

void mixColumns(unsigned char state[][4]){

}

void arrayCopy2DTo1D(unsigned char out[], unsigned char state[][4], int row, int col){
	int i = 0;
	int j = 0;
	
	for(i = 0; i < col; i++){
		for(j = 0; j < row; j++){
			out[i * 4 + j] = state[j][i];
		}
	}
}

void printRound(int round, char title[], char value[]){
	int num_space = 9 - strlen(title);
	int i = 0;
	
	if(round != 10){
		fprintf(stdout, "round[ %d]", round);
	}
	else{
		fprintf(stdout, "round[%d]", round);
	}
	
	fprintf(stdout, ".%s", title);
	
	for(; num_space > 0; num_space--){
		putchar(' ');
	}
	
	for(i = 0; i < 16; i++){
		fprintf(stdout, "%02x", value[i]);
	}
	
	putchar('\n');
}

void AES_encrypt(unsigned char in[], unsigned char out[], unsigned char w[][4]){
	unsigned char state[4][NB];
 	int round = 0;
 
 	arrayCopy1DTo2D(state, in, 4, 4);
 	addRoundKey(state, w[0]);
 
 	for(round = 1; round < NR; round++) {
 		subBytes(state);
 		shiftRows(state);
 		mixColumns(state);
 		addRoundKey(state, w[round]);
 	}
 	subBytes(state);
 	shiftRows(state);
 	addRoundKey(state, w[NR]);
 	
 	arrayCopy2DTo1D(out, state, 4, 4);
}


void encrypt(unsigned char key[], FILE *ifp){
	unsigned char w[NB * (NR + 1)][4];
	unsigned char in[16];
	unsigned char out[16];
	int num = 0;
	
	keyExpansion(key, w, NK);
	num = fread(in, sizeof(unsigned char), 16, ifp);
	
	if(num < 16){
		fprintf(stderr, "Error: The size of file should be at least 16 bytes\n");
		return;
	}
	else{
		AES_encrypt(in, out, w);
	}
}

void invSubBytes(unsigned char state[][4]){

}

void invShiftRows(unsigned char state[][4]){

}

void invMixColumns(unsigned char state[][4]){

}

void AES_decrypt(unsigned char in[], unsigned char out[], unsigned char w[][4]){
	unsigned char state[4][NB];
 	int round = 0;
 	
 	arrayCopy1DTo2D(state, in, 4, 4);
 	addRoundKey(state, w[NR]);
 	
 	for(round=NR-1; round > 0; round--) {
 		invShiftRows(state);
 		invSubBytes(state);
 		addRoundKey(state, w[round]);
 		invMixColumns(state);
 	}
 	invShiftRows(state);
 	invSubBytes(state);
 	addRoundKey(state, w[0]);
 
 	arrayCopy2DTo1D(out, state, 4, 4);
}



void decrypt(unsigned char key[], FILE *ifp){
	unsigned char w[NB * (NR + 1)][4];
	unsigned char in[16];
	unsigned char out[16];
	int num = 0;
	
	keyExpansion(key, w, NK);
	num = fread(in, sizeof(unsigned char), 16, ifp);
	
	if(num < 16){
		fprintf(stderr, "Error: The size of file should be at least 16 bytes\n");
		return;
	}
	else{
		AES_decrypt(in, out, w);
	}
}

#include "hw6.h"

void printRound(int round, char title[], unsigned char value[]){
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

void arrayCopy2DTo1D(unsigned char out[], unsigned char state[][4], int row, int col){
	int i = 0;
	int j = 0;
	
	for(i = 0; i < col; i++){
		for(j = 0; j < row; j++){
			out[i * 4 + j] = state[j][i];
		}
	}
}

void printState(int round, char title[], unsigned char state[][4]){
	unsigned char out[16];
	
	arrayCopy2DTo1D(out, state, 4, 4);
	printRound(round, title, out);
}

void arrayCopy1DTo2D(unsigned char state[][4], unsigned char in[], int row, int col){
	int i = 0;
	int j = 0;
	
	for(i = 0; i < col; i++){
		for(j = 0; j < row; j++){
			state[j][i] = in[i * 4 + j];
		}
	}
}

void addRoundKey(unsigned char state[][4], unsigned char w[][4], int round, char title[]){
	int row = 0, col = 0;
	unsigned char key[16];
	
	for(row = 0; row < 4; row++){
		for(col = 0; col < 4; col++){
			key[row * 4 + col] = w[4 * round + row][col];
		}
	}
	
	if(title[0] == 'i'){
		printRound(NR - round, title, key);
	}
	else{
		printRound(round, title, key);
	}
	
	for(col = 0; col < 4; col++){
		for(row = 0; row < 4; row++){
			state[row][col] = state[row][col] ^ w[4 * round + col][row];
		}
	}

}

void subBytes(unsigned char state[][4], int round){
	int i = 0, j = 0;
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			state[i][j] = S[state[i][j]];
		}
	}
	
	printState(round, "s_box", state);
}

void shiftRows(unsigned char state[][4], int round){
	int i = 0;
	int j = 0;
	for(i = 1; i < 4; i++){
		for(j = 0; j < i; j++){
			leftRotWord(state[i], 4);
		}
	}

	printState(round, "s_row", state);
}

void mixColumns(unsigned char state[][4], int round, unsigned char Poly[], char title[]){
	unsigned char temp[4];
	unsigned char temp2[4];
	int i = 0, j = 0;
	
	for(j = 0; j < 4; j++){
		for(i = 0; i < 4; i++){
			temp[i] = state[i][j];
		}
		modularProduct(temp, Poly, temp2);
	
		for(i = 0; i < 4; i++){
			state[i][j] = temp2[i];
		}
	}
	
	printState(round, title, state);
}


void AES_encrypt(unsigned char in[], unsigned char out[], unsigned char w[][4]){
	unsigned char state[4][NB];
 	int round = 0;
 	
 	arrayCopy1DTo2D(state, in, 4, 4);
 	printState(0, "input", state);
 	addRoundKey(state, w, round, "k_sch");
 
 	for(round = 1; round < NR; round++) {
 		printState(round, "start", state);
 		subBytes(state, round);
 		shiftRows(state, round);
 		mixColumns(state, round, P, "m_col");
 		addRoundKey(state, w, round, "k_sch");
 	}
 	printState(round, "start", state);
 	subBytes(state, round);
 	shiftRows(state, round);
 	addRoundKey(state, w, round, "k_sch");
 	printState(round, "output", state);
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

void invSubBytes(unsigned char state[][4], int round, unsigned char INVR_S[]){
	int i = 0, j = 0;
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			state[i][j] = INVR_S[state[i][j]];
		}
	}
	
	printState(round, "is_box", state);
}

void invShiftRows(unsigned char state[][4], int round){
	int i = 0;
	int j = 0;
	for(i = 1; i < 4; i++){
		for(j = 0; j < i; j++){
			rightRotateArray(state[i], 4);
		}
	}

	printState(round, "is_row", state);	
}


void invMixColumns(unsigned char state[][4], int round, char title[]){
	mixColumns(state, round, INVP, title);
}

void inversion(unsigned char IP[], unsigned char P[], int n){
	int i = 0;
	for(i = 0; i < n; i++){
		P[IP[i]] = i;
	}
}

void AES_decrypt(unsigned char in[], unsigned char out[], unsigned char w[][4]){
	unsigned char state[4][NB];
 	int round = 0;
 	unsigned char INVR_S[256];
 	inversion(S, INVR_S, 256);
 	
 	arrayCopy1DTo2D(state, in, 4, 4);
 	printState(0, "iinput", state);
 	addRoundKey(state, w, NR, "ik_sch");
 	printState(1, "istart", state);
 	for(round=NR-1; round > 0; round--) {
 		invShiftRows(state, NR - round);
 		invSubBytes(state, NR - round, INVR_S);
 		addRoundKey(state, w, round, "ik_sch");
 		printState(NR - round, "ik_add", state);
 		invMixColumns(state, NR - round + 1, "istart");
 	}
 	invShiftRows(state, NR - round);
 	invSubBytes(state, NR - round, INVR_S);
 	addRoundKey(state, w, round, "ik_sch");
 	printState(10, "ioutput", state); 	
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

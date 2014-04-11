#include "hw6.h"

int checkRem(unsigned char rem){
	int i = 0;
	
	for(i = 0; i < 4; i++){
		if(rem[i] != 0){
			return 1;
		}
	}
	
	return -1;
}

long unsigned arrayToLong(unsigned char aux){
	long unsigned inverse = 0;
	int i = 0;
	
	for(i = 0; i < 4; i++){
		inverse = (inverse << 8) + inverse[3 - i];
	}
	
	return inverse;
}


void printTrace(unsigned char rem[][4], unsigned char quo[][4], unsigned char aux[][4], int stages){
	int i = 0;
	
	for(i = 0; i < stages; i++){
		fprintf(stdout, "i=%d, rem[i]=", i+1);
		printPoly(rem[i]);
		fprintf(stdout, ", quo[i]=");
		printPoly(quo[i]);
		fprintf(stdout, ", aux[i]=");
		printPoly(aux[i]);
		putchar('\n');
	}
	
	if(stages != 6){
		printPoly(rem[1]);
		fprintf(stdout, " does not have a multiplicative inverse.\n");
	}
	else{
		fprintf(stdout, "Multiplicative inverse of ");
		printPoly(rem[1]);
		fprintf(stdout, " is ");
		printPoly(aux[5]);
		putchar('\n');
	}
}	

unsigned char polyInverse(unsigned char poly){
	unsigned char i = 1;
	
	if(poly == 0){
		return 0;
	}
	else{
		for(i = 1; i <= 0xff; i++){
			if(polyProduct(i, poly) == 0x01){
				return i;
			}
		}
	}
	
}

void moduleDiv(unsigned char rem[], unsigned char dividend[], unsigned divisor[], unsigned char quo[]){
	quo[0] = quo[1] = 0;
}

void computeAus(unsigned char aux_i[], unsigned char aux_i2[], unsigned char aux_i1[], unsigned char quo[]){
	unsigned char temp[4];
	moduleProduct(quo, aux_i1, temp);
	byteArrayXOR(aux_i, aux_i2, temp, 4);
}

void initiate(unsigned char rem[][4], unsigned char quo[][4], unsigned char aux[][4], long unsigned poly){
	unsigned char temp[4];
	unsigned char oneByteQuo[4] = {0, 0, 0, 0};
	unsigned char temp_product[4] = {1, 0, 0, 0};
	
	longToArray(1, rem[0]);
	longToArray(poly, rem[1]);
	longToArray(0, aux[0]);
	longToArray(1, aux[1]);
	longToArray(0, quo[0]);
	longToArray(0, quo[1]);
	
	quo[1] = polyInverse(rem[1][3]);
	oneByteQuo[3] = quo[1];
	moduleProduct(oneByteQuo, rem[1], temp);
	byteArrayXOR(temp, temp, temp_product);
	
	tempProductGen(temp_product, rem[0][0]);
	if(temp_product[3] == 0){
		byteArrayCopy(rem[2], temp_product, 4);
		quo[0] = 0;
	}
	else{
		quo[0] = polyInverse(temp_product[3]);
		oneByteQuo[0] = quo[0];
		moduleProduct(oneByteQuo, rem[1], temp);
		byteArrayXOR(temp, temp, temp_product);
		byteArrayCopy(rem[2], temp, 4);
	}
}

long unsigned tableMethod(long unsigned poly, int mode){
	unsigned char rem[6][4];
	unsigned char quo[6][4];
	unsigned char aux[6][4];
	int i = 0;
	
	initiate(rem, quo, aux, poly);

	
	
	for(i = 3; i < 6; i++){
		if(i == 5){
			longToArray(1, rem[i]);
			computeSixthQuo(quo[i], rem[i - 2], rem[i - 1]);
		}
		else{
			moduleDiv(rem[i], rem[i - 2], rem[i - 1], quo[i]);
			if(checkRem(rem[i]) == -1){
				break;
			}
		}
	
		computeAus(aux[i], aux[i - 2], aux[i - 1], quo[i]);
	}
	
	
	
	if(mode == TRACE_PRINT){
		printTrace(rem, quo, aux, i);	
	}
	
	if(i == 6){
		return arrayToLong(aux[5]);
	}
	else{
		return 0;
	}
}


long unsigned inverse(long unsigned poly){
	return tableMethod(poly, TRACE_PRINT);
}	

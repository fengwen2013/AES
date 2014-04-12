#include "hw6.h"

void rightRotWord(unsigned char temp[], int length){
	int i = 0;
	for(i = length - 1; i > 0; i--){
		temp[i] = temp[i - 1];
	}
}

void addNumToTemp(unsigned char temp[], int length, unsigned char num){
	rightRotWord(temp, 4);
	temp[0] = num;
}


int checkRem(unsigned char rem[]){
	int i = 0;
	
	for(i = 0; i < 4; i++){
		if(rem[i] != 0){
			return 1;
		}
	}
	
	return -1;
}

long unsigned arrayToLong(unsigned char aux[]){
	long unsigned inverse = 0;
	int i = 0;
	
	for(i = 0; i < 4; i++){
		inverse = (inverse << 8) + aux[3 - i];
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

void tempGen(int hp_ds, int hp_dd, unsigned char dividend[], unsigned char temp[], unsigned char temp_product[]){
	int i = 0;
	int offset = 0;
	if(hp_dd < 4){
		offset = hp_dd - hp_ds;
	}
	
	for(i = 0; i <= hp_ds; i++){
		temp[i] = dividend[offset + i];
	}
	
	for(; i < 4; i++){
		temp[i] = 0;
	}
	
	byteArrayXOR(temp, temp, temp_product, 4);
}

void tempProductGen(int hp_ds, unsigned char divisor[], unsigned char quo, unsigned char temp_product[]){
	int i = 0;
	
	for(i = 0; i <= hp_ds; i++){
		temp_product[i] = polyProduct(divisor[i], quo);
	}
	
	for(; i < 4; i++){
		temp_product[i] = 0;
	}
}

int findHighestPower(unsigned char a[], int length){
	int i = 0;
	
	for(i = length - 1; i >= 0; i--){
		if(a[i] != 0){
			return i;
		}
	}
	
	return 0;
}

void moduleDiv(unsigned char rem[], unsigned char dividend[], unsigned char divisor[], unsigned char quo[], int stage){
	int hp_ds = 0;
	int hp_dd = 0;
	int hp_temp = 0;
	unsigned char temp[4] = {0, 0, 0, 0};
	unsigned char temp_product[4];
	unsigned char dd[4] = {0, 0, 0, 1};
	unsigned char inverse = 0;
	unsigned char t2 = 0;
	int i = 0;
	
	quo[3] = quo[2] = 0;

	hp_ds = findHighestPower(divisor, 4);
	if(stage == 2){
		hp_dd = 4;
	}
	else{
		hp_dd = findHighestPower(dividend, 4);
	}
	inverse = polyInverse(divisor[hp_ds]);
	t2 = dividend[hp_dd];
	
	if(hp_dd <= 3){
		byteArrayCopy(dd, dividend, 4);
	}
	i = 1;
	while(1){
		quo[i] = polyProduct(inverse,t2);
		tempProductGen(hp_ds, divisor, quo[i], temp_product);
		tempGen(hp_ds, hp_dd, dd, temp, temp_product);
		
		hp_temp = findHighestPower(temp, 4);
		if(hp_ds - hp_temp > 1 && hp_dd > hp_ds){
			quo[i + 1] = 0;
			break;
		}
		
		if(hp_ds < hp_dd){
			i--;
			hp_dd--;
			addNumToTemp(temp, 4, dividend[hp_dd - hp_ds]);
			t2 = temp[hp_temp + 1];
			byteArrayCopy(dd, temp, 4);
		}
		else{
			break;
		}	
	}
	byteArrayCopy(rem, temp, 4);
}

void computeAus(unsigned char aux_i[], unsigned char aux_i2[], unsigned char aux_i1[], unsigned char quo[]){
	unsigned char temp[4];
	modularProduct(quo, aux_i1, temp);
	byteArrayXOR(aux_i, aux_i2, temp, 4);
}



void initiate(unsigned char rem[][4], unsigned char quo[][4], unsigned char aux[][4], long unsigned poly){
	unsigned char temp_product[5] = {1, 0, 0, 0, 1};
	
	longToArray(1, rem[0]);
	longToArray(1, rem[5]);
	longToArray(poly, rem[1]);
	longToArray(0, aux[0]);
	longToArray(1, aux[1]);
	longToArray(0, quo[0]);
	longToArray(0, quo[1]);
	
	moduleDiv(rem[2], temp_product, rem[1], quo[2], 2);
	computeAus(aux[2], aux[0], aux[1], quo[2]);
}

void computeSixthQuo(unsigned char quo[], unsigned char dividend[], unsigned char divisor[]){
	unsigned char inverse = polyInverse(divisor[0]);
	quo[1] = polyProduct(inverse, dividend[1]);
	quo[0] = polyProduct(inverse, (dividend[0] ^ 01));
}


long unsigned tableMethod(long unsigned poly, int mode){
	unsigned char rem[6][4];
	unsigned char quo[6][4];
	unsigned char aux[6][4];
	int i = 0;
	
	initiate(rem, quo, aux, poly);

	for(i = 3; i < 6; i++){
		if(checkRem(rem[i - 1]) == -1){
			break;
		}
		if(i == 5){
			longToArray(1, rem[i]);
			computeSixthQuo(quo[i], rem[i - 2], rem[i - 1]);
		}
		else{
			moduleDiv(rem[i], rem[i - 2], rem[i - 1], quo[i], i);
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

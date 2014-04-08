#include "hw6.h"

char xtime(unsigned char a){
	if((a & 0x80) == 0x80){
		return (a << 1) ^ M_X;
	}
	else{
		return a << 1;
	}
}

char polySum(unsigned char a, unsigned char b){
	return a ^ b;
}

char polyProduct(unsigned char a, unsigned char b){
	unsigned char d = 0;
	unsigned char vx[8];
	int i = 0;
	
	vx[0] = a;
	for(i = 1; i < 8; i++){
		a = xtime(a);
		vx[i] = a;
	}

	for(i = 0; i < 8; i++){
		if((b >> i) & 0x01){
			d = polySum(d, vx[i]);
		}
	}
	return d;
}


void longToArray(long unsigned poly, unsigned char a[]){
	int i = 0;
	for(i = 0; i < 4; i++){
		a[i] = (poly >> (8 * i)) & 0xff;
	}
}

void printPoly(unsigned char a[]){
	int int_a = 0;
	int i = 0;
	for(i = 3; i >= 0; i--){
		int_a = a[i];
		fprintf(stdout, "{%02x}", int_a);
	}
}

void printProduct(unsigned char a[], unsigned char b[], unsigned char d[]){
	printPoly(a);
	fprintf(stdout, " CIRCLEX ");
	printPoly(b);
	fprintf(stdout, " = ");
	printPoly(d);
	fprintf(stdout, "\n");
}

void rightRotateArray(unsigned char a[], int len){
	int lastElement = a[len - 1];
	int i = 0;
	for(i = len - 2; i >= 0; i--){
		a[i + 1] = a[i];
	}
	a[0] = lastElement;
}

void modularProduct(unsigned char a[], unsigned char b[], unsigned char d[]){
	int i = 0;
	int j = 0;
	
	for(i = 0; i < 4; i++){
		for(j = 0, d[3 - i] = 0; j < 4; j++){
			
			d[3 - i] = polySum(d[3 - i], polyProduct(a[3 - j], b[j]));
		}
		rightRotateArray(a, 4);
	}
}


void modprod(long unsigned poly1, long unsigned poly2){
	unsigned char a[4];
	unsigned char b[4];
	unsigned char d[4];
	
	longToArray(poly1, a);
	longToArray(poly2, b);
	modularProduct(a, b, d);
	longToArray(poly1, a);
	printProduct(a, b, d);

}





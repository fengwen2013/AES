#include "hw6.h"

unsigned char S[256];
unsigned char P[4];
unsigned char INVP[4];

int polyCheck(char *src, unsigned char *poly, int len){

	int i = 0;
	char high = 0;
	char low = 0;
	
	if(strlen(src) != len){
		fprintf(stderr, "Error: The length of polynomial should be %d bytes\n", len / 2);
		return -1;
	}
	
	for(; i < len; i=i+2){
		if(hexcheck(src[i], &high) && hexcheck(src[i+1], &low)){
			poly[i/2] = (high << 4) + low;
		}
		else{
			return -1;
		}
		
	}
	return 1;
}



void initArray(int a[], int len, int value){
	int i = 0;
	for(; i < len; i++){
		a[i] = value;
	}
}


int checkS(FILE *ifp){
	char buff[1024];
	int checkBox[256];
	int i = 0;
	if(fgets(buff, 1024, ifp) == NULL){
		fprintf(stderr, "Error: Can not read S-box\n");
		return -1;
	}
	
	if(buff[0] != 'S' || buff[1] != '='){
		fprintf(stderr, "Error: Should start with \"S=\"\n");
		return -1;
	}
	
	if(strlen(buff) != 515){
		fprintf(stderr, "Error: Wrong numbers of values, should be exact 512 hexadecimal digits\n");
		return -1;
	}
	
	buff[514] = 0;
	
	if(polyCheck(buff+2, S, 512) == -1){
		return -1;
	}
	
	initArray(checkBox, 256, -1);
	for(i = 0; i < 256; i++){
		if(checkBox[S[i]] == -1){
			checkBox[S[i]] = 0;
		}
		else{
			fprintf(stderr, "Error: Repeated entries\n");
			return -1;
		}
	}
	
	return 1;
}

int checkP(unsigned char poly[], FILE *ifp, char *s){
	char buff[20];
	if(fgets(buff, 20, ifp) == NULL){
		fprintf(stderr, "Error: There is no \"%s\"\n", s);
		return -1;
	}
	
	if(strcmp(substr(buff, 0, strlen(s)), s) != 0){
		fprintf(stderr, "Error: Malformed table file, should start with \"%s\"\n", s);
		return -1;
	}
	if(strlen(buff+strlen(s)) != 9){
		fprintf(stderr, "Error: Wrong numbers of values from \"%s\", should be exact 8 hexadecimal digits\n", s);
		return -1;
	}
	
	buff[strlen(s) + 8] = 0;
		
	if(polyCheck(buff+strlen(s), poly, 8) == -1){
		return -1;
	}
	return 1;
}

int checkINVP(){
	unsigned char d[4];
	modularProduct(P, INVP, d);
	if(d[0] != 1 || d[1] != 0 || d[2] != 0 || d[3] != 0){
		fprintf(stderr, "Error: INVP is not inverse of P\n");
		return -1;
	}
	
	return 1;
}

void reverse(unsigned char a[], int len){
	int i = 0;
	int j = len - 1;
	unsigned char a_char = 0;
	
	
		
	for(i = 0, j = len - 1; i < j; i++, j--){
		a_char = a[i];
		a[i] = a[j];
		a[j] = a_char;
	}
}

int tablecheck(FILE *ifp){
	if(checkS(ifp) == -1){
		return -1;
	}
	if(checkP(P, ifp, "P=") == -1){
		return -1;
	}
	
	if(checkP(INVP, ifp, "INVP=") == -1){
		return -1;
	}
	
	reverse(P, 4);
	reverse(INVP, 4);
	
	if(checkINVP() == -1){
		return -1;
	};
	return 1;
}

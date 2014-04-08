#include "util.h"

char *substr(char *s, int position, int length){
	char *p = malloc(length + 1);
	int i = 0;
	
	if(p == NULL){
		fprintf(stderr, "Unable to allocate memory!\n");
		return NULL;
	}
	

	
	while(i < position){
		s++;
		i++;
	}
	
	for(; i < length && i < strlen(s); i++){
		*(p + i) = *(s++);
	}
	
	*(p + i) = '\0';
	
	return p;
}


int optionCheck(char *option, char *check){
	int clen = strlen(check);
	int olen = strlen(option); 
	int i = 0;
	
	if(olen >= clen){	
		while(i < clen){
			if(option[i] != check[i]){
				return -1;
			}
			i++;
		}
		if(option[clen] == '='){
			return 1;
		}
	}
	return -1;
}

FILE* openFile(char *fileName){
	FILE *ifp = NULL;
	char *mode = "r";
	if(access(fileName, F_OK) == -1){
		fprintf(stderr, "Error: File %s doesn't exsit!\n", fileName);
		return NULL;
	}
	else{
		ifp = fopen(fileName, mode);
		if(ifp == NULL){
			fprintf(stderr, "Error: Can't open %s\n", fileName);
		}
		return ifp;
	}
}


#include "hw6.h"

int main(int argc, char *argv[]){
	if(argc < 2){
		fprintf(stderr, "Error: Too few arguments\n");
		return 0;
	}
	
	if(strcmp(argv[1], "tablecheck") == 0){
		checkCommand(argv, argc);
	}
	else{
		if(strcmp(argv[1], "modprod") == 0){
			modprodCommand(argv, argc);
		}
		else{
			if(strcmp(argv[1], "keyexpand") == 0){
				keyexpandCommand(argv, argc);
			}
			else{
				if(strcmp(argv[1], "encrypt") == 0){
					cryptCommand(argv, argc, ENCRYPT);
				}
				else{
					if(strcmp(argv[1], "decrypt") == 0){
						cryptCommand(argv, argc, DECRYPT);
					}
					else{
						if(strcmp(argv[1], "inverse") == 0){
							inverseCommand(argv, argc);
						}
						else{
							fprintf(stderr, "Error: First argument should be (tablecheck | encrypt | decrypt | encrypt3 | decrypt3)!!!\n");
							return 0;
						}
					}
				}
			}
		}
	}
	return 0;
}

void checkCommand(char *argv[], int argc){
	FILE *ifp = stdin;
	if(argc != 3){
		fprintf(stderr, "Error: Wrong number of arguments for tablecheck command\n");
		return;
	}
	else{
		if(optionCheck(argv[2], "-t") == -1){
				return;
		}
		else{
			if((ifp = openFile(argv[2] + 3)) == NULL){
				return;	
			}
			tablecheck(ifp);
		}
	}
}

void keyexpandCommand(char *argv[], int argc){
	int i = 2;
	FILE *tfp = NULL;
	unsigned char *key = NULL;
	if(argc != 4){
		fprintf(stderr, "Error: Wrong number of arguments for the command\n");
		return;
	}
	else{
		while(i < argc){
			if(optionCheck(argv[i], "-k") == 1){
				key = (unsigned char *)malloc(sizeof(char) * 16);	
				if(keycheck(argv[i] + 3, key) == -1){
					return;
				}
			}
			else{
				if(optionCheck(argv[i], "-t") == 1){
					if((tfp = openFile(argv[i] + 3)) == NULL){
						return;
					}
					if(tablecheck(tfp) == -1){
						return;
					}
				}
				else{
					fprintf(stderr, "Error: Wrong option, should be \"-t\" or \"-k\"\n");
				}
			}
			i++;
		}
		keyexpand(key);
		
	}
}

void cryptCommand(char *argv[], int argc, int mode){
	int i = 2;
	FILE *tfp = NULL;
	FILE *ifp = stdin;
	unsigned char *key = NULL;
	if(argc < 4 || argc > 5){
		fprintf(stderr, "Error: Wrong number of arguments for the command\n");
		return;
	}
	else{
		while(i < argc){
			if(optionCheck(argv[i], "-k") == 1){
				key = (unsigned char *)malloc(sizeof(char) * 16);	
				if(keycheck(argv[i] + 3, key) == -1){
					return;
				}
			}
			else{
				if(optionCheck(argv[i], "-t") == 1){
					if((tfp = openFile(argv[i] + 3)) == NULL){
						return;
					}
					if(tablecheck(tfp) == -1){
						return;
					}
				}
				else{
					fprintf(stderr, "Error: Wrong option, should be \"-t\" or \"-k\"\n");
					return;
				}
			}
			i++;
		}
		
		if(argc == 5){
			if((ifp = openFile(argv[argc - 1])) == NULL){
				return;
			}
		}
		
		if(mode == ENCRYPT){
			encrypt(key, ifp);
		}
		else{
			decrypt(key, ifp);
		}
	}
}

void modprodCommand(char *argv[], int argc){
	int i = 2;
	int j = 0;
	unsigned poly1 = 0, poly2 = 0;
	char hex = 0;
	if(argc != 4){
		fprintf(stderr, "Error: Wrong number of arguments for modprod command\n");
		return;
	}
	else{
		while(i < argc){
			if(optionCheck(argv[i], "-p1") == 1){
				for(j = 0; j < 8; j++){
					hexcheck(*(argv[i] + 4 + j), &hex);
					poly1 = poly1 << 4;
					poly1 += hex; 
				}
			}
			else{
				if(optionCheck(argv[i], "-p2") == 1){
					for(j = 0; j < 8; j++){
						hexcheck(*(argv[i] + 4 + j), &hex);
						poly2 = poly2 << 4;
						poly2 += hex; 
					}
				}
				else{
					fprintf(stderr, "Error: Wrong option, should be \"-p1\" or \"-p2\"\n");
				}
			}
			i++;
		}
		modprod(poly1, poly2);
	}
}

void inverseCommand(char *argv[], int argc){
	long unsigned poly = 0;
	char hex = 0;
	int i = 0;
	if(argc != 3){
		fprintf(stderr, "Error: Wrong number of arguments for inverse command\n");
		return;
	}
	else{
		if(optionCheck(argv[2], "-p") == 1){
			if(*(argv[2] + 11)!= 0){
				fprintf(stderr, "Error: Wrong format of polynomial\n");
				return;
			}
			else{
				for(i = 0; i < 8; i++){
					hexcheck(argv[2][3 + i], &hex);
					poly = poly << 4;
					poly += hex; 
				}
			}
		}
		else{
			fprintf(stderr, "Error: Wrong option, should be \"-p\"\n");
			return;
		}
		inverse(poly);
	}
}

int hexcheck(char c, char *c1){
	if(c >= '0' && c <= '9'){
		*c1 = c - '0';
	}
	else{
		if( c >= 'a' && c <= 'f'){
			*c1 = c - 'a' + 0xa;
		}
		else{
			fprintf(stdout, "Error: '%c' is not valid hex character!\n", c);
			return 0;
		}
	}
	return 1;
}

int keycheck(char *src, unsigned char *key){
	int len = 32;
	int i = 0;
	char high = 0;
	char low = 0;
	
	if(strlen(src) != len){
		fprintf(stderr, "Error: The key length should be %d bytes\n", len / 2);
		return -1;
	}
	
	for(; i < len; i=i+2){
		if(hexcheck(src[i], &high) && hexcheck(src[i+1], &low)){
			key[i/2] = (high << 4) + low;
		}
		else{
			return -1;
		}
		
	}
	return 1;
}

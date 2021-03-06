#include "util.h"
#define ENCRYPT 	0
#define DECRYPT 	1

#define TRACE_PRINT 1
#define TRACE_OMIT	0
#define M_X			0x1b
#define NK			4
#define NB			4
#define NR			10

int tablecheck(FILE *ifp);
void modprod(long unsigned poly1, long unsigned poly2);
void keyexpand (unsigned char key[]);
void encrypt(unsigned char key[], FILE *ifp);
void decrypt(unsigned char key[], FILE *ifp);
long unsigned inverse(long unsigned poly);

void checkCommand(char *argv[], int argc);
void modprodCommand(char *argv[], int argc);
void keyexpandCommand(char *argv[], int argc);
void cryptCommand(char *argv[], int argc, int mode);
void inverseCommand(char *argv[], int argc);

int hexcheck(char c, char *c1);
int keycheck(char *src, unsigned char *key, int len);
void modularProduct(unsigned char a[], unsigned char b[], unsigned char d[]);
unsigned char polyProduct(unsigned char a, unsigned char b);
void longToArray(long unsigned poly, unsigned char a[]);
void printPoly(unsigned char a[]);
void byteArrayXOR(unsigned char result[], unsigned char src1[], unsigned char src2[], int length);
void byteArrayCopy(unsigned char a[], unsigned char b[], int length);
void leftRotWord(unsigned char a[], int length);
void keyExpansion(unsigned char key[], unsigned char w[][4], int nk);
void rightRotateArray(unsigned char a[], int len);

extern unsigned char S[256];
extern unsigned char P[4];
extern unsigned char INVP[4];

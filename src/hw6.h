#include "util.h"
#define ENCRYPT 0
#define DECRYPT 1
#define M_X		0x1b

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

extern unsigned char S[256];
extern unsigned char P[4];
extern unsigned char INVP[4];

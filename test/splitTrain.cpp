#include "head.h"

#define BUF_SIZE 4000000
char buf[BUF_SIZE+10];

int main(){
	srand(time(NULL));

	FILE *fIn = fopen("train.txt", "r");
	FILE *fTrain = fopen("train.tmp", "w");
	FILE *fTest = fopen("test.tmp", "w");

	while (fgets(buf, BUF_SIZE, fIn)){
		if (rand()%100<80)
			fputs(buf, fTrain);
		else
			fputs(buf, fTest);

	}
	return 0;
}

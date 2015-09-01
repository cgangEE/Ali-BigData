#include "head.h"

#define BUF_SIZE 10000
char buf[BUF_SIZE+10];

int main(){
	string fileName = "big.txt";
	FILE *file = fopen(fileName.c_str(), "r");
	
	while (fgets(buf, BUF_SIZE, file)){
		int len = strlen(buf);
		int cnt = 0;

		char *s = buf;
		while (*s != 0){
			if (cnt == 6){
				printf("%s", s);
				break;
			}
			if (*s == '\t') ++cnt;
			++s;
		}
	}
	return 0;
}

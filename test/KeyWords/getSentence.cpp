#include "head.h"

#define fileName "chinese.out"

#define BUF_SIZE 100000
#define uni (unsigned char)

char buf[BUF_SIZE+10];

#include "C.h"

typedef vector<C> sentence;

void saveSentence(vector<C> &stc){
	rep(i, sz(stc)) printf("%s", stc[i].s);
	if (sz(stc)) puts("");

	stc.clear();
}

void getKeyWords(){
	FILE *file = fopen(fileName, "r");	
	if (file==NULL){
		fprintf(stderr, "open file<%s> failed\n", fileName);
		return;
	}

	C c;
	vector<C> stc;

	while (fgets(buf, BUF_SIZE, file)){
		int len = strlen(buf);
		rep(i, len){
			if (buf[i]&(1<<7)){
				if ((buf[i]>>6)==-1 && c.len>0){
					if (c.isChinese()){
						stc.push_back(c);
					} else {
						saveSentence(stc);
					}
					c.clear();
				}
				c.push_back(buf[i]);
			}
			else{
				if (c.isChinese())
					stc.push_back(c);
				saveSentence(stc);
				c.clear();
			}
		}

	}
	fclose(file);
}


int main(){
	getKeyWords();
}


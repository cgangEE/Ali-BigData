#include "head.h"
#include "C.h"

#define fSegName "segment.out"

#define BUF_SIZE 10000000
char buf[BUF_SIZE+10];

struct W{
	vector<C> s;
	void push_back(C &c){
		s.push_back(c);
	}

	bool operator <(const W &w){
		rep(i, min(sz(s), sz(w.s))){
			if (s[i]!=w.s[i]) return s[i]<w.s[i];
		}
		return sz(s)<sz(w.s);
	}
};

void getKeyWords(){
	FILE* fSeg = fopen(fSegName, "r");
	if (fSeg == NULL){
		fprintf(stderr, "open file<%s> failed\n", fSegName);
		return;
	}

	map<W, int> wordToInt;
	
	while (fgets(buf, BUF_SIZE, fSeg)){
		int len = strlen(buf);
		rep(i, len){
			if (buf[i]&(1<<7)){
			}
			else {

			}

		}
	}
}

int main(){
	getKeyWords();
	return 0;
}

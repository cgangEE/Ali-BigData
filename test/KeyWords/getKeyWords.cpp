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

	bool operator <(const W &w)const {
		rep(i, min(sz(s), sz(w.s))){
			if (s[i]!=w.s[i]) return s[i]<w.s[i];
		}
		return sz(s)<sz(w.s);
	}
	size_t size(){
		return sz(s);
	}
	void clear(){
		s.clear();
	}
	void out()const{
		rep(i, sz(s)) s[i].out();
		putchar(' ');
	}
};

void getKeyWords(){
	FILE* fSeg = fopen(fSegName, "r");
	if (fSeg == NULL){
		fprintf(stderr, "open file<%s> failed\n", fSegName);
		return;
	}

	map<W, int> wordToInt;
	W word;
	C c;
	
	while (fgets(buf, BUF_SIZE, fSeg)){
		int len = strlen(buf);
		rep(i, len){
			if (buf[i]&(1<<7)){
				c.push_back(buf[i]);
				if (c.len==3){
					word.push_back(c);
					c.clear();
				}
			}
			else if (sz(word)){
				++wordToInt[word];
				word.clear();
			}

		}
	}

	multimap<int, W> freqToWord;
	foreach(it, wordToInt){
		freqToWord.insert(make_pair(it->second, it->first));
	}

	foreach(it, freqToWord){
		if (it->first<40000) continue;	
		if (sz(it->second)==1) continue;
		it->second.out();
		printf("%d\n", it->first);
	}

}

int main(){
	getKeyWords();
	return 0;
}

#include "head.h"

#define fileName "chinese.out"

#define BUF_SIZE 100000
#define uni (unsigned char)

char buf[BUF_SIZE+10];

struct C{
	int len;
	char s[4];
	bool operator <(const C&c)const{
		rep(i, 3)
			if (s[i]!=c.s[i])
				return s[i]<c.s[i];
		return false;
	}
	void clear(){
		len = 0;
	}
	void push_back(char &c){
		if (len<3)
			s[len++] = c;
	}
	bool isChinese(){
		return len==3
			&& (unsigned char) s[0]!=0xe2
			&& (unsigned char) s[0]!=0xe3
			&& (unsigned char) s[0]!=0xef;
	}
};


void cutSentence(vector<C> &stc){
	rep(i, sz(stc)) cout<<stc[i].s;
	if (sz(stc)) cout<<endl;
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
		cout<<endl<<buf;
		rep(i, len){
			if (buf[i]&(1<<7)){
				if ((buf[i]>>6)==-1 && c.len>0){
					if (c.isChinese()){
						stc.push_back(c);
					} else {
						cutSentence(stc);
					}
					c.clear();
				}
				c.push_back(buf[i]);
			}
			else{
				if (c.isChinese())
					stc.push_back(c);
				cutSentence(stc);
				c.clear();
			}
		}

	}
}


int main(){
	getKeyWords();
}

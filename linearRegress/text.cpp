#include "text.h"
#include "head.h"

int getHttp(string &s){
	int ret = 0;
	int pos = s.find("http", 0);
	while (pos!=-1){
		++ret;
		pos = s.find("http", pos+4);
	}
	return ret;
}

int getFace(string &s){
	int ret = 0;
	int flag = 0;
	rep(i, sz(s)){
		if (s[i]=='[')
			flag = 1;
		else if (s[i]==']'){
			if (flag){
				++ret;
				flag = 0;
			}
		}
	}
	return ret;
}

Text::Text(string s):s(s){
	len = sz(s);
	http = getHttp(s);	
	face = getFace(s);
}

void Text::debug(){
}

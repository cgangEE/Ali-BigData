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

Text::Text(string s, int &total, int &digit, int &chinese, int &english, int &http, int &face):s(s){
	total = 0;
	digit = 0;
	chinese = 0;
	english = 0;

	rep(i, sz(s)){
		if (isdigit(s[i])){
		   	++digit;
			++total;
		}
		else if (isalpha(s[i])){
		   	++english;
			++total;
		}
		else if ( (s[i]&(1<<7)) && ( (s[i]>>6) == -1)){
			++ chinese;
			++ total;
		}
		
		
	}

	http = getHttp(s);	
	face = getFace(s);
}

int Text::getCnt(string p){
	int ret = 0;
	int pos = s.find(p, 0);
	while (pos!=-1){
		++ret;
		pos = s.find(p, pos+sz(p));
	}
	return ret;
}

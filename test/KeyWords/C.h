#ifndef _C_H_
#define _C_H_

#include "head.h"

struct C{
	int len;
	char s[4];
	bool operator <(const C&c)const{
		rep(i, 3)
			if (s[i]!=c.s[i])
				return s[i]<c.s[i];
		return false;
	}
	bool operator !=(const C&c)const{
		rep(i, 3)
			if (s[i]!=c.s[i])
				return true;
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
	void out()const{
		rep(i, len) putchar(s[i]);
	}
};

#endif

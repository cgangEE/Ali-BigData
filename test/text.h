#ifndef _TEXT_H_
#define _TEXT_H_
#include "head.h"

struct Text{
	string s;

	Text(){}
	Text(string s,int &len,int &http,int &face);
	void debug();
	int getCnt(string p);
};

#endif

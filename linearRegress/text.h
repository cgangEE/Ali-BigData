#ifndef _TEXT_H_
#define _TEXT_H_
#include "head.h"

struct Text{
	int len;
	int http;
	int face;
	string s;

	Text(){}
	Text(string s);
	int getCnt(string p);
	void debug();
};

#endif

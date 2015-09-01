#ifndef _TEXT_H_
#define _TEXT_H_
#include "head.h"

struct Text{
	string s;

	Text(){}
	Text(string s, int &total, int &digit, int &chinese, int &english, int &http,int &face);
	int getCnt(string p);
};

#endif

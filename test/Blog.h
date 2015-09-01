#ifndef _BLOG_H_
#define _BLOG_H_

#include "head.h"
#include "text.h"

struct Blog{
	string userId;
	string blogId;
	string date;
	int forward;
	int comment;
	int like;

	int total;
	int digit;
	int chinese;
	int english;

	int http;
	int face;
	Text text;

	Blog(){
		forward=comment=like=0;
	}

	Blog(int forward, int comment, int like):
		forward(forward),comment(comment),like(like){}

	Blog operator +(const Blog&b)const{
		return Blog(forward+b.forward, comment+b.comment, like+b.like);
	}

	bool operator <(const Blog&b)const{
		return date<b.date;
	}

	void out(){
		cout<<forward<<' '<<comment<<' '<<like<<endl;
	}

	static int atoi(char *s){
		int len = strlen(s);
		int ret = 0;
		rep(i, len) 
			ret = ret*10 + (s[i]-'0');
		return ret;
	}

	Blog(char *s, bool flag){
		static char buf[BUF_SIZE];
		int len = strlen(s);
		int idx = 0;
		int bufLen = 0;
		rep(i, len)
			if (s[i]!='\t')
				buf[bufLen++] = s[i];
			else{
				buf[bufLen] = 0;

				if (idx==0) userId = string(buf);
				else if (idx==1) blogId = string(buf);
				else if (idx==2){ 
					date = string(buf);
					text = Text(string(s+i+1), 
							total, digit, chinese, english, http, face);
					break;
				}

				++idx;
				bufLen = 0;
			}
			
	}

	Blog(char *s){
		static char buf[BUF_SIZE];
		int len = strlen(s);
		int idx = 0;
		int bufLen = 0;
		rep(i, len)
			if (s[i]!='\t')
				buf[bufLen++] = s[i];
			else{
				buf[bufLen] = 0;

				if (idx==0) userId = string(buf);
				else if (idx==1) blogId = string(buf);
				else if (idx==2) date = string(buf);
				else if (idx==3) forward = atoi(buf);
				else if (idx==4) comment = atoi(buf);
				else if (idx==5){
					like = atoi(buf);
					text = Text(string(s+i+1), 
							total, digit, chinese, english, http, face);
					break;
				}

				++idx;
				bufLen = 0;
			}
			
	}
};

#endif

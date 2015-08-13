#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

#define rep(i, n) for (int i=0; i<(n); ++i)
#define repf(i, a, b) for (int i=(a); i<=(b); ++i)
#define repd(i, a, b) for (int i=(a); i>=(b); --i)
#define sz(a) ((int)(a).size())

#define trainData "weibo_train_data.txt"
#define testData "weibo_predict_data.txt"

#define inputData trainData
#define BUF_SIZE 100000

#include "Blog.h"
#define N 50000

char buf[BUF_SIZE];

vector<Blog> userBlog[N+10];
Blog statics[N+10];

vector<Blog> train;
vector<Blog> test;

map<string, int> stringToId;

void readTest(){
	FILE *file = fopen(testData, "r");
	if (file==NULL){
		fprintf(stderr, "open file<%s> failed\n", testData);
		return;
	}

	
	FILE *foutput = fopen("test.out", "w");
	if (foutput==NULL){
		fprintf(stderr, "oepn file<%s> failed\n", "test.out");
		return;
	}


	fprintf(foutput, "cnt,userForward,userComment,userLike,text,userId,blogId,date\n");
	while (fgets(buf, BUF_SIZE, file)){
		Blog blog(buf, true);
		int idx = stringToId[blog.userId];
		int cnt = sz(userBlog[idx]);
		Blog &stat = statics[idx];
		fprintf(foutput, "%d,%.8lf,%.8lf,%.8lf,%d,%s,%s,%s\n",
				cnt,
				cnt==0?0.:stat.forward*1./cnt,
				cnt==0?0.:stat.comment*1./cnt,
				cnt==0?0.:stat.like*1./cnt,
				sz(blog.text),
				blog.userId.c_str(),
				blog.blogId.c_str(),
				blog.date.c_str()
				);
	}

	fclose(file);
	fclose(foutput);
}

void readTrain(){
	FILE *file = fopen(inputData, "r");
	if (file==NULL){
		fprintf(stderr, "open file<%s> failed\n", inputData);
		return;
	}

	string fOutputName = "train.out";
	FILE *foutput = fopen(fOutputName.c_str(), "w");
	if (foutput==NULL){
		fprintf(stderr, "open file<%s> failed\n", fOutputName.c_str());
		return;
	}


	while (fgets(buf, BUF_SIZE, file)){
		Blog blog(buf);
		if (rand()%100<=100)
			train.push_back(blog);
		else
			test.push_back(blog);
	}
	fclose(file);

	int idx = 0;

	rep(i, sz(train)){
		Blog &blog =train[i];
		int userIdx = stringToId[blog.userId];
		if (userIdx == 0){
			userIdx = ++idx;
			stringToId[blog.userId] = userIdx;
		}
		userBlog[userIdx].push_back(blog);
	}

	// get statics for each users

	repf(i, 1, idx){
		rep(j, sz(userBlog[i]))
			statics[i] = statics[i] + userBlog[i][j];
	}

	// output features of each train data

	fprintf(foutput, "cnt,userForward,userComment,userLike,forward,comment,like,text\n");
	rep(i, sz(train)){
		Blog &blog = train[i];
		int userIdx = stringToId[blog.userId];
		Blog &stat = statics[userIdx];
		int cnt = userBlog[userIdx].size();

		fprintf(foutput, "%d,%.8lf,%.8lf,%8lf,%d,%d,%d,%d\n", 
				cnt,
				stat.forward*1./cnt,
				stat.comment*1./cnt,
				stat.like*1./cnt,
				blog.forward,
				blog.comment,
				blog.like,
				(int) blog.text.size());
	}
	fclose(foutput);
}

int main(){
	srand(time(NULL));
	readTrain();	
	readTest();
	return 0;
}


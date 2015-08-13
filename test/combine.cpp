#include <iostream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#define BUF_SIZE 100000

char buf[BUF_SIZE+100];

int main(){
	string fTestName = "weibo_predict_data.txt";
	FILE *fTest = fopen(fTestName.c_str(), "r");
	if (fTest==NULL){
		printf("open file<<%s> failed\n", fTestName.c_str());
		return 1;
	}

	string fAnsName = "ans.csv";
	FILE *fAns = fopen(fAnsName.c_str(), "r");
	if (fAns==NULL){
		printf("open file<%s> failed\n", fAnsName.c_str());
		return 1;
	}


	string fOutName = "submit.csv";
	FILE *fOut = fopen(fOutName.c_str(), "w");
	if (fOut==NULL){
		printf("open file<%s> failed\n", fOutName.c_str());
		return 1;
	}


	while (fgets(buf, BUF_SIZE, fTestName)){

	}

	return 0;
}

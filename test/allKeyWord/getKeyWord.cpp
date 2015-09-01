#include "head.h"

#define BUF_SIZE 10000000
char buf[BUF_SIZE+10];

int main(){
	string fileName = "words.txt";
	FILE *file = fopen(fileName.c_str(), "r");
	map<string, int> wordToFreq;
	string s;
		
	while (fgets(buf, BUF_SIZE, file)){
		int len = strlen(buf);
		rep(i, len){
			if (buf[i]==' ' || buf[i]=='\n'){
				++wordToFreq[s];
				s = "";
			}
			else s = s + buf[i];
		}
	}

	multimap<int, string> freqToWord;
	foreach(it, wordToFreq){
		freqToWord.insert( make_pair(it->second, it->first) );
	}

	foreach(it, freqToWord)
		cout<<it->second<<' '<<it->first<<endl;
	return 0;
}

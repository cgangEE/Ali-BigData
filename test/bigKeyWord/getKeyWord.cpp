#include "head.h"

#define BUF_SIZE 10000000
char buf[BUF_SIZE+10];

int main(){
	string fileName = "words.txt";
	string fileFreqName = "freq.txt";

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

	fclose(file);

	map<string, int> allWordToFreq;
	file = fopen(fileFreqName.c_str(), "r");
	
	int cnt;
	while (~fscanf(file, "%s %d", buf, &cnt)){
		allWordToFreq[string(buf)] = cnt;
	}

	multimap<double, string> freqToWord;
	foreach(it, wordToFreq){
		cnt = allWordToFreq[it->first];
		freqToWord.insert(make_pair((double)it->second/10365.*log(1626750./cnt), it->first));
	}

	foreach(it, freqToWord){
		if (sz(it->second)<=1) continue;
		if ( (it->second[0] & (1<<7)) && sz(it->second)<=3) continue;
		cout<<it->second<<' '<<it->first<<' '<<wordToFreq[it->second]<<' '<<allWordToFreq[it->second]<<endl;
	}
	return 0;
}

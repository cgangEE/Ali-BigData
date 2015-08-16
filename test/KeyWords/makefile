getKeyWords: getKeyWords.cpp
	g++ getKeyWords.cpp -o getKeyWords

sentence.out: chinese.out getSentence
	./getSentence> sentence.out

getSentence: getSentence.cpp C.h
	g++ getSentence.cpp -o getSentence

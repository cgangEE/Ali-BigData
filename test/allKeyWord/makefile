getKeyWord: getKeyWord.cpp
	g++ getKeyWord.cpp -o getKeyWord
	
sentence.txt: preProcess
	./preProcess > sentence.txt
	./jieba.R

preProcess: preProcess.cpp
	g++ preProcess.cpp -o preProcess
	

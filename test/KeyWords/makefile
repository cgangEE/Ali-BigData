getKeyWords: getKeyWords.cpp lexicon.txt
	g++ getKeyWords.cpp -o getKeyWords

lexicon.txt: TransWord.class
	java TransWord < TSAIWORD.TXT >lexicon.txt

TransWord.class: TransWord.java
	javac -classpath ./chineseutils-0.1.jar TransWord.java 

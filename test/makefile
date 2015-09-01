#test.out train.out: getFeature
#	./getFeature

getFeature: getFeature.cpp blog.h head.h text.o train.tmp test.tmp
	g++ getFeature.cpp text.o -o getFeature

text.o: text.cpp text.h head.h
	g++ -c text.cpp

train.tmp test.tmp: splitTrain
	./splitTrain

splitTrain: splitTrain.cpp
	g++ splitTrain.cpp -o splitTrain

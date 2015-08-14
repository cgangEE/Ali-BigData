#test.out train.out: getFeature
#	./getFeature

getFeature: getFeature.cpp Blog.h head.h text.o
	g++ getFeature.cpp text.o -o getFeature

text.o: text.cpp text.h head.h
	g++ -c text.cpp

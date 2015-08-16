submit.txt: ans.csv
	awk 'BEGIN{FS=","} NR!=1  {print $$1 "\t" $$2 "\t" $$3 "," $$4 "," $$5}' ans.csv > submit.txt

ans.csv: test.out train.out linearRegress.R
	./linearRegress.R

test.out train.out: getFeature
	./getFeature

getFeature: getFeature.cpp Blog.h text.o
	g++ text.o getFeature.cpp -o getFeature

text.o: text.cpp text.h head.h
	g++ -c text.cpp

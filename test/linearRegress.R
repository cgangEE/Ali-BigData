#!/usr/bin/env Rscript
train = read.csv("train.out");


attach(train)
lineF = lm(forward~cnt+userForward+userComment+userLike+text, train);
lineC = lm(comment~cnt+userForward+userComment+userLike+text, train);
lineL = lm(like~cnt+userForward+userComment+userLike+text+http, train);

test = read.csv("test.out");

f = round(predict(lineF, test));
c = round(predict(lineC, test));
l = round(predict(lineL, test));

f[f<0] = 0
c[c<0] = 0
l[l<0] = 0

f[test$userForward+test$userComment+test$userLike==0] = 0
c[test$userForward+test$userComment+test$userLike==0] = 0
l[test$userForward+test$userComment+test$userLike==0] = 0

df = abs(f-test$forward)/(test$forward+5)
dc = abs(c-test$comment)/(test$comment+3)
dl = abs(l-test$like)/(test$like+3)

prec = 1-0.5*df-0.25*dc-0.25*dl

count = test$forward+test$comment+test$like
count[count>100]=100

sgn=function(prec){
	ret=1:length(prec)
	ret[prec<=0]=0
	ret[prec>0]=1
	return(ret)
}

eval = sum((count+1)*sgn(prec-0.8))/sum(count+1)
eval

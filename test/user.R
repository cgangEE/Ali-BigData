train = read.csv("train.out")
test = read.csv("test.out")


m = max(train$uid)
l = length(test$uid)

test$f = rep(0, l)
test$c = rep(0, l)
test$l = rep(0, l)

for (i in 1:m){	
	print(i)

	trainX = train[train$uid == i,]
	testX = test[test$uid == i,]
	attach(trainX)
	lineF = lm(forward~http+text+face, trainX)
	lineC = lm(comment~http+text+face, trainX)
	lineL = lm(like~http+text+face, trainX)
	detach(trainX)

	test[test$uid == i,]$f  = predict(lineF, testX)
	test[test$uid == i,]$c  = predict(lineC, testX)
	test[test$uid == i,]$l  = predict(lineL, testX)
}


f = round(test$f)
c = round(test$c)
l = round(test$l)

f[f<0] = 0
c[c<0] = 0
l[l<0] = 0



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
print(eval)


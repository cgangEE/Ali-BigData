#!/usr/bin/env Rscript
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
	lineF = lm(forward~http+text+face+keyword0+keyword1+keyword2+keyword3, trainX)
	lineC = lm(comment~http+text+face+keyword0+keyword1+keyword2+keyword3, trainX)
	lineL = lm(like~http+text+face+keyword0+keyword1+keyword2+keyword3, trainX)
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


ans = data.frame(test$userId, test$blogId, f, c, l)
write.csv(ans, "ans.csv", row.names=F, quote=F)



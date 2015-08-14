#!/usr/bin/env Rscript
train = read.csv("train.out");
test = read.csv("test.out");

train = train[train$forward<100,]
train = train[train$comment<100,]
train = train[train$like<100,]


attach(train)
lineF = lm(forward~cnt+userForward+userComment+userLike+text)
lineC = lm(comment~cnt+userForward+userComment+userLike+text)
lineL = lm(like~cnt+userForward+userComment+userLike+text)

data = test[, 1:5]

f = round( predict(lineF, data) )
c = round( predict(lineC, data) )
l = round( predict(lineL, data) )

f[f<0] = 0
c[c<0] = 0
l[l<0] = 0

evaluate = sum(abs(f-test$forward)) + sum(abs(c-test$comment))	+ sum(abs(l-test$like))


#!/usr/bin/env Rscript
train = read.csv("train.out");
test = read.csv("test.out");

train = train[train$forward<100,]
train = train[train$comment<100,]
train = train[train$like<100,]

test= test[test$forward<100,]
test= test[test$comment<100,]
test= test[test$like<100,]

attach(train)
lineF = lm(forward~
		cnt
		+log(userForward+1)
		+poly(userForward,2)
		+poly(userComment,2) + poly(userLike,2)
		+poly(text,2)+poly(http,2)+poly(face,1))
lineC = lm(comment~
		poly(cnt,2)
		+poly(userForward,2)
		+log(userComment+1)
		+poly(userComment,2) 
		+poly(userLike,2)
		+poly(text,2)+poly(http,2)+poly(face,2))
lineL = lm(like~
		cnt
		+poly(userForward,2)
		+poly(userComment,2) 
		+log(userLike+1)
		+poly(userLike,2)
		+poly(text,2)+poly(http,2)+poly(face,2))


data = test[, 1:7]

f = round( predict(lineF, data) )
c = round( predict(lineC, data) )
l = round( predict(lineL, data) )

f[f<0] = 0
c[c<0] = 0
l[l<0] = 0

evaluate = sum(abs(f-test$forward)) + sum(abs(c-test$comment))+ sum(abs(l-test$like))


#!/usr/bin/env Rscript
user = read.csv("user.out")
user = user[,-1]

for(i in 1:3){
	user[,i] =user[,i]/max(user[,i])
}

center =5
cl = kmeans(user, center)

train = read.csv("train.out")
test = read.csv("test.out")


train = train[train$userForward+train$userComment+train$userLike!=0,]


m = length(test$uid)
test$f = rep(0, m)
test$c = rep(0, m)
test$l = rep(0, m)

for (i in 1:center){
	x = which(cl$cluster==i)
	trainX = train[train$uid %in% x,]
	attach(trainX)
	lineF = lm(forward~userForward+userComment+userLike+http)
	lineC = lm(comment~userForward+userComment+userLike+http)
	lineL = lm(like~userForward+userComment+userLike)

	detach(trainX)

	testX = test[test$uid %in% x,]
	f = predict(lineF, testX)
	c = predict(lineC, testX)
	l = predict(lineL, testX)

	test[test$uid %in% x,]$f = f
	test[test$uid %in% x,]$c = c
	test[test$uid %in% x,]$l = l
}


f = round(test$f)
c = round(test$c)
l = round(test$l)


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
print(eval)

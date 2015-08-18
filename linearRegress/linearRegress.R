#!/usr/bin/env Rscript
user = read.csv("user.out")
user = user[,-1]

lenUser = length(user)
cntUser = dim(user)[1]

for (i in 1:lenUser){
	user[,i] = user[,i] / max(user[,i])
}

center = 5
cl = kmeans(user, center)


train = read.csv("train.out");
test = read.csv("test.out");

attach(train)
train = train[userForward+userComment+userLike!=0,]
detach(train)


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
	lineL = lm(like~userForward+userComment+userLike+keyword)

	detach(trainX)

	testX = test[test$uid %in% x,]
	f = predict(lineF, testX)
	c = predict(lineC, testX)
	l = predict(lineL, testX)

	test[test$uid %in% x,]$f = f
	test[test$uid %in% x,]$c = c
	test[test$uid %in% x,]$l = l
}


if (T){
testX =test[test$uid > cntUser,]

attach(train)
lineF = lm(forward~cnt+text+http+keyword+face)
lineC = lm(comment~cnt+text+http+keyword+face)
lineL = lm(like~cnt+text+http+keyword+face)
detach(train)
	
f = predict(lineF, testX)
c = predict(lineC, testX)
l = predict(lineL, testX)

test[test$uid > cntUser,]$f = f
test[test$uid > cntUser,]$c = c
test[test$uid > cntUser,]$l = l
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

ans = data.frame(test$userId, test$blogId, f, c, l)
write.csv(ans, "ans.csv", row.names=F, quote=F)

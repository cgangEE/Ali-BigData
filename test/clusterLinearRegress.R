#!/usr/bin/env Rscript
user = read.csv("user.out")
user = user[,-1]

lenUser = length(user)
cntUser = dim(user)[1]

for(i in 1:lenUser){
	if (max(user[,i]) == 0)
		next
	user[,i] =user[,i]/max(user[,i])
}


center = 5
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



if (T){
testX =test[test$uid > cntUser,]

attach(train)
lineF = lm(forward~cnt+text+http+face)
lineC = lm(comment~cnt+text+http+face)
lineL = lm(like~cnt+text+http+face)
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

df = abs(f-test$forward)/(test$forward+5)
dc = abs(c-test$comment)/(test$comment+3)
dl = abs(l-test$like)/(test$like+3)

prec = 1-0.5*df-0.25*dc-0.25*dl

test$prec = prec

count = test$forward+test$comment+test$like
count[count>100]=100

sgn=function(prec){
	ret=1:length(prec)
	ret[prec<=0]=0
	ret[prec>0]=1
	return(ret)
}

flag = sgn(prec - 0.8)
r = test[flag==1,]
w = test[flag==0,]

eval = sum((count+1)*sgn(prec-0.8))/sum(count+1)
print(eval)


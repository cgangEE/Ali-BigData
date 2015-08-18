#!/usr/bin/env Rscript
user = read.csv("user.out")
user = user[,-1]
user = user[,-13]

lenUser = length(user)

for(i in 1:lenUser){
	user[,i] =user[,i]/max(user[,i])
}

user$http = user$http * 0.1
user$face = user$face * 0.1

center = 5
cl = kmeans(user, center)

par(mfrow = c(4, 4))
attach(user)
plot(forward, col=cl$cluster)
plot(comment, col=cl$cluster)
plot(like, col=cl$cluster)
plot(df, col=cl$cluster)
plot(dc, col=cl$cluster)
plot(dl, col=cl$cluster)
plot(maxf, col=cl$cluster)
plot(maxc, col=cl$cluster)
plot(maxl, col=cl$cluster)
plot(minf, col=cl$cluster)
plot(minc, col=cl$cluster)
plot(minl, col=cl$cluster)
plot(http, col=cl$cluster)
plot(face, col=cl$cluster)

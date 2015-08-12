help(read.table)
babies = present$girls + present$boys

plot(present$year, babies)
plot(present$year, present$boys/(present$boys + present$girls))
plot(present$year, present$boys/(present$girls))
present$year[which.max(abs(present$boys - present$girls))]
load(url("http://s3.amazonaws.com/assets.datacamp.com/course/dasi/cdc.Rdata"))
names(cdc)
head(cdc)
tail(cdc)
dim(cdc)
typeof(cdc$genhlth)
head(cdc)
head(cdc$height)
head(cdc$genhlth)
mean(cdc$weight)
var(cdc$weight)
median(cdc$weight)
summary(cdc$weight)
table(cdc$genhlth)
table(cdc$genhlth)/dim(cdc)[1]
barplot(cdc$smoke100)
summary(cdc$gender)
summary(cdc$genhlth)
table(cdc$gender, cdc$smoke100)
cdc[1337,5]
cdc[111,6]
cdc[1:8, 6:9]
cdc[10:20,6:9]
cdc[205,]
cdc[,5:6]
cdc$smoke100[1000]
cdc$height[1:30]
subset(cdc,cdc$health == 'very good')
subset(cdc,cdc$age >= 50)
boxplot(cdc$weight ~ cdc$smoke100)
cdc$weight / (cdc$height ^ 2) * 703
boxplot( bmi ~ cdc$genhlth)
load(url("http://s3.amazonaws.com/assets.datacamp.com/course/dasi/kobe.RData"))
names(kobe)
kobe$basket[1:9]
barplot(table(kobe_streak))


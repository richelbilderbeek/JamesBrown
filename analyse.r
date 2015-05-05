rm(list = ls())
library(testit)

getwd()
filename <- "Data/4.csv"
assert("Data file must exist",file.exists(filename))
t <- read.table(filename,header=FALSE,sep=",")
names(t) <- c("t_sec","h","t_c")
plot(t_c ~ t_sec,data = t)
plot(h ~ t_sec,data = t)
head(t)
ncol(t)
nrow(t)

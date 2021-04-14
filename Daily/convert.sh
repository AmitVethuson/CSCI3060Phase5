#!/bin/sh
chdir transactionFiles
for i in *.tmp
do
  
  mv -- "$i" "${i%.tmp}.txt"
 
done
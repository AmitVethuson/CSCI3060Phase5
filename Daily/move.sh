#!/bin/sh
chdir input

for i in *.txt
do 
    mv $i ../transactionFiles
done
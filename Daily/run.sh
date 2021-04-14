#!/bin/sh
chdir input

for i in *.inp
do
    echo "running test $i"
    ../../FrontEnd/./test $i ../../FrontEnd/"bankAccounts.txt" >>../output/$i
done


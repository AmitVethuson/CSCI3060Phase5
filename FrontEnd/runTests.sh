#!/bin/sh
chdir testers
for i in *.inp
do
  echo "running test $i"
  .././test $i ../"bankAccounts.txt" >>../output/$i
done
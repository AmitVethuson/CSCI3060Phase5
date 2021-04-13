#!/bin/sh
chdir output
for i in *.inp
do
  
  mv -- "$i" "${i%.inp}.bto"
 
done
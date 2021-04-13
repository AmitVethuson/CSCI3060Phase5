#!/bin/sh
chdir expoutput
for i in *
do
    echo $i
   .././compare $i "../output/$i" >> ../results/results$i
    
done

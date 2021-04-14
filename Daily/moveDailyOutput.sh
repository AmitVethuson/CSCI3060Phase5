#!/bin/sh
chdir ../Backend/out/production/


for i in *.txt
do
   
    mv $i  ../../../Daily/DailyOutputs
done
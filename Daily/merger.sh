#!/bin/sh
chdir transactionFiles
for i in *.txt
do
        
    cat $i >> mergedBankAccountTransaction.txt

done
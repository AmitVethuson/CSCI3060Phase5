#!bin/sh

#Set initial values before iterating over inputs
cd ..
rm Daily/BackendComponents/*
cp Weekly/masterBankAccounts.txt Daily/BackendComponents

# Run the daily script 5 times
for i in 1 2 3 4 5
do 
    #Move .inp files
    rm Daily/input/*
    cp Weekly/inputs/day$i/* Daily/input

    #Run the dailyscript
    cd Daily
    sh dailyScript.sh

    #Move new master bank accounts into BackEnd dir
    cd DailyOutputs
    newMaster=$(find . -name '*newMasterBankAccounts*')
    cp $newMaster masterBankAccounts.txt
    cd ..
    rm BackendComponents/*
    mv DailyOutputs/masterBankAccounts.txt BackendComponents 

    #Reset for next iteration
    cd ..
done

#Move final output into the weekly folder for organizational purposes
cp Daily/BackendComponents/masterBankAccounts.txt Weekly/output
(cd Weekly/output; mv masterBankAccounts.txt newMasterBankAccounts.txt;)

echo Weekly script complete
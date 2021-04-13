The test cases were run using automated scripting. 4 scripts were made in total. runtest is a script that run the program using input files
as commandline arguments and gets outputed into the output folder. The convert script changes the inp to bto. Then the comp script
compares the expected and outputs together and outputs it into results folder. 

In order to run the test, first load all input files into testers folder. Then load expected outputs to expoutput folder. After that 
run the script master.sh which runs all 3 scripts in order. The results will be outputed into the results folder.
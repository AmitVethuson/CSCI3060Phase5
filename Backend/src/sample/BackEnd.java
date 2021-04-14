package sample;

import java.io.*;
import java.text.DecimalFormat;
import java.util.Scanner;
import java.util.ArrayList;

public class BackEnd {

    //Global variables
    private static Account[] accounts;

    /**
     * Read accounts from the old master bank accounts file
     * and creates an instance of Account for each account
     * @param file: filepath of the old master bank accounts file
     */
    private static void loadAccounts(String file) {
        ArrayList<Account> accountList = new ArrayList<Account>();;
        //Open the old master bank accounts file
        try {
            File oldMaster = new File(file);
            Scanner reader = new Scanner(oldMaster);
            String line;
            while(reader.hasNextLine()) {
                line = reader.nextLine();

                //Get account info from the line of read text
                int accountNum = Integer.parseInt(line.substring(0,5));
                String accountHolder = line.substring(6,26).trim();
                char statusChar = line.charAt(27);
                boolean status = (statusChar == 'A');
                double balance = Double.parseDouble(line.substring(29,37));
                int numTransactions = Integer.parseInt(line.substring(38));

                //Create account object from the info
                accountList.add(new Account(accountHolder,accountNum,status,balance,false, numTransactions));
            }
            reader.close();

            accounts = accountList.toArray(new Account[accountList.size()]);
            sortByAccountNumber();
        }catch(Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Reads all transactions from the merge bank account transaction file
     * and processes them
     * @param file: filepath of the merged bank account transaction file
     */
    private static void assignTransactions(String file) {
        //Open merged bank account transaction file
        try {
            File transactions = new File(file);
            Scanner reader = new Scanner(transactions);
            String line;
            while (reader.hasNextLine()) {
                line = reader.nextLine();

                //Get transaction info from the line of read text
                int code = Integer.parseInt(line.substring(0,2));
                String holder = line.substring(3,23).trim();
                int accountNum = Integer.parseInt(line.substring(24,29));
                double funds = Double.parseDouble(line.substring(30,38));
                String additInfo = line.substring(39);

                //Determine the account that the transaction applies to
                for(int i = 0; i < accounts.length; i++) {
                    if(accounts[i].getAccountHolder().compareTo(holder) == 0 &&
                            accounts[i].getNumber() == accountNum) {
                        //Assign the transaction the appropriate
                        if(!additInfo.equals("  ")) {
                            accounts[i].addTransaction(code,funds,additInfo);
                        }
                        else {
                            accounts[i].addTransaction(code,funds);
                        }
                        break;
                    }
                }
            }
        } catch(Exception e) {
            e.printStackTrace();
        }

        //Apply all of the transactions
        for (Account i:accounts) {
            i.applyTransactions();
        }
    }

    /**
     * Sorts the list of bank accounts by account number in ascending order
     */
    private static void sortByAccountNumber() {
        //Sort using insertion sort
        int j;
        Account key;
        for(int i = 1; i < accounts.length; i++) {
            key = accounts[i];
            j = i-1;
            while(j >= 0 && accounts[j].getNumber() > key.getNumber()) {
                accounts[j+1] = accounts[j];
                j = j-1;
            }
            accounts[j+1] = key;
        }
    }

    /**
     * Format account info into a string for output files
     * @param a: an account with data to be transcribed
     * @return a formatted string containing the data of 'a'
     */
    private static String formatAccountData(Account a) {
        String entry = "";
        //Format account number
        for(int k = 0; k < 5-Integer.toString(a.getNumber()).length(); k++) {
            entry = entry + "0";
        }
        entry = entry + Integer.toString(a.getNumber()) + " ";
        //Format account holder name
        entry = entry + a.getAccountHolder();
        for(int k = 0; k < 20-a.getAccountHolder().length(); k++) {
            entry = entry + " ";
        }
        entry = entry + " ";
        //Format active status
        if(a.getIsEnabled()) {
            entry = entry + "A";
        }
        else {
            entry = entry + "D";
        }
        entry = entry + " ";
        //Format balance
        DecimalFormat df = new DecimalFormat("#.00");
        for(int k = 0; k < 8-df.format(a.getBalance()).length(); k++) {
            entry = entry + "0";
        }
        entry = entry + df.format(a.getBalance());

        return entry;
    }

    /**
     * Creates current bank accounts file with the active account data
     */
    private static void createCurrentBankAccounts() {
        //Create new current bank accounts file
       // String workingDir = System.getProperty("user.dir");
        String filepath = "newCurrentBankAccounts.txt";
        try {
            new File(filepath);
            FileWriter writer = new FileWriter(filepath);

            //Create entries for the file for each account
            for (Account i:accounts) {
                //Only add active accounts to the file
                if(i.getIsEnabled()) {
                    writer.write(formatAccountData(i) + "\n");
                }
            }
            writer.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Creates master bank accounts file with all of the account data
     */
    private static void createMasterBankAccounts() {
        //Create new master bank accounts file
        String workingDir = System.getProperty("user.dir");
        String filepath = workingDir + "\\output\\newMasterBankAccounts.txt";
        try {
            new File(filepath);
            FileWriter writer = new FileWriter(filepath);

            //Create entries for the file for each account
            for (Account i:accounts) {
                //Add the number of transactions to the transcribed account data
                String numTransactions = "";
                for(int k = 0; k < 4-Integer.toString(i.getNumTransaction()).length(); k++) {
                    numTransactions = numTransactions + "0";
                }
                numTransactions = numTransactions + Integer.toString(i.getNumTransaction());
                writer.write(formatAccountData(i) + " " + numTransactions + "\n");
            }
            writer.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Main method
     * @param args: array of command line arguments
     */
    public static void main(String[] args) {
        loadAccounts(args[0]); //Load accounts from the old master bank accounts file
        assignTransactions(args[1]); //Load transactions
        createCurrentBankAccounts(); //Create new current bank accounts file
        createMasterBankAccounts(); //Create new master bank accounts file
    }
}

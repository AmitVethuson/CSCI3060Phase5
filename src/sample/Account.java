package sample;
import java.util.Queue;
import java.util.LinkedList;


public class Account {
    public  Queue<Transaction>  transaction = new LinkedList<>();
    private String accountHolder;
    private int number;
    private  boolean IsEnabled;
    private double balance;
    private boolean isDeleted;
    private int numTransaction;
    private String paymanetPlan;

    //constructor
    public Account(String accountHolder, int number, boolean IsEnabled, double balance, boolean isDeleted, int numTransactions, String paymanetPlan){
        this.accountHolder =accountHolder;
        this.number = number;
        this.IsEnabled = IsEnabled;
        this.balance = balance;
        this.isDeleted = isDeleted;
        this.numTransaction = numTransactions;
        this.paymanetPlan = paymanetPlan;
    }
    //constructor if there is no payment plan
    public Account(String accountHolder, int number, boolean IsEnabled, double balance, boolean isDeleted, int numTransactions){
        this.accountHolder =accountHolder;
        this.number = number;
        this.IsEnabled = IsEnabled;
        this.balance = balance;
        this.isDeleted = isDeleted;
        this.numTransaction = numTransactions;
    }

    // add transaction to queue of transaction
    // inputs are code of transaction, amount of funds, and information and additional info
    public void addTransaction(int code, double transactionFunds, String additionalInfo){
        Transaction newTransaction = new Transaction(getAccountHolder(),code,getNumber(),transactionFunds,additionalInfo);
        transaction.add(newTransaction);
        this.numTransaction++;

    }
    //with no additional info
    public void addTransaction(int code, double transactionFunds){
        Transaction newTransaction = new Transaction(getAccountHolder(),code,getNumber(),transactionFunds);
        transaction.add(newTransaction);
        this.numTransaction++;

    }

    //deletes first transaction in queue then applies transaction to account
        public void applyTransactions(){
        while(transaction.size() > 0) {
            Transaction current = transaction.remove();
            int code = current.getCode();
            if (code == 1) {
                this.balance = getBalance() - current.getTransactionFunds();
            } else if (code == 2) {
                this.balance = getBalance() - current.getTransactionFunds();
            } else if (code == 3) {
                this.balance = getBalance() - current.getTransactionFunds();
            } else if (code == 4) {
                this.balance = getBalance() + current.getTransactionFunds();
            } else if (code == 6) {
                this.isDeleted = true;
            } else if (code == 7) {
                //check if additionalInfo is A or D
                if (current.getAdditionalInfo() == "A") {
                    this.IsEnabled = true;
                } else if (current.getAdditionalInfo() == "D") {
                    this.IsEnabled = false;
                }

            } else if (code == 8) {
                this.paymanetPlan = current.getAdditionalInfo();
            }
        }
    }

    //getters
    public String getAccountHolder(){return accountHolder;}

    public int getNumber(){return number;}

    public boolean getIsEnabled(){return  IsEnabled;}

    public double getBalance(){ return balance; }

    public boolean getIsDeleted(){ return isDeleted; }

    public int getNumTransaction(){return numTransaction;}

    public String getPaymanetPlan(){return paymanetPlan;}



}


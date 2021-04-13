package sample;
public class Transaction {
    private String accountName;
    private int code;
    private int accountNum;
    private double transactionFunds;
    private String additionalInfo;

    // constructor
    public Transaction(String accountName, int code, int accountNum, double transactionFunds, String additionalInfo){
        this.accountName = accountName; 
        this.code = code;
        this.accountNum = accountNum;
        this.transactionFunds = transactionFunds;
        this.additionalInfo = additionalInfo;

    }
    //constructor with no additionalInfo
    public Transaction(String accountName, int code, int accountNum, double transactionFunds){
        this.accountName = accountName;
        this.code = code;
        this.accountNum = accountNum;
        this.transactionFunds = transactionFunds;


    }

    //getters
    public String getAccountName(){
        return accountName;
    }
    public int getCode(){ return code;}
    public int getAccountNum(){
        return accountNum;
    }
    public double getTransactionFunds(){
        return  transactionFunds;
    }
    public String getAdditionalInfo(){
        return additionalInfo;
    }
}

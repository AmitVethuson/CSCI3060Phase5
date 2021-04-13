package sample;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class applyTransactionTest {


    //   decision and loop coverage of apply transaction
    @Test
    public void shouldNotLoop(){
        Account a = new Account("Bob",00001,true, 1,false,0);
        a.applyTransactions();
        assertEquals(0,a.getNumTransaction());
    }

    @Test
    public void shouldWithDrawl(){
        Account a = new Account("Bob",00001,true, 1,false,1);
        a.addTransaction(1,1);
        a.applyTransactions();
        assertEquals(0,a.getBalance());
    }
    @Test
    public void shouldTransfer(){
        Account a = new Account("Bob",00001,true, 1,false,1);
        a.addTransaction(2,1);
        a.applyTransactions();
        assertEquals(0,a.getBalance());
    }

    @Test
    public void shouldPaybill(){
        Account a = new Account("Bob",00001,true, 1,false,1);
        a.addTransaction(3,1);
        a.applyTransactions();
        assertEquals(0,a.getBalance());
    }

    @Test
    public void shouldDeposit(){
        Account a = new Account("Bob",00001,true, 0,false,1);
        a.addTransaction(4,1);
        a.applyTransactions();
        assertEquals(1,a.getBalance());
    }

    @Test
    public void shouldDelete(){
        Account a = new Account("Bob",00001,true, 0,false,1);
        a.addTransaction(6,0);
        a.applyTransactions();
        assertEquals(true,a.getIsDeleted());
    }

    @Test
    public void shouldEnable(){
        Account a = new Account("Bob",00001,false, 0,false,1);
        a.addTransaction(7,0,"A");
        a.applyTransactions();
        assertEquals(true,a.getIsEnabled());
    }

    @Test
    public void shouldDisable(){
        Account a = new Account("Bob",00001,true, 0,false,1);
        a.addTransaction(7,0,"D");
        a.applyTransactions();
        assertEquals(false,a.getIsEnabled());
    }

    @Test
    public void shouldNotEnableorDisable(){
        Account a = new Account("Bob",00001,true, 0,false,1);
        a.addTransaction(7,0);
        a.applyTransactions();
        assertEquals(true,a.getIsEnabled());
    }

    @Test
    public void shouldDoNothing(){
        Account a = new Account("Bob",00001,true, 1,false,1,"N");
        a.addTransaction(0,1,"D");
        a.applyTransactions();
        int tester=0;
        if(a.getBalance() == 1){
            tester++;
        }
        if(a.getIsEnabled() == true){
            tester++;
        }
        if(a.getPaymanetPlan() == "N"){
            tester++;
        }
        if(a.getIsDeleted() == false){
            tester++;
        }

        assertEquals(4,tester);
    }

    @Test
    public void shouldLoopTwice(){
        Account a = new Account("Bob",00001,true, 0,false,2);
        for (int i=0;i<2;i++){
            a.addTransaction(4,1);
        }
        a.applyTransactions();
        assertEquals(2,a.getBalance());
    }

    @Test
    public void shouldLoopManyTimes(){
        Account a = new Account("Bob",00001,true, 0,false,10);
        for (int i=0;i<10;i++){
            a.addTransaction(4,1);
        }
        a.applyTransactions();
        assertEquals(10,a.getBalance());
    }







}
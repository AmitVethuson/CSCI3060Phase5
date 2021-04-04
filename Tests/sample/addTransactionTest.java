package sample;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class addTransactionTest {

//    statement coverage for addTransaction
    @Test
    public void statment1AddTransaction(){
        Account a = new Account("Bob",00001,true, 1,false,0);
        a.addTransaction(1,1,"a");
        assertEquals(1,a.transaction.size());
    }

    @Test
    public void statment2AddTransaction(){
        Account a = new Account("Bob",00001,true, 1,false,0);
        a.addTransaction(1,1,"a");
        assertEquals(1,a.transaction.size());
    }
    @Test
    public void statment3AddTransaction(){
        Account a = new Account("Bob",00001,true, 1,false,0);
        a.addTransaction(1,1,"a");
        assertEquals(1,a.getNumTransaction());
    }

}
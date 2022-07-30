#include<iostream>
#include <sstream>

#include "Transaction.hpp"
#include "Block.hpp"
#include "Blockchain.hpp"
#include<vector>

using namespace std;

Blockchain::Blockchain() {
    Transaction genesis("BFC", "BFC", 0);
    pending.push_back(genesis);

    Block gBlock(pending, time(nullptr), "In the beginning..");
    chain.push_back(gBlock);

    pending.clear();
    Transaction freeMoney("BFC", "make money by mining", 0);
    pending.push_back(freeMoney);

    cout << "\nSuccessfully Initiated Chain: Genesis Block Inserted\n";
    difficulty = 4;
    miningReward = 10;
}

void Blockchain::makeInvalid()
{
    chain.begin()->sethash("You Have Changed this Hash of Genesis Block,Making Whole Chain Invalid!");
}

Block Blockchain::getLatestBlock() { 
    return chain.back();
}

void Blockchain::addTransaction(string src, string dst, int coins) {
  Transaction newTransaction(src,dst,coins);
    if(getBalanceOfAddress(src)>coins)
    {
      pending.push_back(newTransaction); //If Balance of sender is greater than sending-amount is sufficient Transaction will be added
      cout<<"Success! Added Transaction in Pending!";
    }
    else{
        //OtherWise transaction will be Blocked/Terminated
      cout<<"Unsuccessful! Transaction Blocked due to Insufficient Balance\n";
    }
}

bool Blockchain::isChainValid() { 
  vector<Block>::iterator ptr;
  bool flag=true;
  string hash="";
  string sub="";
  char* cstr = new char[difficulty + 1];
  char ch;

  /* Following for loop will make the difficulty string 
  which will be compared to hash. 
  if Difficulty = 4 this 'for' loop will generate a string of the form '0000'  */
  for (int i = 0; i < difficulty; ++i) {
      cstr[i] = '0';
  }
  cstr[difficulty] = '\0';//ending element of every string Which tells the string ends here.
  string str(cstr); //Converting pointer of char to string

  for(ptr=chain.begin()+1;ptr<chain.end();ptr++)
    {
        hash=ptr->gethash();
        sub=hash.substr(0,difficulty);//It will extract the first four characters of hash
        if(sub != cstr)//if first four characters of hash is equal to the cstr(our validity checking string)
          flag=false;
        if(ptr->getprevhash() !=(ptr-1)->gethash())/*Compares 'prevHash' of current block with its previous Blocks' hash*/
          flag=false;
    }
    return flag;
}
bool Blockchain::minePendingTransactions(string minerAddress) {
  /*Generating a new Block passing to it 'pending','currenttime','PreviousHash'.
  This previous hash will be the hash of latest block of Chain*/
  Block newBlock(pending,time(nullptr),getLatestBlock().gethash());
  newBlock.mineBlock(difficulty);//MiningBLock of 'difficulty'
  chain.push_back(newBlock);
  pending.clear();

  /*Rewarding Miner with miningReward and adding this transaction to pending.*/
  Transaction newTransaction("BFC",minerAddress,miningReward);
  pending.push_back(newTransaction);
  cout<<"Adding new Transaction to pending:"<<newTransaction.toString();
  return true;
}

int Blockchain::getBalanceOfAddress(string address) {
    int balance=0;
    vector<Transaction> t;
    vector<Transaction>::iterator ptr_T;
    vector<Block>::iterator ptr_B;

    /*For Loop:Iterating over each block in Chain*/
    for (ptr_B = chain.begin(); ptr_B < chain.end(); ptr_B++)
    {
        t = ptr_B->gettransactions();
        /*For Loop:Iterating over each transaction of Respective Block*/
        for (ptr_T = t.begin(); ptr_T < t.end(); ptr_T++)
        {
            /*If address is sending amount. Minus this amount from balance*/
            if (ptr_T->getSender() == address)
                balance = balance - ptr_T->getAmount();
            /*If address is receiving amount. plus this amount to balance*/
            if (ptr_T->getReceiver() == address)
                balance = balance + ptr_T->getAmount();
        }
    }
  return balance;
  }

vector<Transaction> Blockchain::getpending()
{
  return pending;
}

void Blockchain::getpendinglist()
{
  vector<Transaction>::iterator ptr_T;
  for(ptr_T=pending.begin();ptr_T<pending.end();ptr_T++)
    if(ptr_T==pending.end())
    cout<<ptr_T->toString();
    else
    cout<<ptr_T->toString() << "->";
}

void Blockchain::all_block_hash()
{
  vector<Transaction> t;
    vector<Transaction>::iterator ptr_T;
    vector<Block>::iterator ptr_B;
    int count=1;
    for(ptr_B=chain.begin();ptr_B<chain.end();ptr_B++)
  {
    t=ptr_B->gettransactions(); 
    cout<<"[Hash' Block#"<<count<<"]:"<<ptr_B->gethash()<<endl;
    if(ptr_B!=chain.end()-1)
    {
      cout<<"   |   "<<endl;
      cout<<"   V   "<<endl;
    }
    count=count+1;
  }
}

void Blockchain::prettyPrint() {
    vector<Transaction> t;
    vector<Transaction>::iterator ptr_T;
    vector<Block>::iterator ptr_B;
    int count=1;

    /*For Loop:Iterating over each block in Chain*/
       
    for(ptr_B=chain.begin();ptr_B<chain.end();ptr_B++)
  {
    t=ptr_B->gettransactions(); 
    cout<<"[Transactions' Block#"<<count<<"]:";

    /*For Loop:Iterating over each transaction of Respective Block*/
    for(ptr_T=t.begin();ptr_T<t.end();ptr_T++)
      {
        if(ptr_T!=(t.end()-1))
        cout<<ptr_T->toString()<<"->";
        else
        cout<<ptr_T->toString()<<endl;
      }
    if(ptr_B!=chain.end()-1)
    {
      cout<<"   |   "<<endl;
      cout<<"   V   "<<endl;
    }
    count=count+1;//To keep count of Block
  }
}
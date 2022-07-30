#include<iostream>
#include <sstream>


#include "Transaction.hpp"
#include "Block.hpp"
#include "sha256.hpp"

using namespace std;

string Block::calculateHash() {
    hash=sha256(toString());
    return hash;   
}

Block::Block(vector<Transaction> _transactions, time_t _timestamp, string _previousHash) {
    nonce = -1;
    transactions = _transactions;
    previousHash = _previousHash;
    timestamp = _timestamp;
    hash = calculateHash();
}

vector<Transaction> Block::gettransactions()
{
  return transactions;
}

void Block::sethash(string s)
{
  hash=s;
}

string Block::getprevhash()
{
  return previousHash;
}

string Block::gethash()
{
  return hash;
}

void Block::setPreviousHash(string _previousHash) {
    previousHash = _previousHash;
}



void Block::mineBlock(unsigned int difficulty) {
    char *cstr=new char[difficulty + 1];
    char ch;
    for (int i = 0; i < difficulty; ++i) {
        cstr[i] = '0';
    }
    cstr[difficulty] = '\0';
    string str(cstr);

    cout << "\nMine Block Using Brute Force(y/n) It will take Some Time to compute:";
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        
        //------------------to run with brute force------------------------
        cout << "\npleasewait! calculating nonce and valid hash. . .";
        /*Following Do while Will keep incrementing nonce and calculate new hash
        of block with nonce*/
        do {
            nonce++;
            cout <<"Nonce: " << nonce << "\n";
            hash = calculateHash();
            cout <<"Hash: "<< hash << "\n";
        } while (hash.substr(0, difficulty) != str);/*This while loop will check. 
                                                    If hash generated contains 'difficulty' number of zeros in its front
                                                    Than this while will terminate loop 
                                                    and block will be mined with that Hash*/
    }
    
    else {
        //------------------To Run Without Brute Force------------------------
        /*in this simply adding zeros in front of hash to make it valid*/
        hash = calculateHash();
        hash = cstr + hash;
    }
    cout << "Success! Block mined: " << hash << endl;
}

string Block::toString() {
    stringstream ss;
    ss << nonce;
  vector<Transaction>::iterator ptr;

  /*For Loop:Iterating over each transaction of Respective Block
  And passing each transaction in stringstream*/
  for(ptr=transactions.begin();ptr<transactions.end();ptr++)
    {
      ss<<ptr->toString();
    }
  ss<<previousHash<<timestamp;
    return ss.str();
}
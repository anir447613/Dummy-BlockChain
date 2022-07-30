#include <iostream>
#include <string>
#include "Blockchain.hpp"
using namespace std;
int main() {

  Blockchain buffCUoin; //Initiating Block Chain----------

  bool quit = false;
  int ch;
  while (!quit) {
  cout <<"\n======Main Menu======" << endl;
  cout <<"1. Add Transaction" << endl;
  cout <<"2. Mine Pending Transactions/Mine Block" << endl;
  cout <<"3. Verify Blockchain" << endl;
  cout<<"4. Find Balance of Address"<<endl;
  cout<<"5. PrettyPrint Blockchain"<<endl;
  cout<<"6. Get Pending Transactions"<<endl;
  cout<<"7. Show Hashes Of All Blocks in Blockchain."<<endl;
  cout << "8. Make BlockChain Invalid-Beware! Once its done Chain Wont be valid"<<endl;
  cout << "9. Quit" << endl;
  cout<<"Your Choice:";
  cin>>ch ;
  string sender,receiver,miner,address;
  int amount=0;
  switch (ch) {
    case 1:{
      cout<<"Enter Sender Name:";
      cin>>sender;
      cout<<"Enter Receiver Name:";
      cin>>receiver;
      cout<<"Enter amount to be transferred:";
      cin>>amount;
      cout << "\n================[Result]=================\n";
      buffCUoin.addTransaction(sender,receiver,amount);
      cout << "\n=========================================\n";
      break;
    }
    case 3:{
      if(buffCUoin.isChainValid())
      {
        cout << "\n================[Result]=================\n";
        cout<<"Yes! Chain is Valid.";
        cout << "\n=========================================\n";
      }
      else
      {
        cout << "\n================[Result]=================\n";
        cout<<"No! Chain is not Valid.";
        cout << "\n=========================================\n";

      }
      break;
    }
    case 2:
      {
        cout<<"Enter Miner Address:";
        cin>>miner;
        cout << "\n================[Result]=================\n";
        buffCUoin.minePendingTransactions(miner);
        cout << "\n=========================================\n";

      break;
      }
    case 4:
      {
        cout<<"Enter address to find balance:";
        cin>>address;
        cout << "\n================[Result]=================\n";
        cout<<"Balance of "<<address<<": "<<buffCUoin.getBalanceOfAddress(address);
        cout << "\n=========================================\n";
        break;
      }
    case 6:
      {
        cout << "\n================[Result]=================\n";
        buffCUoin.getpendinglist();
        cout << "\n=========================================\n";
        break;
      }
    case 5:
      {
        cout << "\n================[Result]=================\n";
        buffCUoin.prettyPrint();
        cout << "\n=========================================\n";
        break;
      }
    case 7:
      {
        cout << "\n================[Result]=================\n";
        buffCUoin.all_block_hash();
        cout << "\n=========================================\n";
        break;
      }
    case 8:
      {
        cout << "\n================[Result]=================\n";
        buffCUoin.makeInvalid();
        cout<<"\nChain is Now Invalid!";
        cout << "\n=========================================\n";
        break;
      }
    case 9:
    {
        cout << "\n================[Result]=================\n";
        cout << "Quitting";
        cout << "\n=========================================\n";
        quit = true;
        break;
    }
}
    }
      }
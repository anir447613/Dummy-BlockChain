# Dummy-BlockChain
Buff-CUoin (Design and Implementation of a Toy Cryptocurrency) using C++.
Project Specification
This Blockchain system supports the following functionality:
• Blockchain. A blockchain is implemented as a list of nodes called Blocks
where each block consists of a list of transactions, hashcode of the previous block, a
timestamp, and a parameter called nonce.
Page 2
• Transaction. A transaction is a simple structure containing three fields: sender (a
string), receiver (a string), and amount (int).
• List of Pending Transactions. A blockchain have a member called pending
that is a list of pending transactions, this is a must have for all real-life Blockchains.
• Crypto Mining. Periodically, all of the pending transactions are Finalized by a
process called mining. The process of mining is simply collecting all of the pending
transactions, packaging them in a block and inserting that block to the blockchain. In
order to make a blockchain secure, the insertion of a new block into the blockchain
must be a computationally complex task. This Blockchain have a private
integer-valued member called diffculty such that a block can only be inserted into
the chain if the nonce of the block is such that the hash-code of the contents of the
block along-with the nonce results in a hash-code with the first n characters (where
n = diffculty) are 0's. This process is called the mining of a block.
• Rewading Miners with Buff-CUoins. For every successful mining of a block, a
corresponding user (represented simply as a string) is paid a fixed amount of reward
that we call Bff-cuoins or BFCs.
• Balance Checking. Between the mining of blocks, the blockchain must receive
transactions containing three fields (sender, receivers, amount) documenting that
sender has paid the receiver number of coins equal to the given amount. These
transactions will be stored within the blockchain as a list of pending transactions. It
is the job of your algorithm to traverse the blockchain to see if the user corresponding
to the sender string has enough balance to be able to pay to the receiver. This is
done by traversing the blockchain, block-by-block, and traversing transactions
within each block in the sequence, and keeping the information about the sender's
history: adding all the coins received by her, and subtracting any coins spent.
• Validity Checking. This is aprocedure to check validity of a blockchain
by traversing the blockchain sequentially, computing the hashcode of every block and
checking if the next block has that hashcode in the field (previousHash).

#ifndef Client
#define Client
#include "STD.h"

// For client to make transaction
void MakeTransactionClient(u16 AccIDTrnsfrFrom,u16 AccIDTrnsfrTo,u16 TransferAmountOfCash);

// For client to withdraw cash
void WithdrawClient(u16 BankAccountID,u16 TransferAmoutRequired);

// For client to deposit cash
void DepositInAccountClient(u16 BankAccountID,u16 TransferAmoutRequiredToDeposit);

void ChangePassword(u16 OldPW,u16 NewPW,u16 BankAccountID);

void ClientMode(void);


#endif // Client

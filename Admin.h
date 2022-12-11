#ifndef Admin
#define Admin
#include "STD.h"

typedef struct BankAcc node;
struct BankAcc{
	u8 FullName[100];
	u8 FullAddress[100];
	ul64 NationalID;
	u32 Age;
	u32 BankAccountID;
	u8 GuardianName[100];
	ul64 GuardianNationalID;
	u32 AccountStatus;
	u32 Balance;
	u32 Password;
	node *next;
	node *pre;
};

// Functions
// To create dummy account
void CreateDummyAcc(void);
//To create new account
void CreateNewAcc(void);
// To open an existing account
void OpenExistingAcc(void);
void ChangeAccStatus(u16 BankAccountID);
void AdminMode(u16 *ext);
u32 GenerateID(void);
u32 GeneratePW(void);

// For Admin to make transaction
void MakeTransactionAdmin(u16 AccIDTrnsfrFrom,u16 AccIDTrnsfrTo,u16 TransferAmountOfCash);
// For Admin to withdraw cash
void WithdrawAdmin(u16 BankAccountID,u16 TransferAmoutRequired);
// For Admin to deposit cash
void DepositInAccountAdmin(u16 BankAccountID,u16
TransferAmoutRequiredToDeposit);

#endif //Main

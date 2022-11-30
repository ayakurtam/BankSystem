#include<stdio.h>
#include<stdlib.h>


typedef struct BankAcc node;
struct BankAcc{
	char FullName[100];
	char FullAddress[100];
	int NationalID;
	int Age;
	int BankAccountID;
	int GuardianName;
	int GuardianNationalID;
	int AccountStatus;
	int Balance;
	int Password;	
	node *next;
	node *pre;
};

node *ptr;
node *first = NULL;
node *last = NULL;

//Admis user and pw
int AdminUser= 2000;
int AdminPW = 2022;

//Prototypes
void CreateDummyAcc(void);
void CreateNewAcc(void);
void MakeTransaction(int AccIDTrnsfrFrom,int AccIDTrnsfrTo,int TransferAmountOfCash);
void OpenExistingAcc(void);
void ChangeAccStatus(int BankAccountID);
void Withdraw(int BankAccountID,int TransferAmoutRequired);
void DepositInAccount(int BankAccountID,int TransferAmoutRequiredToDeposit);
void ChangePassword(int OldPW,int NewPW,int BankAccountID);
void AdminMode(int *ext);
void ClientMode(void);

int main()
{
	int choice,Exit=0;
	CreateDummyAcc();
	while(1)
	{
		printf("Welcome to Bank account system\n");
		printf("To enter Admin mode press 1\nTo enter Client mode press 2\nYour choice is :");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			AdminMode(&Exit);
			break;
			case 2:
			ClientMode();
			break;
			default:
			printf("Wrong Choice\n");
			break;
 		}
		if(Exit==1)
		{
			break;
		}		
	
	}
}

void CreateDummyAcc(void){
	node*ptrDummy=(node*)malloc(sizeof(node));
	ptrDummy->next=NULL;
	ptrDummy->pre=NULL;
	first=ptrDummy;
	last=ptrDummy;
}

//Creating New Account 
void CreateNewAcc(void){
	
	node*ptrNew=(node*)malloc(sizeof(node));
	ptrNew->pre=last;
	ptrNew->next=NULL;
	last->next=ptrNew;
	last=ptrNew;

	printf("Please Enter your Full Name (At least 1st four names): ");
	scanf(" %[^\n]",ptrNew->FullName);	
	printf("Please Enter your Full Address: ");
	scanf(" %[^\n]",ptrNew->FullAddress);
	printf("Please Enter your National ID (at least 14 digits): ");
	scanf("%d",&ptrNew->NationalID);
	printf("Please Enter your Age: ");
	scanf("%d",&ptrNew->Age);
	if(ptrNew->Age<21)
	{
		printf("Please Enter your Guardian Name: ");
		scanf(" %[^\n]",ptrNew->GuardianName);
		printf("Please Enter your Guardian National ID (at least 14 digits): ");
		scanf("%d",&ptrNew->GuardianNationalID);
	}
	printf("Please Enter your Balance");
	scanf("%d",&ptrNew->Balance);
	ptrNew->AccountStatus=1;
	printf("Please Enter bank Account ID");
	scanf("%d",&ptrNew->BankAccountID);
	printf("Please Enter your Password");
	scanf("%d",&ptrNew->Password);
}

void MakeTransaction(int AccIDTrnsfrFrom,int AccIDTrnsfrTo,int TransferAmountOfCash){
	int flag1=0,flag2=0;
	ptr=first;
	while(ptr!=NULL)
	{	
			if(AccIDTrnsfrFrom==ptr->BankAccountID&& ptr->AccountStatus==1&&ptr->Balance>TransferAmountOfCash)
			{
				flag1=1;			
			}
			if(AccIDTrnsfrTo==ptr->BankAccountID && ptr->AccountStatus==1)
			{	
				flag2=1;
			}
		ptr=ptr->next;
	}
	if(flag1==1&&flag2==1)
	{	ptr=first;
		while(ptr!=NULL)
		{
			if(AccIDTrnsfrFrom==ptr->BankAccountID&& ptr->AccountStatus==1)
			{
				printf("Your balance was :%d \n",ptr->Balance);
				ptr->Balance-=TransferAmountOfCash;
				printf("Your balance now is :%d \n",ptr->Balance);
			}
			if(AccIDTrnsfrTo==ptr->BankAccountID && ptr->AccountStatus==1)
			{
				printf("Your balance was :%d \n",ptr->Balance);
				ptr->Balance+=TransferAmountOfCash;	
				printf("Your balance now is :%d \n",ptr->Balance);
			}
		ptr=ptr->next;	
		}
	}else{printf("The accounts you entered either not active or does not exist\n");}
	
}	

void OpenExistingAcc(void){
	int choice;
	printf("To make transaction press: 1 \n ");
	printf("To change status press: 2 \n ");
	printf("To withdraw press: 3 \n ");
	printf("To deposit  press: 4 \n ");
	printf("To return to main menu press: 5 \n ");
	scanf("%d",&choice);	
	switch(choice)
	{
		case 1:
		{ int AccID1,AccID2,TransferAmout;
			printf("Please enter the account ID to transfer from");
			scanf("%d",&AccID1);
			printf("Please enter the account ID to transfer to");
			scanf("%d",&AccID2);
			printf("Please enter the amount to be transfered");
			scanf("%d",&TransferAmout);
		MakeTransaction(AccID1,AccID2,TransferAmout);
		}
		break;
		case 2:
		{
			int AccID; 
			printf("Please enter the account ID to change the status");
			scanf("%d",&AccID);
			ChangeAccStatus(AccID);
		}
		break;
		case 3:
		{	int AccIDW,TransferAmout1; 
			printf("Please enter the account ID to withdraw ");
			scanf("%d",&AccIDW);
			printf("Please enter the amount you want");
			scanf("%d",&TransferAmout1);
			Withdraw(AccIDW,TransferAmout1);
		}
		break;
		case 4:
		{
			int AccIDD,TransferAmout2; 
			printf("Please enter the account ID to deposit cash ");
			scanf("%d",&AccIDD);
			printf("Please enter the amout you want to deposit");
			scanf("%d",&TransferAmout2);			
			DepositInAccount(AccIDD,TransferAmout2);
		}
		break;
		case 5:
				return;
		break;
		default:
		printf("Wrong Choice\n");
		break;
		
	}
}	

void ChangeAccStatus(int BankAccountID){
	int choice;
	printf("Please enter the bank account statues 1 for active 2 for restricted 3 for closed ");
	scanf("%d",&choice);
    switch(choice)
	{
		case 1:
			ptr=first;
			while(ptr!=NULL)
			{
				if( ptr->BankAccountID==BankAccountID)
				{
					ptr->AccountStatus=1;
				}
				ptr=ptr->next;			
			}
		break;
		case 2:
			ptr=first;
			while(ptr!=NULL)
				{
					if( ptr->BankAccountID==BankAccountID)
					{
						ptr->AccountStatus=2;
					}
				ptr=ptr->next;					
				}
		break;
		case 3:
			ptr=first;
			while(ptr!=NULL)
				{
					if( ptr->BankAccountID==BankAccountID)
					{
						ptr->AccountStatus=3;
					}	
					ptr=ptr->next;					
				}
		break;
		default:
		printf("wrong choice \n");
		break;
	}
}

void Withdraw(int BankAccountID,int TransferAmoutRequired){
	ptr=first;
			while(ptr!=NULL)
			{
				if( ptr->BankAccountID==BankAccountID&&ptr->Balance>TransferAmoutRequired&&ptr->AccountStatus==1)
				{	
					printf("your balance was  :%d \n",ptr->Balance);
					ptr->Balance-=TransferAmoutRequired;
					printf("your balance now is :%d \n",ptr->Balance);
				}
				ptr=ptr->next;			
			}
}	

void DepositInAccount(int BankAccountID,int TransferAmoutRequiredToDeposit){
	
	ptr=first;
	while(ptr!=NULL)
	{
		if( ptr->BankAccountID==BankAccountID&&ptr->AccountStatus==1)
		{	
			printf("your balance was :%d \n",ptr->Balance);
			ptr->Balance+=TransferAmoutRequiredToDeposit;
			printf("your balance now is :%d \n",ptr->Balance);
		}
		ptr=ptr->next;			
	}
}

void ChangePassword(int OldPW,int NewPW,int BankAccountID){
	ptr=first;
	while(ptr!=NULL)
	{
		if( ptr->Password==OldPW&&BankAccountID==ptr->BankAccountID)
		{	
			ptr->Password=NewPW;
		}
		ptr=ptr->next;			
	}
}

void AdminMode(int *ext){
	int user,pw,choice;
	printf("Please enter the user name of admin :");
	scanf("%d",&user);
	printf("Please enter the password for admin :");
	scanf("%d",&pw);
	if(user==AdminUser &&pw==AdminPW)
	{
		printf("Welcome admin\n");
		printf("Please select from the below menu\n");
		printf("1:creat new account\n");
		printf("2:open existing account\n");
		printf("3:Exit system \n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			
			CreateNewAcc();
			break;
			case 2:
			OpenExistingAcc();
			break;
			case 3:
			*ext=1;
			break;
			default:
			break;
		}
	}else{
		printf("incorrect user name or pw for admin\n");
	}
}

void ClientMode(void){
	
	int BankAccID1,PassWord1;
	printf("Please enter the bank account ID :");
	scanf("%d",&BankAccID1);
	printf("Please enter the password for bank account :");
	scanf("%d",&PassWord1);
	ptr=first;
	while(ptr!=NULL)
	{
		if (BankAccID1== ptr->BankAccountID&&PassWord1==ptr->Password)
		{
			int choice1;
			printf("Welcome our dear client\n");
			printf("Please select from the below menu:\n");
			printf("1:make transaction\n");
			printf("2:change account password\n");
			printf("3:Get cash\n");
			printf("4:Deposite in the account \n");
			printf("5:return to main menu \n");
			printf("your choice :");
			scanf("%d",&choice1);
			switch(choice1)
			{
				case 1:
				{	
					int bank_ID_from, bank_ID_to, TransferAmout;
					printf("Please enter the bank account ID trans from \n");
					scanf("%d",&bank_ID_from);
					printf("Please enter the bank account ID trans to \n");
					scanf("%d",&bank_ID_to);
					printf("Please enter the TransferAmout of money \n");
					scanf("%d",&TransferAmout);
					MakeTransaction(bank_ID_from, bank_ID_to, TransferAmout);
					return;
				}
				break;
				case 2:
				{	
					int new,old,id;
					printf("Please enter the old password");
					scanf("%d",&old);
					printf("Please enter the new password");
					scanf("%d",&new);
					printf("Please enter the account bank id");
					scanf("%d",&id);
					scanf("%d",&new);
					ChangePassword(old,new,id);
					return;
					
				}
				break;
				case 3:
				{
					int get,id;
					printf("Please enter the TransferAmout of cash needed ");
					scanf("%d",&get);
					printf("Please enter the bank account id  ");
					scanf("%d",&id);
					Withdraw(id,get);	
					return;
				}
				break;
				case 4:
				{
					int dep,id;
					printf("Please enter the TransferAmout of cash to deposit ");
					scanf("%d",&dep);
					printf("Please enter the account bank id");
					scanf("%d",&id);
					DepositInAccount(id,dep);
					return;
				}
				break;
				case 5:
				return;
				break;	
				
				default:
				printf("wrong choice :)\n");
				break;
			}
		}	
		ptr=ptr->next;
	}	
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STD.h"
#include "Admin.h"
#include "Client.h"

extern node *ptr;
node *FirstC = NULL;
void MakeTransactionClient(u16 AccIDTrnsfrFrom, u16 AccIDTrnsfrTo, u16 TransferAmountOfCash){
	u16 flag1=0,flag2=0;
	ptr=FirstC;
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
	{	ptr=FirstC;
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

void WithdrawClient(u16 BankAccountID,u16 TransferAmoutRequired){
	ptr=FirstC;
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

void DepositInAccountClient(u16 BankAccountID,u16 TransferAmoutRequiredToDeposit){

	ptr=FirstC;
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

void ChangePassword(u16 OldPW,u16 NewPW,u16 BankAccountID){
	ptr=FirstC;
	while(ptr!=NULL)
	{
		if( ptr->Password==OldPW&&BankAccountID==ptr->BankAccountID)
		{
			ptr->Password=NewPW;
			printf("Password Changed Successfully\n");
		}
		ptr=ptr->next;
	}
}

void ClientMode(void){

	u32 BankAccID1,PassWord1;
	printf("Please enter the bank account ID :");
	fflush(stdin);
	scanf("%d",&BankAccID1);
	printf("Please enter the password for bank account :");
	fflush(stdin);
	scanf("%d",&PassWord1);
	ptr=FirstC;
	u8 flag=0;
	while(ptr!=NULL)
	{
		if (BankAccID1== ptr->BankAccountID&&PassWord1==ptr->Password)
		{
			u16 choice1;
			printf("Welcome our dear client\n");
			printf("Please select from the below menu:\n");
			printf("1:make transaction\n");
			printf("2:change account password\n");
			printf("3:Get cash\n");
			printf("4:Deposite in the account \n");
			printf("5:return to main menu \n");
			printf("Your Choice :");
			fflush(stdin);
			scanf("%d",&choice1);
			flag++;
			switch(choice1)
			{
				case 1:
				{
					u16 bank_ID_from, bank_ID_to, TransferAmout;
					printf("Please enter the bank account ID trans from \n");
					fflush(stdin);
					scanf("%d",&bank_ID_from);
					printf("Please enter the bank account ID trans to \n");
					fflush(stdin);
					scanf("%d",&bank_ID_to);
					printf("Please enter the TransferAmout of money \n");
					fflush(stdin);
					scanf("%d",&TransferAmout);
					MakeTransactionClient(bank_ID_from, bank_ID_to, TransferAmout);
					return;
				}
				break;
				case 2:
				{
					u16 new,old,id;
					printf("Please enter the old password");
					fflush(stdin);
					scanf("%d",&old);
					printf("Please enter the new password");
					fflush(stdin);
					scanf("%d",&new);
					printf("Please enter the account bank id");
					fflush(stdin);
					scanf("%d",&id);
					ChangePassword(old,new,id);
					return;

				}
				break;
				case 3:
				{
					u16 get,id;
					printf("Please enter the TransferAmout of cash needed ");
					fflush(stdin);
					scanf("%d",&get);
					printf("Please enter the bank account id  ");
					fflush(stdin);
					scanf("%d",&id);
					WithdrawClient(id,get);
					return;
				}
				break;
				case 4:
				{
					u16 dep,id;
					printf("Please enter the TransferAmout of cash to deposit ");
					fflush(stdin);
					scanf("%d",&dep);
					printf("Please enter the account bank id");
					fflush(stdin);
					scanf("%d",&id);
					DepositInAccountClient(id,dep);
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
	if(flag == 0){
		printf("Incorrect ID or Password\n");
	}
}


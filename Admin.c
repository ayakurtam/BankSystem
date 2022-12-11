#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STD.h"
#include "Admin.h"
#include "Client.h"

 node *ptr;
 node *first = NULL;
 node *last = NULL;

u32 GlobalPW=2000;
u32 GlobalID=999999999;

//Admis user and pw
u16 AdminUser= 2000;
u16 AdminPW = 2022;



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
	u8 count = 0;
	do{
		count = 0;
	printf("Please Enter your Full Name (At least 1st four names): ");
	scanf(" %[^\n]",ptrNew->FullName);
	fflush(stdin);

	for(u32 i=0;i<strlen(ptrNew->FullName);i++)
	{
		if((ptrNew->FullName[i]==' ')&&((ptrNew->FullName[i+1]!=' ')&&(ptrNew->FullName[i+1]!='\0')))
		{
			count++;
		}
	}
	if(count>=3)
		break;
	}while(1);
	printf("Please Enter your Full Address: ");
	scanf(" %[^\n]",ptrNew->FullAddress);
	fflush(stdin);
	do{
	printf("Please Enter your National ID (at least 14 digits): ");
	scanf("%d",&ptrNew->NationalID);
	fflush(stdin);
	}while((ptrNew->NationalID)<9999999999999||(ptrNew->NationalID)>9999999999999);

	do{
	printf("Please Enter your Age: ");
	setbuf(stdout, NULL);
	scanf("%u",(u32*)&(ptrNew->Age));
	fflush(stdin);
	}while(!((ptrNew->Age>=5)&&(ptrNew->Age<=100)));

	if(ptrNew->Age<21)
	{
		printf("Please Enter your Guardian Name: ");
		scanf(" %[^\n]",ptrNew->GuardianName);
		fflush(stdin);
		do{
		printf("Please Enter your Guardian National ID (at least 14 digits): ");
		scanf("%d",&ptrNew->GuardianNationalID);
		fflush(stdin);
		}while((ptrNew->GuardianNationalID)<9999999999999||(ptrNew->GuardianNationalID)>9999999999999);

	}
	do{
	printf("Please Enter your Balance");
	setbuf(stdout, NULL);
	scanf("%ld",(u64 *)&(ptrNew->Balance));
	fflush(stdin);
	}while(ptrNew->Balance<=0);
	ptrNew->AccountStatus=1;
	u32 NewID,NewPW;
	NewID = GenerateID();
	ptrNew->BankAccountID = NewID;
	printf("Your ID is  %d\n",NewID);
	NewPW = GeneratePW();
	ptrNew->Password = NewPW;
	printf("Your Password is  %d\n",NewPW);
}

u32 GenerateID(){
	GlobalID++;
}

u32 GeneratePW(){
	GlobalPW++;
}

void OpenExistingAcc(void){
	u32 choice;
	printf("To make transaction press: 1 \n ");
	printf("To change status press: 2 \n ");
	printf("To withdraw press: 3 \n ");
	printf("To deposit  press: 4 \n ");
	printf("To return to main menu press: 5 \n ");
	fflush(stdin);
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
		{ u16 AccID1,AccID2,TransferAmout;
			printf("Please enter the account ID to transfer from");
			fflush(stdin);
			scanf("%d",&AccID1);
			printf("Please enter the account ID to transfer to");
			fflush(stdin);
			scanf("%d",&AccID2);
			printf("Please enter the amount to be transfered");
			fflush(stdin);
			scanf("%d",&TransferAmout);
		MakeTransactionAdmin(AccID1,AccID2,TransferAmout);
		}
		break;
		case 2:
		{
			u16 AccID;
			printf("Please enter the account ID to change the status");
			fflush(stdin);
			scanf("%d",&AccID);
			ChangeAccStatus(AccID);
		}
		break;
		case 3:
		{	u16 AccIDW,TransferAmout1;
			printf("Please enter the account ID to withdraw ");
			fflush(stdin);
			scanf("%d",&AccIDW);
			printf("Please enter the amount you want");
			fflush(stdin);
			scanf("%d",&TransferAmout1);
			WithdrawAdmin(AccIDW,TransferAmout1);
		}
		break;
		case 4:
		{
			u16 AccIDD,TransferAmout2;
			printf("Please enter the account ID to deposit cash ");
			fflush(stdin);
			scanf("%d",&AccIDD);
			printf("Please enter the amout you want to deposit");
			fflush(stdin);
			scanf("%d",&TransferAmout2);
			DepositInAccountAdmin(AccIDD,TransferAmout2);
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

void ChangeAccStatus(u16 BankAccountID){
	u16 choice;
	printf("Please enter the bank account statues 1 for active 2 for restricted 3 for closed ");
	fflush(stdin);
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

void AdminMode(u16 *ext){
	u16 user,Password,choice;
	printf("Please enter the user name of admin :");
	scanf("%d",&user);
	fflush(stdin);
	printf("Please enter the password for admin :");
	scanf("%d",&Password);
    fflush(stdin);
	if(user==AdminUser &&Password==AdminPW)
	{
		printf("Welcome admin\n");
		printf("Please select from the below menu\n");
		printf("1:Create new account\n");
		printf("2:Open existing account\n");
		printf("3:Exit system \n");
		fflush(stdin);
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
			printf("Wrong Choice\n");
			break;
		}
	}else{
		printf("Incorrect Username or Password for admin\n");
	}
}





/////////////////////////////////////////////
void DepositInAccountAdmin(u16 BankAccountID,u16 TransferAmoutRequiredToDeposit){

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

void WithdrawAdmin(u16 BankAccountID,u16 TransferAmoutRequired){
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

void MakeTransactionAdmin(u16 AccIDTrnsfrFrom,u16 AccIDTrnsfrTo,u16 TransferAmountOfCash){
	u16 flag1=0,flag2=0;
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


#include <stdio.h>
#include <stdlib.h>
#include "Admin.h"
#include "Client.h"
#include "STD.h"	


void main()
{
	u16 choice,Exit=0;
	CreateDummyAcc();
	while(1)
	{
		printf("Welcome to Bank account system\n");
		printf("To enter Admin mode press 1\nTo enter Client mode press 2\nYour choice is :");
		scanf("%d", &choice);
		fflush(stdin);
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
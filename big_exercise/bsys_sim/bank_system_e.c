/* Bank System */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue_queue.c"

/////////////////////////////////////////////////////////////////
SqQueue common, vip;

#define BSYS_MAX_USER_NUM     1000
//#define Line_Mode

static void printf_func(void)
{
	printf("1.vip user get number\n");
	printf("2.common user get number\n");
	printf("3.Back call number\n");
	printf("4.Exit\n");
	printf("Please Select[1-4]:");
}

static void empty_cache(void)
{
	char ch;

	while ((ch = getchar()) != '\n');
}

static int select_num(void)
{
	int num = 0;

	while (num < 1 || num > 4)
	{
		printf_func();
		if (0 == scanf("%d", &num)) 		
			empty_cache();
	}

	return num;
}

/***************************************************************
* Bank System Init
****************************************************************/
int Bank_Sys_Init(void)
{
	QueueCreate(&vip);
	QueueCreate(&common);

    return 0;
}

/***************************************************************
* Bank System Quit
****************************************************************/
int Bank_Sys_Term(void)
{
	QueueDestroy(&vip);
	QueueDestroy(&common);

    return 0;    
}

/***************************************************************
* Bank Get One ID
****************************************************************/
int Bank_Sys_Get_Id(int flag)
{
	static int vip_id = 0;
	static int common_id =0;

#ifdef Line_Mode 

	if (flag == 0 )
	{
		if (0 == QueueEnterC(&vip, vip_id))
		{
			vip_id++; 
			return vip_id;
		}
		else
			return -1;
	}
	else
	{
		if (0 == QueueEnterC(&common, common_id))
		{
			common_id++; 
			return common_id;
		}
		else
			return -1;
	}

#else
	
	if (flag == 0 )
	{
		if (0 == QueueEnterC(&vip, vip_id))
		{
			vip_id++; 
			return vip_id;
		}
		else
			return -1;
	}
	else
	{
		if (0 == QueueEnterC(&common, common_id))
		{
			common_id++; 
			return common_id;
		}
		else
			return -1;
	}

#endif	

}

/***************************************************************
* Bank Call One ID
****************************************************************/
int Bank_Sys_Call_Id(int *Vip)
{
	int id;

#ifdef Line_Mode

	if (-1 != QueueDeleteC(&vip, &id))
		*Vip = 1;
	else
		if (-1 != QueueDeleteC(&common, &id))
			*Vip = 0;
    	else
			return -1;

#else
	
	if (-1 != QueueDeleteC(&vip, &id))
		*Vip = 1;
	else
		if (-1 != QueueDeleteC(&common, &id))
			*Vip = 0;
    	else
			return -1;

#endif
	
	return id;
}

/***************************************************************
* Bank Get All Users Number
****************************************************************/
unsigned int Bank_Get_User_Num(int flag)
{
	unsigned int num;

	if (flag == 0)
		num = QueueGetTag(&vip);
	else
		num = QueueGetTag(&vip) + QueueGetTag(&common);
	
	return num;
}


/***************************************************************
* main
****************************************************************/
int main(int argc, char**argv)
{
	int id, Vip;
	unsigned int num;
    
	Bank_Sys_Init();

	while (1)
	{
		switch (select_num())
		{
			case 1:
				id = Bank_Sys_Get_Id(0);
				num = Bank_Get_User_Num(0);
				if (id == -1)
					printf("the number is too large, you have to wait several minutes !\n");
				else
				{
					printf("you get the vip %d\n", id);
					printf("there are %d people in front of you\n", num-1);
				}

				break;
			case 2:
				id = Bank_Sys_Get_Id(1);
				num = Bank_Get_User_Num(1);
				if (id == -1)
					printf("the number is too large, you have to wait several minutes !\n");
				else
				{
					printf("you get the common %d\n", id);
					printf("there are %d people in front of you\n", num-1);					
				}

				break;
			case 3:
				id = Bank_Sys_Call_Id(&Vip);
				num = Bank_Get_User_Num(1);
				if (id == -1)
					printf("there are no people in wait\n");
				else
				{
					printf("you should call %s %d\n", (Vip ? "vip": "common"), id+1);
					printf("there are %d people are in wait\n", num + 1);
				}

				break;
			case 4:
				Bank_Sys_Term();

				return 0;	
		}
	}
	
    return 0;

}









#if 0

/***************************************************************
* main
****************************************************************/
int main(int argc, char**argv)
{
    char virtkey = 0;
    
	Bank_Sys_Init();


	      	
	  for(;;)
	  {
        scanf("%c", &virtkey); 
        
        switch(virtkey)
        {
        	   case 'g':
        	     break;
        	     
        	   case 'c':
        	     break;
        	     
        	   case 'u':
        	     break;
        	     
        	   case 'e':
	                goto BSYSEXIT;
        	     break;        	     
        	   
        	   default:     	   	   
        	   	   if(virtkey != 10) // "ENTER" Key Code (10)
        	   	   {
        	           printf("Error Enter Key!! \n");
        	       }
        	     break;
        }
	  }
	  
BSYSEXIT:
	  Bank_Sys_Term();


	  
    return 0;
}

#endif

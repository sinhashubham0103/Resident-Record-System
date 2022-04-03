#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 500
#define SUCCESS 1
#define FAILURE 0
#define ACCOMODATED 1
#define UNACCOMODATED 0

int status_code;

struct idnumber
{ 
char aadhaar[15]; 
char passport[15]; 
char empcode[15];
};

struct accomodation
{ 
char firstname[50]; 
char lastname[50]; 
char accomodation_type[20];
int idtype; 
struct idnumber idnum;	
char address[100]; 
};

struct block
{
	int type1[10];
	int type2[10];
	int type3[10];
	int type4[10];
};
 
int InsertRecord(struct accomodation B[],int n);
void Initialize(struct accomodation B[],int n);
void printRecords(struct accomodation B[],int n);
int removeDuplicates(struct accomodation B[],int n);
int updateRecord(struct accomodation B[],int n,int a[]); 
void Sorting(struct accomodation B[],int n,int a[]);
void Search(struct accomodation B[],int n,int a[]);
void deleteRecord(struct accomodation B[],int n,int a[]);
void printSortedRecords(struct accomodation B[],int n,int a[]);
int specialRequestAllocation(struct accomodation B[],int n,int a[],struct block acc_type);

int main()
{
	struct accomodation B[SIZE];
	struct block acc_type;
	int index[SIZE];
	int choice=1,cont=1,i;
	Initialize(B,SIZE);
	for(i=0;i<SIZE;i++)
	{
		index[i]=i;
	}
	for(i=0;i<10;i++)
	{
		acc_type.type1[i]=UNACCOMODATED;
		acc_type.type2[i]=UNACCOMODATED;
		acc_type.type3[i]=UNACCOMODATED;
		acc_type.type4[i]=UNACCOMODATED;
	}
	while(cont)
	{
		printf("\n#1 - Insert new data\n#2 - Reset Data\n#3 - Print Records\n#4 - Print Sorted Records\n#5 - Search by name\n#6 - Delete data\n#7 - Update Record\n#8 - Remove Duplicate elements\n#9 - Special Request block allocation\n#0 - Quit");
 		printf("\nEnter your choice :");
 		fflush(stdin);
		scanf("%d",&choice);
		switch(choice)
	 	{
			case 1: 
			{
				status_code=InsertRecord(B,SIZE);
				if(!status_code)
				{
					printf("Oops!!!\nCouldn't add the new record");
				}
				Sorting(B,SIZE,index);
				break;
			}
			case 2:
			{
				int reset;
				printf("This will erase all the records data.\nPress 1 to continue. Else press 0.");
				scanf("%d",&reset);
				if(reset)
				{
					Initialize(B,SIZE);
				}
				break;
			}
			case 3:
			{
				printRecords(B,SIZE);
				break;
			}
			case 4:
			{
				printSortedRecords(B,SIZE,index);
				break;
			}
			case 5:
			{
				Search(B,SIZE,index);
				break;
			}
			case 6:
				{
					deleteRecord(B,SIZE,index);
					break;
				}
			case 7:
			{
				status_code=updateRecord(B,SIZE,index);
				if(status_code)
				{
					printf("The data was successfully updated");
				}
				else
				{
					printf("Sorry, the data couldn't be updated");
				}
				break;
			}
			case 8:
			{
				status_code=removeDuplicates(B,SIZE);
				if(status_code)
				{
					printf("Duplicate elements were successfully removed\n.");
				}
				break;
			}
			case 9:
			{
				status_code=specialRequestAllocation(B,SIZE,index,acc_type);
				if(status_code)
				{
					printf("The block is successfully allocated.");
				}
				else
				{
					printf("The block cannot be allocated.");
				}
				break;
			}
			default:
			{
				int quit;
				printf("Do you really want to quit?\nPress 1 to continue.Else press 0.");
				scanf("%d",&quit);
				if(quit)
				{
					cont=0;
				}
				else
				{
					cont=1;
				}
				break;
			}
		}
	}
	return 0;
}

void Initialize(struct accomodation B[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		B[i].firstname[0]='\0';
		B[i].lastname[0]='\0';
		B[i].accomodation_type[0]='\0';
		B[i].idtype=-1;
		B[i].idnum.aadhaar[0]='\0';
		B[i].idnum.passport[0]='\0';
		B[i].idnum.empcode[0]='\0';
		B[i].address[0]='\0';
	}
}

int InsertRecord(struct accomodation B[],int n)
{
	status_code=SUCCESS;
	char firstname[50],lastname[50],accomodation_type[20],aadhaar[15],passport[15],empcode[15],address[100];
	int idtype;
	aadhaar[0]='\0';
	passport[0]='\0';
	empcode[0]='\0';
	int i,j,found,isFreeLoc,correct_id=0;
	printf("\nEnter the first name :");
	scanf("%s",firstname);
	printf("Enter the last name :");
	scanf("%s",lastname);
	printf("Enter the accomodation type :");
	scanf("%s",accomodation_type);
	while(!correct_id)
	{
		printf("Enter the id type.\nEnter 0 for aadhaar, 1 for passport and 2 for employee code :");
		scanf("%d",&idtype);
		if(idtype==0)
		{
			printf("Enter aadhar number :");
			scanf("%s",aadhaar);
			correct_id=1;
		}
		else if(idtype==1)
		{
			printf("Enter passport number :");
			scanf("%s",passport);
			correct_id=1;
		}
		else if (idtype==2)
		{
			printf("Enter employee code :");
			scanf("%s",empcode);
			correct_id=1;
		}
		else
		{
			printf("You have entered an invalid id type.");
			correct_id=0;
		}
	}
	printf("Enter the address :");
	fflush(stdin);
	fgets(address,100,stdin);
	i=0;
	found=0;
	while(i<n && !found)
	{
		if((B[i].idtype==idtype) && (strcmp(B[i].idnum.aadhaar,aadhaar)==0) && (strcmp(B[i].idnum.passport,passport)==0) && (strcmp(B[i].idnum.empcode,empcode)==0))
		{
			found=1;
		}
		else
		{
			i++;
		}
	}
	if(found)
	{
		strcpy(B[i].firstname,firstname);
		strcpy(B[i].lastname,lastname);
		strcpy(B[i].accomodation_type,accomodation_type);
		strcpy(B[i].address,address);
	}
	else
	{
		isFreeLoc=0;
		j=0;
		while(j<n && !isFreeLoc)
		{
			if(B[j].idtype==-1)
			{
				isFreeLoc=1;
			}
			else
			{
				j++;
			}
		}
		if(isFreeLoc)
		{
			strcpy(B[j].firstname,firstname);
			strcpy(B[j].lastname,lastname);
			strcpy(B[j].accomodation_type,accomodation_type);
			B[j].idtype=idtype;
			strcpy(B[j].idnum.aadhaar,aadhaar);
			strcpy(B[j].idnum.passport,passport);
			strcpy(B[j].idnum.empcode,empcode);
			strcpy(B[j].address,address);
		}
		else
		{
			status_code=FAILURE;
		}
	}
	return status_code;
}

void printRecords(struct accomodation B[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(B[i].idnum.passport[0]!='\0')
		{
			printf("%s %s\n%s\n%d\t%s\n%s\n\n",B[i].firstname,B[i].lastname,B[i].accomodation_type,B[i].idtype,B[i].idnum.passport,B[i].address);
		}
	}
	for(i=0;i<n;i++)
	{
		if(B[i].idnum.aadhaar[0]!='\0')
		{
			printf("%s %s\n%s\n%d\t%s\n%s\n\n",B[i].firstname,B[i].lastname,B[i].accomodation_type,B[i].idtype,B[i].idnum.aadhaar,B[i].address);
		}
	}
	for(i=0;i<n;i++)
	{
		if(B[i].idnum.empcode[0]!='\0')
		{
			printf("%s %s\n%s\n%d\t%s\n%s\n\n",B[i].firstname,B[i].lastname,B[i].accomodation_type,B[i].idtype,B[i].idnum.empcode,B[i].address);
		}
	}
}


void Sorting(struct accomodation B[],int n,int a[])
{
	int i,j,temp,sorted;
	sorted=0;
	
	for(i=0;(i<n-1) && !sorted;i++)
	{
		sorted=1;
		for(j=0;j<(n-1-i);j++)
		{
			if(B[a[j+1]].idtype!=-1)
			{
				if(B[a[j]].idtype==-1)
				{
					temp=a[j];
					a[j]=a[j+1];
					a[j+1]=temp;
					
					sorted=0;
				}
				else
				{
					if(strcmp(B[a[j]].firstname,B[a[j+1]].firstname)>0)
					{
						temp=a[j];
						a[j]=a[j+1];
						a[j+1]=temp;
						
						sorted=0;
					}
					else if(strcmp(B[a[j]].firstname,B[a[j+1]].firstname)==0)
					{
						if(strcmp(B[a[j]].lastname,B[a[j+1]].lastname)>0)
						{
							temp=a[j];
							a[j]=a[j+1];
							a[j+1]=temp;
							
							sorted=0;
						}
					}
				}
			}
		}
	}
}

void printSortedRecords(struct accomodation B[],int n,int a[])
{
	int i;
	for(i=0;(i<n) && (B[a[i]].idtype!=-1);i++)
	{
		printf("%s %s\n%s\n%d ",B[a[i]].firstname,B[a[i]].lastname,B[a[i]].accomodation_type,B[a[i]].idtype);
		if(B[a[i]].idtype==0)
		{
			printf("%s",B[a[i]].idnum.aadhaar);
		}
		else if(B[a[i]].idtype==1)
		{
			printf("%s",B[a[i]].idnum.passport);
		}
		else
		{
			printf("%s",B[a[i]].idnum.empcode);
		}
		printf("\n%s\n",B[a[i]].address);
	}
}

void Search(struct accomodation B[],int n,int a[])
{
	int i,found;
	char firstname[50],lastname[50];
	found=0;
	printf("\nEnter the firstname :");
	scanf("%s",firstname);
	printf("Enter the lastname :");
	scanf("%s",lastname);
	i=0;
	while((B[a[i]].idtype!=-1) && !found)
	{
		if((strcmp(B[a[i]].firstname,firstname)==0) && (strcmp(B[a[i]].lastname,lastname)==0))
		{
			found=1;
		}
		else
		{
			i++;
		}
	}
	if(found)
	{
		printf("\n%s\n%d ",B[a[i]].accomodation_type,B[a[i]].idtype);
		if(B[a[i]].idtype==0)
		{
			printf("%s",B[a[i]].idnum.aadhaar);
		}
		else if(B[a[i]].idtype==1)
		{
			printf("%s",B[a[i]].idnum.passport);
		}
		else
		{
			printf("%s",B[a[i]].idnum.empcode);
		}
		printf("\n%s\n",B[a[i]].address);
	}
	else
	{
		printf("The name couldn't be found.");
	}
}

void deleteRecord(struct accomodation B[],int n,int a[])
{
	int i,j,idtype,found;
	char aadhaar[15],passport[15],empcode[15];
	aadhaar[0]='\0';
	passport[0]='\0';
	empcode[0]='\0';
	printf("\nEnter the id type.\nEnter 0 for aadhaar, 1 for passport and 2 for employee code:");
	scanf("%d",&idtype);
	if(idtype==0)
	{
		printf("Enter aadhaar number :");
		scanf("%s",aadhaar);
	}
	else if(idtype==1)
	{
		printf("Enter passport number :");
		scanf("%s",passport);
	}
	else if(idtype==2)
	{
		printf("Enter employee code :");
		scanf("%s",empcode);
	}
	i=0;
	found=0;
	while((B[a[i]].idtype!=-1) && !found)
	{
		if((B[a[i]].idtype==idtype) && (strcmp(B[a[i]].idnum.aadhaar,aadhaar)==0) && (strcmp(B[a[i]].idnum.passport,passport)==0) && (strcmp(B[a[i]].idnum.empcode,empcode)==0))
		{
			found=1;
		}
		else
		{
			i++;
		}
	}
	if(found)
	{
		strcpy(B[a[i]].firstname,"");
		strcpy(B[a[i]].lastname,"");
		strcpy(B[a[i]].accomodation_type,"");
		B[a[i]].idtype=-1;
		strcpy(B[a[i]].idnum.aadhaar,"");
		strcpy(B[a[i]].idnum.passport,"");
		strcpy(B[a[i]].idnum.empcode,"");
		strcpy(B[a[i]].address,"");
		
		j=i;
		a[n-1]=a[i];
		while(j<n-1)
		{
			a[j]=a[j+1];
			j++;
		}
		printf("The data has been successfully deleted");
	}
	else
	{
		printf("The data couldn't be found");
	}
}

int updateRecord(struct accomodation B[],int n,int a[])
{
	status_code=SUCCESS;
	int i,j,idtype,found,choice;
	char firstname[50],lastname[50],accomodation_type[20],address[100];
	char aadhaar[15],passport[15],empcode[15];
	aadhaar[0]='\0';
	passport[0]='\0';
	empcode[0]='\0';
	printf("\nEnter the id type.\nEnter 0 for aadhaar, 1 for passport and 2 for employee code:");
	scanf("%d",&idtype);
	if(idtype==0)
	{
		printf("Enter aadhaar number :");
		scanf("%s",aadhaar);
	}
	else if(idtype==1)
	{
		printf("Enter passport number :");
		scanf("%s",passport);
	}
	else if(idtype==2)
	{
		printf("Enter employee code :");
		scanf("%s",empcode);
	}
	i=0;
	found=0;
	while((B[a[i]].idtype!=-1) && !found)
	{
		if((B[a[i]].idtype==idtype) && (strcmp(B[a[i]].idnum.aadhaar,aadhaar)==0) && (strcmp(B[a[i]].idnum.passport,passport)==0) && (strcmp(B[a[i]].idnum.empcode,empcode)==0))
		{
			found=1;
		}
		else
		{
			i++;
		}
	}
	if(found)
	{
		printf("Enter the option you want to update :");
		printf("\n#1 - Firstname\n#2 - Lastname\n#3 - Accomodation type\n#4 - Id number\n#5 - Address");
		printf("\nEnter your choice :");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			{
				printf("\nEnter the first name :");
				scanf("%s",firstname);
				strcpy(B[a[i]].firstname,firstname);
				Sorting(B,n,a);
				break;
			}
			case 2:
			{
				printf("\nEnter the last name :");
				scanf("%s",lastname);
				strcpy(B[a[i]].lastname,lastname);
				Sorting(B,n,a);
				break;
			}
			case 3:
			{
				printf("\nEnter the accomodation type :");
				scanf("%s",accomodation_type);
				strcpy(B[a[i]].accomodation_type,accomodation_type);
				break;
			}
			case 4:
			{
				printf("\nEnter the id type.\nEnter 0 for aadhaar, 1 for passport and 2 for employee code.");
				scanf("%d",&idtype);
				if(idtype==0)
				{
					printf("Enter aadhaar number :");
					scanf("%s",aadhaar);
					B[a[i]].idtype=idtype;
					strcpy(B[a[i]].idnum.aadhaar,aadhaar);
					strcpy(B[a[i]].idnum.passport,"");
					strcpy(B[a[i]].idnum.empcode,"");
				}
				else if(idtype==1)
				{
					printf("Enter passport number :");
					scanf("%s",passport);
					B[a[i]].idtype=idtype;
					strcpy(B[a[i]].idnum.passport,passport);
					strcpy(B[a[i]].idnum.aadhaar,"");
					strcpy(B[a[i]].idnum.empcode,"");
				}
				else if (idtype==2)
				{
					printf("Enter employee code :");
					scanf("%s",empcode);
					B[a[i]].idtype=idtype;
					strcpy(B[a[i]].idnum.empcode,empcode);
					strcpy(B[a[i]].idnum.aadhaar,"");
					strcpy(B[a[i]].idnum.passport,"");
				}
				else
				{
					printf("You have entered a wrong id type");
					status_code=FAILURE;
				}
				break;
			}
			case 5:
			{
				printf("\nEnter address");
				scanf("%s",address);
				strcpy(B[a[i]].address,address);
				break;
			}
		}
	}
	else
	{
		printf("The data was not found.");
		status_code=FAILURE;
	}
	return status_code;	
}


int removeDuplicates(struct accomodation B[],int n)
{
	status_code=SUCCESS;
	int i,j;
	for(i=0;(i<n-1) && (B[i].idtype!=-1);i++)
	{
		for(j=i+1;(j<n) && (B[j].idtype!=-1);j++)
		{
			if((strcmp(B[i].firstname,B[j].firstname)==0) && (strcmp(B[i].lastname,B[j].lastname)==0))
			{
				strcpy(B[j].firstname,"");
				strcpy(B[j].lastname,"");
				strcpy(B[j].accomodation_type,"");
				B[j].idtype=-1;
				strcpy(B[j].idnum.aadhaar,"");
				strcpy(B[j].idnum.passport,"");
				strcpy(B[j].idnum.empcode,"");
				strcpy(B[j].address,"");
			}
		}
	}
	return status_code;
}

int specialRequestAllocation(struct accomodation B[],int n,int a[],struct block acc_type)
{
	status_code=SUCCESS;
	int i,j,idtype,found,type,alloc;
	char aadhaar[15],passport[15],empcode[15];
	aadhaar[0]='\0';
	passport[0]='\0';
	empcode[0]='\0';
	printf("\nEnter the id type.\nEnter 0 for aadhaar, 1 for passport and 2 for employee code:");
	scanf("%d",&idtype);
	if(idtype==0)
	{
		printf("Enter aadhaar number :");
		scanf("%s",aadhaar);
	}
	else if(idtype==1)
	{
		printf("Enter passport number :");
		scanf("%s",passport);
	}
	else if(idtype==2)
	{
		printf("Enter employee code :");
		scanf("%s",empcode);
	}
	i=0;
	found=0;
	while((B[a[i]].idtype!=-1) && !found)
	{
		if((B[a[i]].idtype==idtype) && (strcmp(B[a[i]].idnum.aadhaar,aadhaar)==0) && (strcmp(B[a[i]].idnum.passport,passport)==0) && (strcmp(B[a[i]].idnum.empcode,empcode)==0))
		{
			found=1;
		}
		else
		{
			i++;
		}
	}
	if(found)
	{
		printf("Enter the block type.\nEnter 1 for type1, 2 for type2, 3 for type3 and 4 for type4 :");
		scanf("%d",&type);
		alloc=0;
		j=0;
		while((j<10) && !alloc)
		{
			if(type==1)
			{
				if(acc_type.type1[j]==UNACCOMODATED)
				{
					acc_type.type1[j]==ACCOMODATED;
					alloc=1;
					strcpy(B[a[i]].accomodation_type,"type-I");
				}
			}
			else if(type==2)
			{
				if(acc_type.type2[j]==UNACCOMODATED)
				{
					acc_type.type2[j]==ACCOMODATED;
					alloc=1;
					strcpy(B[a[i]].accomodation_type,"type-II");
				}
			}
			else if(type==3)
			{
				if(acc_type.type3[j]==UNACCOMODATED)
				{
					acc_type.type3[j]==ACCOMODATED;
					alloc=1;
					strcpy(B[a[i]].accomodation_type,"type-III");
				}
			}
			else if(type==4)
			{
				if(acc_type.type4[j]==UNACCOMODATED)
				{
					acc_type.type4[j]==ACCOMODATED;
					alloc=1;
					strcpy(B[a[i]].accomodation_type,"type-IV");
				}
			}
		}
		if(!alloc)
		{
			status_code=FAILURE;
		}
	}
	else
	{
		printf("The data was not found.");
		status_code=FAILURE;
	}
	return status_code;
}


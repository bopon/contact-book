// creating phone-book application
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

//declearing structure
struct phone_book{
	char first_name[15];
	char last_name[15];
	int contact_number;
}contact[100];

//declearing function part
int add_contact();
int view_contact();
int edit_contact(struct phone_book a[]);
int delete_contact(struct phone_book a[]);

int search(struct phone_book a[]);
int count(int a);
int standby();

//declearing global variable
char first_name[15],last_name[15];
int number;

//declearing file pointer as a global pointer
FILE *fp;

//starting of main function
int main(){
	system("cls");
	int ch;
	
	//checking weather there is file or not if not then it will create file
	fp=fopen("contacts.csv","a");
	fclose(fp);
	
	//main menu with fail safe loop
	printf("\n-----------[Main Menu]------------");
	while(1){
		printf("\nPress [1] to Add contact. \nPress [2] to View contacts. \nPress [3] to Edit contact. \nPress [4] to Delete contact. \nPress [5] to Exit. ");
		printf("\n==================================");
		printf("\nEnter your input here: ");
		scanf(" %d",&ch);
		
		switch (ch){
			case 1:
				add_contact();
				break;//for breaking switch case
			case 2:
				view_contact();
				break;//for breaking switch case
			case 3:
				edit_contact(contact);
				break;//for breaking switch case
			case 4:
				delete_contact(contact);
				break;//for breaking switch case
			case 5:
				exit(0);
				break;//for breaking switch case
			default:
				printf("\nERROR Invalid input!!! \n");
				continue;//redirecting the flow towards nearest infinity while loop
		}
		break;//for breaking while loop
	}
	
return 0;
}

//starting of add contact function
int add_contact(){
	
    system("cls");
    
	//declearing
	int check;
	char ch='y';    
    
	//opening file as append+
	fp=fopen("contacts.csv","a+");
    printf("----------[Add Contacts]----------");
    while((ch=='y')||(ch=='Y')){
    	printf("\n==================================");
		printf("\nEnter Name (with last name): ");
		scanf(" %s",&first_name);
		scanf(" %s",&last_name);
    	printf("Enter contact number: 9");
    	
		while(1){
    		scanf(" %d",&number);
    		//calling count function
    		check=count(number);
    		
			if(check==9){
				break;//for breaking infinity while loop
			}else{
				printf("\n<<-------Invalid Phone Number!!!-------->>");
				printf("\nPlease Re-enter Remaining 9 digit Number after: 9");// here 9 is already written because all 10 letter are not supported by data type
				continue;//redirecting the flow towards nearest infinity while loop
			}
		}
		//changing both first name and last name into lower case
		strlwr(first_name);
		strlwr(last_name);
		//storing in a file using fprintf function
    	fprintf(fp,"%s %s , 9%d \n",first_name,last_name,number);
		printf("-------------------------------------");
	    printf("\nDO YOU WANT TO ADD MORE CONTACTS(y/n):");
    	scanf(" %c",&ch);
    	printf("-------------------------------------");
    }
    fclose(fp);
    //calling standby function
    standby();
return 0;
}

//starting view_contact function
int view_contact(){
	system("cls");
	
	//declearing
	char ch;
		
	//opening file in read mode
	fp=fopen("contacts.csv","r");
	//resetting the cursor to using rewind(fp);
	rewind(fp);
	printf("----------[View Contacts]----------");
	printf("\nPress [s] to search contacts and anything else to Cancel.");
	printf("\n=====================================");
	while(fscanf(fp,"%s %s , 9%d",&first_name,&last_name,&number)>0){
	printf("\nContact Name: %s %s \nContact Number: 9%d \n",first_name,last_name,number);
	}
	printf("\n=====================================");
	fclose(fp);
	printf("\nPress [s] to search contacts and anything else to cancel: ");
	scanf(" %c",&ch);
	printf("=====================================");
	if((ch=='s')||(ch=='S')){
		search(contact); //calling search function
	}
	
	//calling standby function
	standby();
return 0;
}

//starting edit_contact function[longest function in this progarm
int edit_contact(struct phone_book contact[]){
	system("cls");
	
	//declearing
	int i=0,j=0,k=0,found=0,inp,temp,check;
	int total,pos;
	
	//taking input
	printf("\n==================================");
	printf("\nEnter name you want to edit(with last name): ");
	scanf(" %s",&first_name);
	scanf(" %s",&last_name);
	printf("-------------------------------------");
	printf("\n-------[Searching %s %s]-------",first_name,last_name);
	printf("\n-------------------------------------");
	//changing both first name and last name into lower case
	strlwr(first_name);
	strlwr(last_name);
	//opening data file in append+ mode
	fp=fopen("contacts.csv","a+");
	//reseting the cursor to using rewind(fp);
	rewind(fp);
	//loading in structure from file
	//*here i will count the total no of contacts.
	while(fscanf(fp,"%s %s , 9%d",&contact[i].first_name,&contact[i].last_name,&contact[i].contact_number)>0){
		i++;
	}
	total=i;
	fclose(fp);
	
	//* j will store the position of the name in structure.
	for(j=0;j!=total;j++){
		//checking whether user inputed name is in the file or not
		if((strcmp(contact[j].first_name,first_name)==0)&&(strcmp(contact[j].last_name,last_name)==0)){
			printf("\n=======***Found***========");
			printf("\nContact Name: %s %s \nContact Number: 9%d",contact[j].first_name,contact[j].last_name,contact[j].contact_number);
			printf("\n==========================");
			found=1;
			break;//for breaking for loop
		}
	}
	pos=j;
	
	if(found==1){
		while(1){
			printf("\nWhat do you want to edit: \n[1]Name \n[2]Contact Number \n[3]Both \n[4]Cancel ");
			printf("\n-------------------------------------");
			printf("\nEnter you input here: ");
			scanf(" %d",&inp);
			printf("---------------------------------------");
		
			switch (inp){
				case 1:
					//**replacing in structure
					printf("\nEnter Name(with last name): ");
					scanf(" %s",contact[pos].first_name);
					scanf(" %s",contact[pos].last_name);
					//changing both first name and last name into lowercase
					strlwr(contact[pos].first_name);
					strlwr(contact[pos].last_name);
					break;//for breaking switch case
				case 2:
					printf("\nEnter Contact Number: 9");// here 9 is already written because all 10 letter are not supported by data type
					while(1){
	    				scanf(" %d",&temp);
	    				check=count(temp);
						if(check==9){
							//**replacing in structure
							contact[pos].contact_number=temp;
							break;//for breaking while loop
						}else{
							printf("\n<<-------Invalid Phone Number!!!-------->>");
							printf("\nPlease Re-enter Remaining 9 digit Number after: 9");// here 9 is already written because all 10 letter are not supported by data type
							continue;//redirecting the flow towards nearest infinity while loop
						}
					}
					break;//for breaking switch case
			 	case 3:
				 	printf("\nEnter Name(with last name): ");
					scanf(" %s",contact[pos].first_name);
					scanf(" %s",contact[pos].last_name);
					//changing both first name and last name into lowercase
					strlwr(contact[pos].first_name);
					strlwr(contact[pos].last_name);
					printf("Enter Contact Number: 9");// here 9 is already written because all 10 letter are not supported by data type
					while(1){
		    			scanf(" %d",&temp);
		    			//calling count function
		    			check=count(temp);
						if(check==9){
							//**replacing in structure
							contact[pos].contact_number=temp;
							break;//for breaking while loop
						}else{
							printf("\n<<-------Invalid Phone Number!!!-------->>");
							printf("\nPlease Re-enter Remaining 9 digit Number after: 9");// here 9 is already written because all 10 letter are not supported by data type
							continue;//redirecting the flow towards nearest infinity while loop
						}
					}
					break;//for breaking switch case
				case 4:
					break;//for breaking switch case
				default:
						printf("\nERROR Invalid input!!! \n");
						continue;//redirecting the flow towards top infinity while loop
				}
			break;//for breaking while loop
			}
		printf("\n==========================");
		printf("\nContact Name: %s %s \nContact Number: 9%d",contact[pos].first_name,contact[pos].last_name,contact[pos].contact_number);
		printf("\n==========================");
		
		//**finally replacing in data file
		fp=fopen("contacts.csv","w");
		for(k=0;k!=total;k++){
			fprintf(fp,"%s %s , 9%d \n",contact[k].first_name,contact[k].last_name,contact[k].contact_number);
		}
		fclose(fp);
	}else{
		printf("\n======***Not Found***=========");
			printf("\nSORRY Contact Name: %s %s \nNOT FOUND!!! ",first_name,last_name);
			printf("\n============================");
	}
	//calling standby function
	standby();
return 0;
}

//starting delete_contact function
int delete_contact(struct phone_book contact[]){
	system("cls");
	
	//Declearing
	int i=0,j=0,k=0,found=0;
	int total,pos;
	char ch;
	
	//taking input
	printf("\n==================================");
	printf("\nEnter name you want to delete(with last name): ");
	scanf(" %s",&first_name);
	scanf(" %s",&last_name);
	//changing both first name and last name into lowercase
	strlwr(first_name);
	strlwr(last_name);
	printf("-------------------------------------");
	printf("\n-------[Searching %s %s]-------",first_name,last_name);
	printf("\n-------------------------------------");
	
	//opening data file in append+ mode
	fp=fopen("contacts.csv","a+");
	//reseting the cursor to using rewind(fp);
	rewind(fp);
	//loading in structure from file
	//*here i will count the total no of contacts.
	while(fscanf(fp,"%s %s , 9%d",&contact[i].first_name,&contact[i].last_name,&contact[i].contact_number)>0){
		i++;
	}
	total=i;
	fclose(fp);
	
	//*here value of i is taken from above.
	//* And j will store the exact location of the name in structure.
	for(j=0;j!=i;j++){
		//checking whether user inputed name is in the file or not  
		if((strcmp(contact[j].first_name,first_name)==0)&&(strcmp(contact[j].last_name,last_name)==0)){
			printf("\n=======***Found***========");
			printf("\nContact Name: %s %s \nContact Number: 9%d",contact[j].first_name,contact[j].last_name,contact[j].contact_number);
			printf("\n==========================");
			found=1;
			break;//for breaking for loop
		}
	}
	pos=j;
	
	if(found==1){
		printf("\nAre you sure want to delete this contact(y/n): ");
		scanf(" %c",&ch);
		printf("-------------------------------------");
		if(ch=='y'||ch=='Y'){
			for(k=pos;k!=total-1;k++){
				strcpy(contact[k].first_name,contact[k+1].first_name);
				strcpy(contact[k].last_name,contact[k+1].last_name);
				contact[k].contact_number=contact[k+1].contact_number;
			}
			printf("\n=================================");
			printf("\n***Contact Deleted successfully***");
			printf("\n=================================");
		}
		//**finally replacing in data file
		fp=fopen("contacts.csv","w");
		for(k=0;k!=total-1;k++){
			fprintf(fp,"%s %s , 9%d \n",contact[k].first_name,contact[k].last_name,contact[k].contact_number);
		}
		fclose(fp);
		
	}else{
		printf("\n======***Not Found***=========");
		printf("\nSORRY Contact Name: %s %s \nNOT FOUND!!! ",first_name,last_name);
		printf("\n============================");
	}
	
	//calling standby fulction
	standby();
	
return 0;	
}

//these are helping function------>>>\\

//starting search function.
int search(struct phone_book contact[]){

	//declearing
	int i,total,j,found=0;
	
	//taking input
	printf("\n==================================");
	printf("\nEnter name to search(First Name only): ");
	scanf(" %s",&first_name);
	strlwr(first_name);
	printf("-------------------------------------");
	printf("\n-------[Searching for %s]-------",first_name);
	printf("\n-------------------------------------");
	
	//opening data file in append+ mode
	fp=fopen("contacts.csv","a+");
	//reseting the cursor to using rewind(fp);
	rewind(fp);
	//loading in structure from file
	//*here i will count the total no of contacts.
	while(fscanf(fp,"%s %s , 9%d",&contact[i].first_name,&contact[i].last_name,&contact[i].contact_number)>0){
		i++;
	}
	total=i;
	fclose(fp);
	
	printf("\n=======*** Contact Found ***========");
	for(j=0;j!=i;j++){
		//checking whether user inputed name is in the file or not  
		if((strcmp(contact[j].first_name,first_name)==0)){	
			printf("\nContact Name: %s %s \nContact Number: 9%d",contact[j].first_name,contact[j].last_name,contact[j].contact_number);
			printf("\n");
			found=found+1;
		}
	}
	printf("\n %d Contact Found",found);
	printf("\n===================================");
return 0;	
}

//starting count function.
int count(int a){
	int c=0;
	while(a!=0){
    	c=c+1;
		a=a/10;	
    }
    return c;
}

//starting standby function.
int standby(){
	int input;
	printf("\n[1]Go to Main Menu \t [2]EXIT");
	printf("\nEnter your input here: ");
	while(1){
		scanf(" %d",&input);
		switch (input){
			case 1:
				main();
				break;//breaking switch case
			case 2:
				exit(0);
			default:
				printf("\nERROR Invalid input!!! \n");
						continue;//redirecting the flow towards nearest infinity while loop
		}
		break;//for breaking while loop
	}
return 0;
}

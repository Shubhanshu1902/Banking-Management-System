#include "client.h"

void chooseOption(int sd){
	while(1){
		write(1,"1 : Normal User Login\n",sizeof("1 : Normal User Login\n"));
		write(1,"2 : Joint Account-User Login\n",sizeof("2 : Joint Account User Login\n"));
		write(1,"3 : Admin Login\n",sizeof("3 : Admin Login\n"));
		
		write(1,"Your choice : ",sizeof("Your choice : "));
		scanf("%d",&choice);

		if(choice == 1){
			normalUserLogin(sd); 
			break;
		}
		else if(choice == 2){
			jointUserLogin(sd);
			break;
		}
		else if(choice == 3){
			adminLogin(sd);
			break;
		}
		else write(1,"Invalid selection!!\n\n",sizeof("Invalid selection!!\n\n"));
	}
	return;
}

void menu(int sd){
	int ch;
	if(choice==1 || choice==2){
		write(1,"1 : Deposit\n",sizeof("1 : Deposit\n"));
		write(1,"2 : Withdraw\n",sizeof("2 : Withdraw\n"));
		write(1,"3 : Balance Enquiry\n",sizeof("3 : Balance Enquiry\n"));
		write(1,"4 : Password Change\n",sizeof("4 : Password Change\n"));
		write(1,"5 : View Details\n",sizeof("5 : View Details\n"));
		write(1,"6 : Exit\n",sizeof("6 : Exit\n"));
	
		write(1,"Your choice : ",sizeof("Your choice : "));
		scanf("%d",&ch);
		
        switch(ch){
		case 1 :
			deposit(sd);
			break;
		case 2 :
			withdraw(sd);
			break;
		case 3 :
			balanceEnquiry(sd);
			break;
		case 4 :
			changePassword(sd);
			break;
		case 5 :
			viewDetails(sd);
			break;
		case 6 :
			write(sd,&ch,sizeof(int));
			write(1,"Thank you\n",sizeof("Thank you\n"));
			exit(0);
		default :
			write(1,"Invalid selection!!\n\n",sizeof("Invalid selection!!\n\n"));
			menu(sd);
			break;
		}
	}
	else if(choice==3){
		write(1,"1 : Add Account\n",sizeof("1 : Add Account\n"));
		write(1,"2 : Delete Account\n",sizeof("2 : Delete Account\n"));
		write(1,"3 : Modify Account\n",sizeof("3 : Modify Account\n"));
		write(1,"4 : Search Account\n",sizeof("4 : Search Account\n"));
		write(1,"5 : Exit\n",sizeof("6 : Exit\n"));

		write(1,"Your choice : ",sizeof("Your choice : "));
		scanf("%d",&ch);
		
		switch(ch){
		case 1 :
			addAccount(sd);
			break;
		case 2 :
			deleteAccount(sd);
			break;
		case 3 :
			modifyAccount(sd);
			break;
		case 4 :
			searchAccount(sd);
			break;
		case 5 :
			write(sd,&ch,sizeof(int));
			write(1,"Thank you\n",sizeof("Thank you\n"));
			exit(0);
		default :
			write(1,"Invalid selection!!\n\n",sizeof("Invalid selection!!\n\n"));
			menu(sd);
			break;
		}
	}
}

void normalUserLogin(int sd){
	bool result;
	normalUser currUser;
	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&currUser.id);
	curr=currUser.id;
	write(1,"Password : ",sizeof("Password : "));
	scanf("%s",currUser.password);

	write(sd,&choice,sizeof(int));
	write(sd,&currUser,sizeof(normalUser));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Invalid login!!\n\n",sizeof("Invalid login!!\n\n"));
		chooseOption(sd);
	}
	else{
		write(1,"Succesfully logged in!!\n\n",sizeof("Succesfully logged in!!\n\n"));
	}
	return;
}

void jointUserLogin(int sd){
	bool result;
	jointUser currUser;
	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&currUser.id);
	curr=currUser.id;
	write(1,"Password : ",sizeof("Password : "));
	scanf("%s",currUser.password);

	write(sd,&choice,sizeof(int));
	write(sd,&currUser,sizeof(jointUser));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Invalid login!!\n\n",sizeof("Invalid login!!\n\n"));
		chooseOption(sd);
	}
	else{
		write(1,"Succesfully logged in!!\n\n",sizeof("Succesfully logged in!!\n\n"));
	}
	return;
}

void adminLogin(int sd){
	bool result;
	admin currUser;
	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&currUser.id);
	curr=currUser.id;
	write(1,"Password : ",sizeof("Password : "));
	scanf("%s",currUser.password);

	//to the server
	write(sd,&choice,sizeof(int));
	write(sd,&currUser,sizeof(admin));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Invalid login!!\n\n",sizeof("Invalid login!!\n\n"));
		chooseOption(sd);
	}
	else{
		write(1,"Succesfully logged in!!\n\n",sizeof("Succesfully logged in!!\n\n"));
	}
	return;
}

void deposit(int sd){
	float amm;
	int ch=1;
	bool result;

	write(1,"Amount to Deposit : Rs.",sizeof("Amount to Deposit : Rs."));
	scanf("%f",&amm);

	while(amm<=0){
		printf("Enter a valid amount!!\n");
		write(1,"Amount to Deposit : Rs.",sizeof("Amount to Deposit : Rs."));
		scanf("%f",&amm);
	}

	write(sd,&ch,sizeof(int));
	write(sd,&amm,sizeof(float));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error depositing your money!!\n\n",sizeof("Error depositing your money!!\n\n"));
	}
	else{
		write(1,"Succesfully deposited!!\n\n",sizeof("Succesfully deposited!!\n\n"));
	}
	menu(sd);
	return;
}

void withdraw(int sd){
	float amm;
	int ch=2;
	bool result;

	write(1,"Amount to Withdraw : Rs.",sizeof("Amount to Withdraw : Rs."));
	scanf("%f",&amm);

	while(amm<=0){
		printf("Enter a valid amount!!\n");
		write(1,"Amount to Withdraw : Rs.",sizeof("Amount to Withdraw : Rs."));
		scanf("%f",&amm);
	}
	write(sd,&ch,sizeof(int));
	write(sd,&amm,sizeof(float));

	read(sd,&result,sizeof(result));
	if(!result){
		write(1,"Error withdrawing your money, please check your balance!!\n\n",sizeof("Error depositing your money, please check your balance!!\n\n"));
	}
	else{
		write(1,"Succesfully withdrew!!\n\n",sizeof("Succesfully withdrew!!\n\n"));
	}
	menu(sd);
	return;
}

void balanceEnquiry(int sd){
	float amm;
	int ch=3;
	int len;

	//to the server
	write(sd,&ch,sizeof(int));
	
	len=read(sd,&amm,sizeof(float));	//from server

	write(1,"Available Balance :: Rs.",sizeof("Available Balance :: Rs."));
	printf("%0.2f\n\n",amm);

	menu(sd);
	return;
}

void changePassword(int sd){
	int ch=4;
	char newpass[20];
	bool result;

	write(1,"New password(max 20 characters) : ",sizeof("New password(max 20 characters) : "));
	scanf("%s",newpass);

	write(sd,&ch,sizeof(int));
	write(sd,newpass,sizeof(newpass));

	read(sd,&result,sizeof(result)); 

	if(!result){
		write(1,"Error changing the password!!\n\n",sizeof("Error changing the password!!\n\n"));
	}
	else{
		write(1,"Succesfully changed the password!!\n\n",sizeof("Succesfully changed the password!!\n\n"));
	}
	menu(sd);
	return;
}

void viewDetails(int sd){
	int ch=5;

	write(sd,&ch,sizeof(int));

	if(choice==1){
		normalUser currUser1;
		read(sd,&currUser1,sizeof(normalUser));
		
		printf("User ID : %d\n",currUser1.id);
		printf("Name : %s\n",currUser1.name);
		printf("Account Number : %d\n",currUser1.acc_no);
		printf("Available Balance : Rs.%0.2f\n",currUser1.balance);
		printf("Status : %s\n\n",currUser1.stat);
	}
	else if(choice==2){
		jointUser currUser2;
		read(sd,&currUser2,sizeof(jointUser));
		
		printf("User ID : %d\n",currUser2.id);
		printf("Main Account Holder's Name : %s\n",currUser2.name1);
		printf("Other Account Holder's Name : %s\n",currUser2.name2);
		printf("Account Number : %d\n",currUser2.acc_no);
		printf("Available Balance : Rs.%0.2f\n",currUser2.balance);
		printf("Status : %s\n\n",currUser2.stat);
	}
	menu(sd);
	return;
}

void addAccount(int sd){
	int ch=1;
	int type;
	bool result;

	write(sd,&ch,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser addUser1;
		write(1,"Name of the account holder : ",sizeof("Name of the account holder : "));
		scanf(" %[^\n]",addUser1.name);
		write(1,"Password(max 20 characters) : ",sizeof("Password(max 20 characters) : "));
		scanf("%s",addUser1.password);
		write(1,"Initial Deposit : Rs.",sizeof("Initial Deposit : Rs."));
		scanf("%f",&addUser1.balance);
		write(sd,&addUser1,sizeof(normalUser));
	}

	if(type==2){
		jointUser addUser2;
		write(1,"Name of the primary account holder : ",sizeof("Name of the primary account holder : "));
		scanf(" %[^\n]",addUser2.name1);
		write(1,"Name of the other account holder : ",sizeof("Name of the other account holder : "));
		scanf(" %[^\n]",addUser2.name2);
		write(1,"Password(max 20 characters) : ",sizeof("Password(max 20 characters) : "));
		scanf("%s",addUser2.password);
		write(1,"Initial Deposit : Rs.",sizeof("Initial Deposit : Rs."));
		scanf("%f",&addUser2.balance);
		write(sd,&addUser2,sizeof(jointUser));
	}
	
	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error adding the account!!\n\n",sizeof("Error adding the account!!\n\n"));
	}
	else{
		write(1,"Succesfully added the account!!\n\n",sizeof("Succesfully added the account!!\n\n"));
	}
	menu(sd);
	return;
}

void deleteAccount(int sd){
	int ch=2;
	int type,userID;
	bool result;

	write(sd,&ch,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);
	
	write(sd,&type,sizeof(int));

	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&userID);
	write(sd,&userID,sizeof(int));
	
	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error deleting the account ,no such user id exists!!\n\n",sizeof("Error deleting the account ,no such user id exists\n\n"));
	}
	else{
		write(1,"Succesfully deleted the account!!\n\n",sizeof("Succesfully deleted the account!!\n\n"));
	}
	menu(sd);
	return;
}

void modifyAccount(int sd){
	int ch=3;
	int type;
	bool result;

	write(sd,&ch,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser modUser1;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&modUser1.id);
		write(1,"Account Number : ",sizeof("Account Number : "));
		scanf("%d",&modUser1.acc_no);
		write(1,"New Name of the account holder : ",sizeof("New Name of the account holder : "));
		scanf(" %[^\n]",modUser1.name);
		write(1,"New Password(max 10 characters) : ",sizeof("New Password(max 10 characters) : "));
		scanf("%s",modUser1.password);
		write(1,"New Balance : ",sizeof("New Balance : "));
		scanf("%f",&modUser1.balance);
		write(sd,&modUser1,sizeof(normalUser));
	}

	if(type==2){
		jointUser modUser2;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&modUser2.id);
		write(1,"Account Number : ",sizeof("Account Number : "));
		scanf("%d",&modUser2.acc_no);
		write(1,"New Name of the primary account holder : ",sizeof("New Name of the primary account holder : "));
		scanf(" %[^\n]",modUser2.name1);
		write(1,"New Name of the other account holder : ",sizeof("New Name of the other account holder : "));
		scanf(" %[^\n]",modUser2.name2);
		write(1,"New Password(max 10 characters) : ",sizeof("New Password(max 10 characters) : "));
		scanf("%s",modUser2.password);
		write(1,"New Balance : ",sizeof("New Balance : "));
		scanf("%f",&modUser2.balance);
		write(sd,&modUser2,sizeof(jointUser));
	}
	
	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error modifying the account ,please re-check the User ID and Account No!!\n\n",sizeof("Error modifying the account ,please re-check the User ID and Account No!!\n\n"));
	}
	else{
		write(1,"Succesfully modified the account!!\n\n",sizeof("Succesfully modified the account!!\n\n"));
	}
	menu(sd);
	return;
}

void searchAccount(int sd){
	int ch=4;
	int type,len;
	bool result;

	write(sd,&ch,sizeof(int));

	write(1,"Enter the type account(1: Normal Account 2: Joint Account) : ",sizeof("Enter the type account(1: Normal Account 2: Joint Account) : "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser searchUser1;
		int userID;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&userID);
		write(sd,&userID,sizeof(int));
		
		len=read(sd,&searchUser1,sizeof(normalUser));
		if(len==0){
			write(1,"Please re-check the User ID!!\n\n",sizeof("Please re-check the User ID!!\n\n"));
		}
		else{
			printf("User ID : %d\n",searchUser1.id);
			printf("Name : %s\n",searchUser1.name);
			printf("Account Number : %d\n",searchUser1.acc_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser1.balance);
			printf("Status : %s\n\n",searchUser1.stat);
		}
	}

	if(type==2){
		jointUser searchUser2;
		int userID1;
		write(1,"User ID : ",sizeof("User ID : "));
		scanf("%d",&userID1);
		write(sd,&userID1,sizeof(int));
		
		len=read(sd,&searchUser2,sizeof(jointUser));
		if(len==0){
			write(1,"Please re-check the User ID!!\n\n",sizeof("Please re-check the User ID!!\n\n"));
		}
		else{
			printf("User ID : %d\n",searchUser2.id);
			printf("Main Account Holder's Name : %s\n",searchUser2.name1);
			printf("Other Account Holder's Name : %s\n",searchUser2.name2);
			printf("Account Number : %d\n",searchUser2.acc_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser2.balance);
			printf("Status : %s\n\n",searchUser2.stat);
		}
	}
	menu(sd);
	return;
}

int main(){
	struct sockaddr_in server;
	int sd,msgLength;
	char buff[50];
	char result;

	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1"); 
	server.sin_port=htons(5555);
	connect(sd,(struct sockaddr *)&server,sizeof(server));

	chooseOption(sd);
	menu(sd);	

	close(sd);

	return 0;
}
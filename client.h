#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdbool.h>

typedef struct normalUser{
	int id;
	char name[30];
	char password[20];
	int acc_no;
	float balance;
	char stat[20];
}normalUser;

typedef struct jointUser{
	int id;
	char name1[30];
	char name2[30];
	char password[20];
	int acc_no;
	float balance;
	char stat[20];
}jointUser;

typedef struct admin{
	int id;
	char username[30];
	char password[10];
}admin;



void normalUserLogin(int sd);
void jointUserLogin(int sd);
void adminLogin(int sd);
void menu(int sd);
void deposit(int sd);
void withdraw(int sd);
void balance(int sd);
void changePassword(int sd);
void balanceEnquiry(int sd);
void viewDetails(int sd);
void details(int sd);
void addAccount(int sd);
void deleteAccount(int sd);
void modifyAccount(int sd);
void searchAccount(int sd);
int choice,curr; // curr is the current user id
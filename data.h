#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

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

int getid1();
int getid2();
int getid3();

char* nu = "data_nu";
char* ju = "data_ju";
char* ad = "data_admin";
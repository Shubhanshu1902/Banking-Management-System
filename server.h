#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<fcntl.h>
#include <pthread.h>

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

char* nu = "data_nu";
char* ju = "data_ju";
char* ad = "data_admin";
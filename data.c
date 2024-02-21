#include "data.h"

int getid1(){
	int fd=open(nu,O_RDONLY,0744);
	normalUser record;
	lseek(fd,-sizeof(normalUser),SEEK_END);
	read(fd,&record,sizeof(normalUser));
	close(fd);
	return record.id+1;
}

int getid2(){
	int fd=open(ju,O_RDONLY,0744);
	jointUser record;
	lseek(fd,-sizeof(jointUser),SEEK_END);
	read(fd,&record,sizeof(jointUser));
	close(fd);
	return record.id+1;
}

int getid3(){
	int fd=open(ad,O_RDONLY,0744);
	admin record;
	lseek(fd,-sizeof(admin),SEEK_END);
	read(fd,&record,sizeof(admin));
	close(fd);
	return record.id+1;
}

int main(){
	int fd=open(ad,O_RDWR | O_CREAT,0744);
	int choice=0;
	admin newAdmin;
	printf("Name of the admin: ");
	scanf(" %s",newAdmin.username);
	printf("Password(max 20 characters): ");
	scanf(" %s",newAdmin.password);
	newAdmin.id=1000;
	printf("Your id is : %d\n",newAdmin.id);
	write(fd,&newAdmin,sizeof(newAdmin));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Name of the admin: ");
		scanf(" %[^\n]",newAdmin.username);
		printf("Password(max 10 characters): ");
		scanf(" %[^\n]",newAdmin.password);
		newAdmin.id=getid3();
		printf("Your id is : %d\n",newAdmin.id);
		write(fd,&newAdmin,sizeof(admin));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open(nu,O_RDWR | O_CREAT,0744);
	choice=1;
	normalUser newNUser;
	printf("Name of the normal user: ");
	scanf(" %[^\n]",newNUser.name);
	printf("Password(max 10 characters): ");
	scanf(" %[^\n]",newNUser.password);
	newNUser.id=1000;
	newNUser.balance=1000;
	newNUser.acc_no=(newNUser.id-1000)+100000;
	printf("Your id is : %d\n",newNUser.id);
	strcpy(newNUser.stat,"ACTIVE");
	write(fd,&newNUser,sizeof(normalUser));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Name of the normal user: ");
		scanf(" %[^\n]",newNUser.name);
		printf("Password(max 10 characters): ");
		scanf(" %[^\n]",newNUser.password);
		newNUser.id=getid1();
		newNUser.balance=1000;
		newNUser.acc_no=(newNUser.id-1000)+100000;
		printf("Your id is : %d\n",newNUser.id);
		strcpy(newNUser.stat,"ACTIVE");
		write(fd,&newNUser,sizeof(normalUser));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open(ju,O_RDWR | O_CREAT,0744);
	choice=1;
	jointUser newJUser;
	printf("Main name of the joint user: ");
	scanf(" %[^\n]",newJUser.name1);
	printf("Second name of the joint user: ");
	scanf(" %[^\n]",newJUser.name2);
	printf("Password(max 10 characters): ");
	scanf(" %[^\n]",newJUser.password);
	newJUser.id=1000;
	newJUser.balance=1000;
	newJUser.acc_no=(newJUser.id-1000)+100000;
	printf("Your id is : %d\n",newJUser.id);
	strcpy(newJUser.stat,"ACTIVE");
	write(fd,&newJUser,sizeof(jointUser));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Main name of the joint user: ");
		scanf(" %[^\n]",newJUser.name1);
		printf("Second name of the joint user: ");
		scanf(" %[^\n]",newJUser.name2);
		printf("Password(max 10 characters): ");
		scanf(" %[^\n]",newJUser.password);
		newJUser.id=getid2();
		newJUser.balance=1000;
		newJUser.acc_no=(newJUser.id-1000)+100000;
		printf("Your id is : %d\n",newJUser.id);
		strcpy(newJUser.stat,"ACTIVE");
		write(fd,&newJUser,sizeof(jointUser));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);
	return 0;
}


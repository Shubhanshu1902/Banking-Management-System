#include "server.h"

normalUser getNU(int ID){
	int i=ID-1000;
	normalUser user;
	int fd=open(nu,O_RDONLY,0744);
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    	     
	lock.l_len=sizeof(normalUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
	read(fd,&user,sizeof(normalUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return user;
}

jointUser getJU(int ID){
	int i=ID-1000;
	jointUser user;
	int fd=open(ju,O_RDONLY,0744);
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    	     
	lock.l_len=sizeof(jointUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	
	//getchar();

	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&user,sizeof(jointUser));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return user;
}

admin getAdmin(int ID){
	int i=ID-1000;
	admin user;
	int fd=open(ad,O_RDONLY,0744);
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(admin);    	     
	lock.l_len=sizeof(admin);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);
	lseek(fd,(i)*sizeof(admin),SEEK_SET);  
	read(fd,&user,sizeof(admin));

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return user;
}

bool checkNU(normalUser user){
	int i=user.id-1000;
	int fd=open(nu,O_RDONLY,0744);
	bool result;
	normalUser temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    	   
	lock.l_len=sizeof(normalUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	
	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);
	read(fd,&temp,sizeof(normalUser));
	if(!strcmp(temp.password,user.password) && !strcmp(temp.stat,"ACTIVE"))	result=true;
	else result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool checkJU(jointUser user){
	int i=user.id-1000;
	int fd=open(ju,O_RDONLY,0744);
	bool result;
	jointUser temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    	     
	lock.l_len=sizeof(jointUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	
	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&temp,sizeof(jointUser));
	if(!strcmp(temp.password,user.password) && !strcmp(temp.stat,"ACTIVE"))	result=true;
	else result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool checkAdmin(admin user){
	int i=user.id-1000;
	int fd=open(ad,O_RDONLY,0744);
	bool result;
	admin temp;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(admin);    	     
	lock.l_len=sizeof(admin);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	
	lseek(fd,(i)*sizeof(admin),SEEK_SET);  
	read(fd,&temp,sizeof(admin));
	if(!strcmp(temp.password,user.password))	result=true;
	else result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool deposit(int accType,int ID,float amt){
	int i=ID-1000;
	if(accType==1){
		int fd=open(nu,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    
		lock.l_len=sizeof(normalUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	
		//getchar();

		normalUser user;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET); 
		read(fd,&user,sizeof(normalUser));
		
		if(!strcmp(user.stat,"ACTIVE")){
			user.balance+=amt;
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&user,sizeof(normalUser));
			result=true;
		}
		else result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;		
	}
	else if(accType==2){
		int fd=open(ju,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    
		lock.l_len=sizeof(jointUser);	       
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	
		jointUser user;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&user,sizeof(jointUser));
		
		if(!strcmp(user.stat,"ACTIVE")){
			user.balance+=amt;
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&user,sizeof(jointUser));
			result=true;
		}
		else result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;	
	}
	return false;
}

bool withdraw(int accType,int ID,float amt){
	int i=ID-1000;
	if(accType==1){
		int fd=open(nu,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);   
		lock.l_len=sizeof(normalUser);	       
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	
		normalUser user;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
		read(fd,&user,sizeof(normalUser));
		
		if(!strcmp(user.stat,"ACTIVE") && user.balance>=amt){
			user.balance-=amt;
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&user,sizeof(normalUser));
			// printf("Ammount withdrawn\n");
			result=true;
		}
		else result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;	
	}
	else if(accType==2){
		int fd=open(ju,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    
		lock.l_len=sizeof(jointUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);

		jointUser user;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&user,sizeof(jointUser));
		
		if(!strcmp(user.stat,"ACTIVE") && user.balance>=amt){
			user.balance-=amt;
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&user,sizeof(jointUser));
			result=true;
		}
		else result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

float getBalance(int accType,int ID){
	int i=ID-1000;
	float result;
	if(accType==1){
		int i=ID-1000;
		int fd=open(nu,O_RDONLY,0744);
		normalUser temp;
	
		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    	     
		lock.l_len=sizeof(normalUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
		read(fd,&temp,sizeof(normalUser));
		if(!strcmp(temp.stat,"ACTIVE"))	result=temp.balance;
		else result=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int i=ID-1000;
		int fd=open(ju,O_RDONLY,0744);
		jointUser temp;
	
		int fl1;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    	     
		lock.l_len=sizeof(jointUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&temp,sizeof(jointUser));
		if(!strcmp(temp.stat,"ACTIVE"))	result=temp.balance;
		else					result=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return 0;
}

bool changePassword(int accType,int ID,char newPwd[10]){
	int i=ID-1000;
	if(accType==1){
		int fd=open(nu,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(normalUser);    
		lock.l_len=sizeof(normalUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		normalUser user;
		lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
		read(fd,&user,sizeof(normalUser));
		
		if(!strcmp(user.stat,"ACTIVE")){
			strcpy(user.password,newPwd);
			lseek(fd,sizeof(normalUser)*(-1),SEEK_CUR);
			write(fd,&user,sizeof(normalUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	else if(accType==2){
		int fd=open(ju,O_RDWR,0744);
		bool result;
		int fl1;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(i)*sizeof(jointUser);    
		lock.l_len=sizeof(jointUser);	             
		lock.l_pid=getpid();
	
		fl1=fcntl(fd,F_SETLKW,&lock);	

		jointUser user;
		lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
		read(fd,&user,sizeof(jointUser));
		
		if(!strcmp(user.stat,"ACTIVE")){
			strcpy(user.password,newPwd);
			lseek(fd,sizeof(jointUser)*(-1),SEEK_CUR);
			write(fd,&user,sizeof(jointUser));
			result=true;
		}
		else	result=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);

		close(fd);
		return result;
	}
	return false;
}

bool addNU(normalUser record){
	int fd=open(nu,O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(normalUser);    
	lock.l_len=sizeof(normalUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	normalUser user;
	lseek(fd,(-1)*sizeof(normalUser),SEEK_END);  
	read(fd,&user,sizeof(normalUser));
		
	record.id=user.id+1;
	record.acc_no=user.acc_no+1;
	strcpy(record.stat,"ACTIVE");
	
	int j=write(fd,&record,sizeof(normalUser));
	if(j!=0)	result=true;
	else	result=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool addJU(jointUser record){
	int fd=open(ju,O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(jointUser);    
	lock.l_len=sizeof(jointUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	jointUser user;
	lseek(fd,(-1)*sizeof(jointUser),SEEK_END);  
	read(fd,&user,sizeof(jointUser));
		
	record.id=user.id+1;
	record.acc_no=user.acc_no+1;
	strcpy(record.stat,"ACTIVE");
	
	int j=write(fd,&record,sizeof(jointUser));
	if(j!=0)	result=true;
	else	result=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool deleteNU(int ID){
	int i=ID-1000;
	int fd=open(nu,O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    
	lock.l_len=sizeof(normalUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	
	normalUser user;
	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
	read(fd,&user,sizeof(normalUser));
	
	if(!strcmp(user.stat,"ACTIVE")){	
		strcpy(user.stat,"CLOSED");
		user.balance=0;
		
		lseek(fd,(-1)*sizeof(normalUser),SEEK_CUR); 
		int j=write(fd,&user,sizeof(normalUser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool deleteJU(int ID){
	int i=ID-1000;
	int fd=open(ju,O_RDWR,0744);
	bool result;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    
	lock.l_len=sizeof(jointUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	jointUser user;
	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&user,sizeof(jointUser));
	
	if(!strcmp(user.stat,"ACTIVE")){	
		strcpy(user.stat,"CLOSED");
		user.balance=0;
		
		lseek(fd,(-1)*sizeof(jointUser),SEEK_CUR); 
		int j=write(fd,&user,sizeof(jointUser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool modifyNU(normalUser modUser){
	int i=modUser.id-1000;
	int fd=open(nu,O_RDWR,0744);
	bool result=false;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(normalUser);    
	lock.l_len=sizeof(normalUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	

	normalUser user;
	lseek(fd,(i)*sizeof(normalUser),SEEK_SET);  
	read(fd,&user,sizeof(normalUser));
	
	if(!strcmp(user.stat,"ACTIVE") && (modUser.acc_no==user.acc_no)){	
		strcpy(modUser.stat,"ACTIVE");
		lseek(fd,(-1)*sizeof(normalUser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(normalUser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

bool modifyJU(jointUser modUser){
	int i=modUser.id-1000;
	int fd=open(ju,O_RDWR,0744);
	bool result=false;
	
	int fl1;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(jointUser);    
	lock.l_len=sizeof(jointUser);	             
	lock.l_pid=getpid();
	
	fl1=fcntl(fd,F_SETLKW,&lock);	//lock the selected record
	//getchar();

	jointUser user;
	lseek(fd,(i)*sizeof(jointUser),SEEK_SET);  
	read(fd,&user,sizeof(jointUser));
	
	if(!strcmp(user.stat,"ACTIVE")  && (modUser.acc_no==user.acc_no)){	
		strcpy(modUser.stat,"ACTIVE");
		lseek(fd,(-1)*sizeof(jointUser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(jointUser));
		if(j!=0)	result=true;
		else		result=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return result;	
}

void serverTask(int nsd){
	int msgLength,select,type,option,accType,id;
	bool result;
	while(1){
		read(nsd,&option,sizeof(option));
		printf("Option : %d\n",option);

		if(option==1){
			normalUser currUser1;
			accType=1;
			msgLength=read(nsd,&currUser1,sizeof(normalUser));
			printf("Username : %d\n",currUser1.id);
			printf("Password : %s\n",currUser1.password);
			id=currUser1.id;
			result=checkNU(currUser1);
			write(nsd,&result,sizeof(result));
		}
		else if(option==2){
			jointUser currUser2;
			accType=2;
			msgLength=read(nsd,&currUser2,sizeof(jointUser));
			id=currUser2.id;
			printf("Username : %d\n",currUser2.id);
			printf("Password : %s\n",currUser2.password);
			result=checkJU(currUser2);
			write(nsd,&result,sizeof(result));
		}
		else if(option==3){
			admin currUser3;
			accType=3;
			msgLength=read(nsd,&currUser3,sizeof(admin));
			id=currUser3.id;
			printf("Username : %d\n",currUser3.id);
			printf("Password : %s\n",currUser3.password);
			result=checkAdmin(currUser3);
			write(nsd,&result,sizeof(result));
		}
		else{
			result=false;
			write(nsd,&result,sizeof(result));
		}
		if(result)	break;		
	}

	while(1){
		read(nsd,&select,sizeof(int));
		if(option==1 || option==2){
			if(select==1){
				float amt;
				read(nsd,&amt,sizeof(float));
				result=deposit(accType,id,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==2){
				float amt;
				read(nsd,&amt,sizeof(float));
				result=withdraw(accType,id,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==3){
				float amt;
				amt=getBalance(accType,id);
				write(nsd,&amt,sizeof(float));
			}
			else if(select==4){
				char pwd[10];
				read(nsd,pwd,sizeof(pwd));
				result=changePassword(accType,id,pwd);
				write(nsd,&result,sizeof(result));
			}
			else if(select==5){
				if(option==1){
					normalUser user1=getNU(id);
					write(nsd,&user1,sizeof(normalUser));
				}
				else if(option==2){
					jointUser user2=getJU(id);
					write(nsd,&user2,sizeof(jointUser));
				}
			}
			else if(select==6)	break;
		}
		else if(option==3){
			read(nsd,&type,sizeof(int));
			if(select==1){
				if(type==1){
					normalUser newUser1;
					read(nsd,&newUser1,sizeof(normalUser));
					result=addNU(newUser1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					jointUser newUser2;
					read(nsd,&newUser2,sizeof(jointUser));
					result=addJU(newUser2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==2){
				if(type==1){
					int delUserID1;
					read(nsd,&delUserID1,sizeof(int));
					result=deleteNU(delUserID1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					int delUserID2;
					read(nsd,&delUserID2,sizeof(int));
					result=deleteJU(delUserID2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==3){
				if(type==1){
					normalUser modUser1;
					read(nsd,&modUser1,sizeof(normalUser));
					result=modifyNU(modUser1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2){
					jointUser modUser2;
					read(nsd,&modUser2,sizeof(jointUser));
					result=modifyJU(modUser2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==4){
				if(type==1){
					normalUser searchUser1;
					int userID1;
					read(nsd,&userID1,sizeof(int));
					searchUser1=getNU(userID1);
					write(nsd,&searchUser1,sizeof(normalUser));
				}
				else if(type==2){
					jointUser searchUser2;
					int userID2;
					read(nsd,&userID2,sizeof(int));
					searchUser2=getJU(userID2);
					write(nsd,&searchUser2,sizeof(jointUser));
				}
			}
			else if(select==5)	break;
		}
	}
	close(nsd);
	write(1,"Ended client session.....\n",sizeof("Ended client session.....\n"));
	return;
}

void *connection_handler(void *nsd) {
	int nsfd = *(int*)nsd;
	serverTask(nsfd);
}


int main(){
	struct sockaddr_in server,client;
	int sd,nsd,clientLen;
	pthread_t threads;
	bool result;
	sd=socket(AF_INET,SOCK_STREAM,0);

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5555);

	bind(sd,(struct sockaddr *)&server,sizeof(server));
	listen(sd,5);	//queue length :: 5 clients per connection
	
	write(1,"Waiting for the client.....\n",sizeof("Waiting for the client.....\n"));
	while(1){
		clientLen=sizeof(client);
		nsd=accept(sd,(struct sockaddr *)&client,&clientLen);

		write(1,"Connected to the client.....\n",sizeof("Connected to the client.....\n"));
		if(pthread_create(&threads,NULL,connection_handler,(void*) &nsd)<0){
			perror("could not create thread");
			return 1;
		}	
	}
	pthread_exit(NULL);
	close(sd);
	return 0;
}
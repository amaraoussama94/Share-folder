/********************************************************************************/
/**  This  is  the  code for the  Client                                       **/
/**  For the momesnt we  are  using local Host ip 127.0.0.1                    **/
/** @Oussama AMARA                                                             **/
/** Last modification 6/11/2022                                                **/
/** version 0.5                                                               **/
/********************************************************************************/

#include <arpa/inet.h> // inet_addr()/
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define PORT 8080// Port number  must be > then 1100
#define SA struct sockaddr

//Struct for Authentication
struct Authentication{
	char name[10];
	int userId;
	char password[10];
};


void func(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		printf("[i]Enter the string : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("[i]From Server : %s", buff);
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("[i]Client Exit...\n");
			break;
		}
		if ((strncmp(buff, "Exit", 4)) == 0) {
			printf("[i]Stop server ...\n");
			break;
		}
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, client_addr;
	char seradd[20];
	char *ptr_seraddr =NULL;
	ptr_seraddr = seradd;
    //char *ip ="127.0.0.1";
	struct Authentication myAuth;
	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);// AF_INET :IPV4  , SOCK_STREAM:TCP
	if (sockfd < 0) 
    {
		perror("[-]socket creation failed...\n");
		exit(1);
	}
	else
		printf("[+]Socket successfully created..\n");
        //initialize to zeo 
        /* bzero :Set N bytes of pointer to 0.  */
	bzero(&servaddr, sizeof(servaddr));//or you can use memset (&servaddr,'\0', sizeof(servaddr))

	//get the @IP of the serveur 
	printf("[i]Tape the serveur @IP : ");
	fgets(seradd,13,stdin);
	
	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ptr_seraddr);// the adress of the serveur 
	servaddr.sin_port = htons(PORT);  //htons :Functions to convert between host and network byte order
	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) <0) 
    {
		perror("[-]connection with the server failed...\n");
		exit(1);
	}
	else
		printf("[+]connected to the server..\n");
	// Getting from the  user  user ID and password for Authentification
	Authentification : printf("[i]Enter userId : "); 
	scanf("%d",&myAuth.userId);
	printf("[i]Enter password : "); 
	scanf("%s",myAuth.password);
	//sending the information to the serveur 
	write(sockfd,&myAuth,sizeof(myAuth));
	//Get the serveur message  
	char message[20];
	read(sockfd, message, sizeof(message));
	printf("%s ",message);
	
	if (strcmp("Login Successful\n", message) == 0) 
	{// really i dont know  why i need this but it make it work normally
		printf("[i]Enter the string : ");
		scanf("\n");
		// function for chat
		func(sockfd);
	}
	else 
	{
		perror("[-]Flaid to log in please try again \n "); 
		goto Authentification;
	}
  	// function for chat
	//func(sockfd);
	// close the socket
	close(sockfd);
}

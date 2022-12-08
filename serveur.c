/********************************************************************************/
/**  This  is  the  code for the  server                                       **/
/**  using local Host ip 127.0.0.1    Iterative Server                         **/
/** @Oussama AMARA                                                             **/
/** Last modification 6/11/2022                                                **/
/** version 0.5                                                                **/
/********************************************************************************/
#include <arpa/inet.h> // inet_addr()/
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <errno.h>


#define  LISTENQ 8/*maximum number of client connections */
#define MAX 80 //Max length of the  buffer for message exchange 
#define PORT 8080// Port number  must be > then 1100
#define SA struct sockaddr
#define True 1
#define False 0
//Struct for Authentication
struct Authentication{
	char name[10];
	int userId;
	char password[10];
};


// Function designed for chat between client and server.
void func(int connfd, int* ptrRUN)
{
	
	char buff[MAX];
	int n;
	// infinite loop for chat
	for (;;)
	{
		/* bzero :Set N bytes of pointer to 0.  */
		bzero(buff, MAX);//or you can use memset (&buff,'\0',sizeof(buff))

		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));
		// print buffer which contains the client contents
		printf("[i]From client: %s\t To client : ", buff);
		bzero(buff, MAX);
		n = 0;
		// copy server message in the buffer
		while ((buff[n++] = getchar()) != '\n')
		;

		// and send that buffer to client
		write(connfd, buff, sizeof(buff));
		
		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0) 
		{
			printf("[i]Server Exit...\n");
			break;
		}
		if (strncmp("Exit", buff, 4) == 0) 
		{
			*ptrRUN = False;
			printf("[i]Stop server ...\n");
			//printf("[d] ptrRUN = %d\n",*ptrRUN);
			break;
		}
	}
}

// Returns hostname for the local computer
void checkHostName(int hostname)
{
	if (hostname == -1)
	{
		perror("[-]gethostname");
		exit(1);
	}
}

// Returns host information corresponding to host name
void checkHostEntry(struct hostent * hostentry)
{
	if (hostentry == NULL)
	{
		perror("[-]gethostbyname");
		exit(1);
	}
}

// Converts space-delimited IPv4 addresses
// to dotted-decimal format
void checkIPbuffer(char *IPbuffer)
{
	if (NULL == IPbuffer)
	{
		perror("[-]inet_ntoa");
		exit(1);
	}
}


// Driver function
int main()
{
	/*Const of  server */
	int RUN=True;
	int* ptrRUN =NULL;
	ptrRUN = &RUN;
	/*to get @ IP of th host machine */
	char *IPbuffer;
	struct hostent *host_entry;
	char hostbuffer[256];
	int hostname;
	/*for socket*/
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;
	//char *ip ="127.0.0.1";
	struct Authentication myAuth, Auth[5]={{"oama",1,"oama"},
						   {"oama",2,"oama"},
						   {"oama",3,"oama"},
						   {"oama",4,"oama"},
						   {"oama",5,"oama"}};
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
	/*get the local host @IP and host name */
	// To retrieve hostname
	hostname = gethostname(hostbuffer, sizeof(hostbuffer));
	checkHostName(hostname);
	

	// To retrieve host information
	host_entry = gethostbyname(hostbuffer);
	checkHostEntry(host_entry);
	// To convert an Internet network
	// address into ASCII string
	IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));

	printf("[+]Host IP: %s\n", IPbuffer);

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr =htonl(INADDR_ANY);// Address to accept any incoming messages.   
	servaddr.sin_port = htons(PORT);//htons :Functions to convert between host and network byte order
	
	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) < 0) 
	{
		perror("[-]socket bind failed...\n");
		exit(1);
	}
	else
		printf("[+]Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, LISTENQ)) != 0) //5 connection requests will be queued before further requests are refused.
	{
		printf("[-]Listen failed...\n");
		exit(1);
	}
	else
		printf("[+]Server listening..\n");

	printf("[i]To stop Server  tape  exit server ..\n");
	while (RUN)
	{
		printf("[i]RUN = %d \n",RUN);
		len = sizeof(cli);
		//printf("hello ok \n");
		// Accept the data packet from client and verification
		connfd = accept(sockfd, (SA*)&cli, &len);
		
		if (connfd < 0) 
		{
			perror("[-]server accept failed...\n");
			exit(1);
		}
		else
			printf("[+]server accept the client...\n");
		// recive the authentification from client and printing it 
		Authentification: read(connfd, &myAuth, sizeof(myAuth));

		//printf("userId received :%d\n",myAuth.userId);
		//printf("password received :%s\n",myAuth.password);

		// check if the user and password are in the struc mean a trusted one 
		int fl=1;
		for(int i=0;i<5;i++)
		{
			if((myAuth.userId==Auth[i].userId) && (strcmp(myAuth.password,Auth[i].password)==0))
			{
				fl=0;
				break;
			}
		}
		
		
		if(fl==0)
		{	// sending msg to client for Login Successful
			char message[20]="Login Successful\n";
			printf("[+]Successful Authentification \n");
			write(connfd, message, sizeof(message));
			
			// Function for chatting between client and server
			func(connfd,ptrRUN);
			
		}
		else 
		{
			// sending msg to client for Login Failure
			char message[20]="[-]Login Failure\n";
			write(connfd, message, sizeof(message));
			goto Authentification;// recheck for  new  imput 
			
		}	
		close(connfd);
	}
    

	// After chatting close the socket
	close(sockfd);
}

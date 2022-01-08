#include <stdio.h>  //Input, Output. Do I really even need to describe this?
#include <sys/types.h> //Data types for system calls
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h> //Constants, Structures needed for domain addresses

#include <stdlib.h>

void error (const char *msg)
{
	perror(msg); //Prints msg and then the error
	exit(1);
}

int main(int argc, char *argv[])
{
	//fd = file descriptor
	int sockfd, newsockfd, portno, n;
	char buffer[255];

	struct sockaddr_in serv_addr, cli_addr;
	
	socklen_t clilen;

	printf("Hello World!");

	if (argc < 2)
	{
		fprintf(stderr, "Port Number not provided\n");
		exit(1);
	}
	
	/* CREATE AND BIND THE SERVER SOCKET */
	
	sockfd = socket(AF_INET6, SOCK_STREAM, 0); //Create a socket, assign it to sockfd
	
	if (sockfd < 0)
	{
		error("Error opening socket.");
	}
	
	memset((char *) &serv_addr, 0, sizeof(serv_addr));

	portno = atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET6;		//Address Family = IPv6
	serv_addr.sin_addr.s_addr = INADDR_ANY; 
	serv_addr.sin_port = htons(portno); 	//htons: host to network short
	
	//The bind() function binds a unique local name to the socket with descriptor socket.
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
	{
		error("Binding Failed");
	}
	
	/* START LISTENING, CONNECTING, ANSWERING */
	
	//listen(int socket, int backlog) where backlog = max connection requests the queue can handle (max num of clients)
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0)
		error("Error on accept");
	
	while(1)
	{
		/* READ ANY MESSAGES */
		memset(buffer, 0, 256);
		n = read(newsockfd, buffer, 255);
		
		if (n < 0)
			error("Error on read");
		
		printf("Client: %s\n", buffer);
		
		/* SEND ANY MESSAGES */
		memset(buffer, 0, 255);
		
		fgets(buffer, 255, stdin);
		n = write(newsockfd, buffer, strlen(buffer));
		
		if (n < 0)
			error("Error on write");
		
		int i = strncmp("Terminate", buffer, 9);
		
		if (i == 0)
		{
			break;
		}
	}
	
	close(newsockfd);
	close(sockfd);
	return 0;

    //return 0;
	
}
#include "../include/common.h"

int main(int argc, char *argv[])
{
	//fd = file descriptor
	int sockfd, newsockfd, n;
	char buffer_read[255], buffer_write[255];

	struct sockaddr_in serv_addr, cli_addr;
	
	socklen_t clilen;

	/*
	if (argc < 2)
	{
		fprintf(stderr, "Port Number not provided\n");
		exit(1);
	}
	*/
	
	/* CREATE AND BIND THE SERVER SOCKET */
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //Create a socket, assign it to sockfd
	
	if (sockfd < 0)
	{
		error("Error opening socket");
	}
	
	memset((char *) &serv_addr, 0, sizeof(serv_addr));

	//PORTNO = atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET;		//Address Family = IPv6
	serv_addr.sin_addr.s_addr = INADDR_ANY; 
	serv_addr.sin_port = htons(PORTNO); 	//htons: host to network short
	
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
		memset(buffer_read, 0, 255);
		n = read(newsockfd, buffer_read, 255);
		
		if (n < 0)
			error("Error on read");
		
		printf("Client: %s\n", buffer_read);
		
		/* SEND ANY MESSAGES */
		/* 		
		memset(buffer_write, 0, 255);
		
		fgets(buffer_write, 255, stdin);
		n = write(newsockfd, buffer_write, strlen(buffer_write));
		
		if (n < 0)
			error("Error on write");
		
		int i = strncmp("Terminate", buffer_read, 9);
		
		if (i == 0)
		{
			break;
		} 
		*/
	}
	
	close(newsockfd);
	close(sockfd);
	return 0;

    //return 0;
	
}
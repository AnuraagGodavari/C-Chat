#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error (const char *msg)
{
	perror(msg); //Prints msg and then the error
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	char buffer[256];
	
	/*
	argv[0] filename
	argv[1] server_ipaddress
	argv[2] portno
	*/
	if (argc < 3)
	{
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(1);
	}
	
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0)
		error("Error opening socket");
	
	server = gethostbyname(argv[1]);
	if (server == NULL)
	{
		fprintf(stderr, "Error: no such host");
	}
	
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length); //Copy n bytes from server to serv_addr
	
	serv_addr.sin_port = htons(portno); //htons = host to network short
	
	//Try connecting, if < 0 then error
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Connection Failed");
	
	while(1)
	{
		memset(buffer, 0, 255);
		
		fgets(buffer, 255, stdin);
		n = write(sockfd, buffer, strlen(buffer));
		
		if (n < 0)
			error("Error on write");
		
		memset(buffer, 0, 255);
		
		n = read(sockfd, buffer, 255);
		
		if(n < 0)
			error("Error on read");
		
		printf("Server: %s", buffer);
		
		int i = strncmp("Terminate", buffer, 9);
		if (i == 0)
			break;

	}
}

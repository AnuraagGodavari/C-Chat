#include "../include/common.h"
  
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}

int main(int argc, char *argv[])
{
	int sockfd, n;
	
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	char buffer_read[256], buffer_write[256];
	
	/* argv[0] filename, argv[1] server_ipaddress, argv[2] PORTNO */
	
	/*
	if (argc < 3)
	{
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(1);
	}
	*/
	//PORTNO = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0)
		error("Error opening socket");
	
	server = gethostbyname("127.0.0.1"); //server = gethostbyname(argv[1]);
	
	if (server == NULL)
	{
		fprintf(stderr, "Error: no such host");
	}
	
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length); //Copy n bytes from server to serv_addr
	
	serv_addr.sin_port = htons(PORTNO); //htons = host to network short
	
	//Try connecting, if < 0 then error
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Connection Failed");
	
	while(1)
	{
		/*SEND ANY MESSAGES */
		memset(buffer_read, 0, 255);
		
		/* 
		pthread_t thread_id;
		printf("Before Thread\n");
		pthread_create(&thread_id, NULL, myThreadFun, NULL);
		 */
		
		fgets(buffer_read, 255, stdin);
		n = write(sockfd, buffer_read, strlen(buffer_read));
		
		/* 		
		pthread_join(thread_id, NULL);
		printf("After Thread\n");
		 */
		
		if (n < 0)
			error("Error on write");
		
		/*READ ANY MESSAGES *//* 
		memset(buffer_write, 0, 255);
		
		n = read(sockfd, buffer_write, 255);
		
		if(n < 0)
			error("Error on read");
		
		printf("Server: %s\n", buffer_write);
		
		int i = strncmp("Terminate", buffer_read, 9);
		if (i == 0)
			break; */

	}
}

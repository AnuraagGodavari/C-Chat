#include "../include/common.h"

void error (const char *msg)
{
	perror(msg); //Prints msg and then the error
	exit(1);
}
#Compilation Command
CC = gcc
#Debug Flags
CFLAGS = -Wall -g

#Source code Folder
SRC = Program/src
#Object Folder
OBJ = Obj

all: Test_Server Test_Client 
	
Test_Server: $(OBJ)/test_server.o $(OBJ)/common.o
	$(CC) $(CFLAGS) $(OBJ)/test_server.o $(OBJ)/common.o -o Test_Server

Test_Client: $(OBJ)/test_client.o $(OBJ)/common.o
	$(CC) $(CFLAGS) $(OBJ)/test_client.o $(OBJ)/common.o -o Test_Client
	
#Create or update any needed *.o files in the OBJ/ directory from all .c files in src/.
# -c creates object files without linking, -o specifies the output
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@
	
#Not called in "all", so won't run.
clean: 
	rm *.o
	
	
	
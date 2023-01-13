CC = gcc
CFLAGS = -I.
OBJ = main.o palloc.o hash.o bst.o request.o disk.o cJSON.o

EXECUTABLE := server.out
all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)
CC = gcc
CFLAGS = -g -I.
OBJ = main.o palloc.o request.o disk.o cJSON.o

EXECUTABLE := server.out
all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)
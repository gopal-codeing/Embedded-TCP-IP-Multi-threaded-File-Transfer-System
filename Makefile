# Compiler
	CC = gcc

# Compiler Flags
CFLAGS = -Wall -Iinclude


# Server
SERVER_TARGET = bin/server
SERVER_SRC = src/server.c
SERVER_OBJ = obj/server.o

# Client
CLIENT_TARGET = bin/client
CLIENT_SRC = src/client.c
CLIENT_OBJ = obj/client.o

# Build All
all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Server Build
$(SERVER_TARGET): $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) -o $(SERVER_TARGET)

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $(SERVER_SRC) -o $(SERVER_OBJ)

# Client Build
$(CLIENT_TARGET): $(CLIENT_OBJ)
	$(CC) $(CLIENT_OBJ) -o $(CLIENT_TARGET)

$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -c $(CLIENT_SRC) -o $(CLIENT_OBJ)

# Clean
clean:
	rm -f obj/*.o
	rm -f bin/server
	rm -f bin/client

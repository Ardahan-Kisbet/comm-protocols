#Compiler
CC 				= g++

# Flags
CFLAGS 			= -W -Wall -std=c++11
IFLAGS 			= -I ${INC_DIR}

# Include Directory
INC_DIR = include

binary: main.o protocol.o
	# creating binary
	$(CC) main.o protocol.o -o binary

main.o: main.cpp
	$(CC) -c main.cpp $(IFLAGS)

protocol.o: src/protocol.cpp
	$(CC) -c src/protocol.cpp $(IFLAGS)

clean:
	# removing object files and binary
	rm *.o binary

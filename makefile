binary: main.o protocol.o
	g++ main.o protocol.o -o binary

main.o: main.cpp
	g++ -c main.cpp -I include

protocol.o: protocol.cpp
	g++ -c protocol.cpp -I include

clean:
	rm *.o binary

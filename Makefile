prog: main.o Executive.o Board.o Player.o
	g++ -g -Wall -std=c++11 main.o Executive.o Board.o Player.o -o prog

main.o: main.cpp
	g++ -g -Wall -std=c++11 -c main.cpp

Executive.o: Executive.cpp Executive.h
	g++ -std=c++11 -c Executive.cpp

Player.o: Player.cpp Player.h
	g++ -std=c++11 -c Player.h

Board.o: Board.cpp Board.h
	g++ -std=c++11 -c Board.cpp

clean:
	rm *.o prog

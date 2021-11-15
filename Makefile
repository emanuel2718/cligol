all: main.cpp
	g++ main.cpp util.cpp gameoflife.cpp -o cligol -Werror -Wall -lncurses


clean:
	rm cligol

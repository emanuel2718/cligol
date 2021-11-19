all: main.cpp
	g++ main.cpp util.cpp gameoflife.cpp -o cligol -Werror -Wall -lncurses -ggdb3


clean:
	rm cligol

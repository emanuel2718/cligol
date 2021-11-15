all: main.cpp
	g++ main.cpp util.cpp -o cligol -Werror -Wall -lncurses


clean:
	rm cligol

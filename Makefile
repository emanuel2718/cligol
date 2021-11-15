all: main.cpp
	g++ main.cpp -o cligol -Werror -Wall -lncurses


clean:
	rm cligol

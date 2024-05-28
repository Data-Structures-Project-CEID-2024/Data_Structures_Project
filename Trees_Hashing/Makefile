all:
	g++ Hashing.cpp Trees.cpp Input.cpp Main.cpp  -o output/a -Wall -Werror -Wextra && ./output/a

debug:
	g++ Hashing.cpp Trees.cpp Input.cpp Main.cpp -g -o output/a -Wall -Werror -Wextra && ./output/a 


valgrind:
	g++ Hashing.cpp Trees.cpp Input.cpp Main.cpp -g -o output/a -Wall -Werror -Wextra && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./output/a

run :
	gdb ./output/a
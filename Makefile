all:
	g++  Sort.cpp Input.cpp Main.cpp -o output/a -Wall -Werror -Wextra && ./output/a

compile:
	g++  Sort.cpp  Input.cpp Main.cpp -g -o output/a -Wall -Werror -Wextra && ./output/a

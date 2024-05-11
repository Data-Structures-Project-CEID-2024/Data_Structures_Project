all:
	g++ Input.cpp  -o a -Wall -Werror -Wextra && ./a

debug:
	g++   Input.cpp  -g -o a -Wall -Werror -Wextra && ./a 
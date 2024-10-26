taillight: taillight.c
	clang -g -Wall -Wextra --pedantic -fsanitize=address -o taillight taillight.c

run: taillight
	./taillight
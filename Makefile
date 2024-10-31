taillight: taillight.c guppy.h
	clang -g -Wall -Wextra --pedantic -fsanitize=address -o taillight taillight.c

run: taillight
	./taillight

taillight_checker: ./tests/taillight_checker.c taillight
	clang -g -Wall -Wextra --pedantic -fsanitize=address -o ./tests/taillight_checker ./tests/taillight_checker.c

test: taillight_checker
	./tests/taillight_checker
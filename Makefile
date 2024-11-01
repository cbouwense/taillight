taillight: taillight.c guppy.h
	clang -g -Wall -Wextra --pedantic -fsanitize=address -o taillight taillight.c

run: taillight
	./taillight

taillight_test: ./tests/taillight_test.c taillight
	clang -g -Wall -Wextra --pedantic -fsanitize=address -o ./tests/taillight_test ./tests/taillight_test.c

test: taillight_test
	./tests/taillight_test
flags=-std=c11 -O2 -Wall -Wextra -pedantic -Wstrict-overflow -fno-strict-aliasing

all:
	gcc ${flags} -c src/stack.c -o /dev/null
	gcc ${flags} src/postfix_eval.c -o bin/postfix_eval

clean:
	-rm bin/postfix_eval

CFLAGS += -Wall -Wextra -Wformat-security -g -std=gnu99

umemtester: umemtester.c Makefile
	gcc $(CFLAGS) -o umemtester umemtester.c

# Depends on compilation to make sure the syntax is ok.
format: umemtester
	clang-format -i *.c

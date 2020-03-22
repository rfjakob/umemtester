CFLAGS += -Wall -Wextra -Wformat-security -std=gnu99

umemtester: umemtester.c Makefile
	$(CROSS_COMPILE)gcc $(CFLAGS) -o umemtester umemtester.c

umemtester-static: umemtester.c Makefile
	$(CROSS_COMPILE)gcc $(CFLAGS) -static -s -o umemtester-static umemtester.c

# Depends on compilation to make sure the syntax is ok.
format: umemtester
	clang-format -i *.c

#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

void usage(char* myname)
{
    printf("usage: %s SIZE_MIB\n", myname);
    exit(1);
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        usage(argv[0]);
    }

    errno = 0;
    long mib = strtol(argv[1], NULL, 10);
    if (mib <= 0 || errno != 0) {
        printf("fatal: invalid SIZE_MIB: %s\n", argv[1]);
        usage(argv[0]);
    }
    unsigned long bytes = 0;
    bool overflow = __builtin_umull_overflow(mib, 1024 * 1024, &bytes);
    if (overflow) {
        printf("fatal: integer overflow\n");
        exit(1);
    }
    printf("testing %ld MiB\n", mib);

    int* buf = malloc(bytes);
    if (!buf) {
        perror("fatal: malloc failed");
        exit(1);
    }

    int err = mlockall(MCL_CURRENT | MCL_FUTURE);
    if (err != 0) {
        perror("warning: could not lock memory");
    }

    printf("filling\n");
    srand(1);
    const long words = bytes / sizeof(int);
    for (long i = 0; i < words; i++) {
        buf[i] = rand();
    }

    printf("verifying\n");
    srand(1);
    for (long i = 0; i < words; i++) {
        int want = rand();
        if (buf[i] != want) {
            printf("fatal: mismatch at offset %ld: want=0x%08x have=0x%08x\n",
                i * sizeof(int), want, buf[i]);
            exit(2);
        }
    }
    printf("ok\n");
    exit(0);
}

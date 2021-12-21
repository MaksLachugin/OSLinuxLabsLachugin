#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int n = 0;
    double t = 0;

    struct option longopts[] = {
        {.name = "number",
            .has_arg = required_argument,
            .flag = NULL,
            .val = 'n' },
        {.name = "timeout",
            .has_arg = optional_argument,
            .flag = NULL,
            .val = 't' },
        {}
    };
    while (1) {
        int c = getopt_long(argc, argv, "n:t::", longopts, NULL);
        if (c == -1) {
            break;
        }
        switch (c) {
        case 'n':
            n = atoi(optarg);
            break;
        case 't':
            if (optarg) {
                t = atoi(optarg);
		printf("t");
            }
            else {
		printf("---");
                t = 1;
            }
            break;
        }
    }
    if (n < 1 || t < 0 || strcmp(argv[optind - 1], "--") != 0) {
        printf("usage: prntxt -n|--number <N> [-t|--timeout [<T>]] -- <TEXT>\n");
    }
    else {
        int i = 0;
        while (i < n) {
            printf("%s\n", argv[optind]);
            sleep(t);
            i = i + 1;
        }
    }
    return 0;
}

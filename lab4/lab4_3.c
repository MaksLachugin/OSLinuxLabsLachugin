#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
	int n = 0;
	double t = 0;
	char inp[] = "n:t:";
	struct option longopts[] =
	{
		{ "number", required_argument, NULL, 'n'},
		{ "timeout", required_argument, NULL, 't'},
		{}
	};
	while(1)
	{
		int c = getopt_long(argc, argv, inp, longopts, NULL);
		if (c == -1)
		{
			break;
		}
		switch (c)
		{
			case 'n':
				n=atoi(optarg);
				break;
			case 't':
				printf(optarg);
				if (optarg)
				{
					t=atoi(optarg);
				}
				else
				{
					t=1;
				}
				break;
		}
	}
	if ((n>0) && (t>=0) && (strcmp(argv[optind-1], "--") == 0))
	{
		for (int i=0; i<n; i++)
		{
			printf("%s\n",argv[optind]);
			sleep(t);
		}
	}
	else
	{
		printf("usage: prntxt -n|--number <N> [-t|--timeout[<T>]] -- <TEXT>\n");
	}
	return 0;
}

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	int timeout;
	int number;
	struct option longopts[] =
	{
		{
			.name = "number",
			.has_arg = required_argument,
			.flag = NULL,
			.val = 'n'
		},
		{
			.name = "timeout",
			.has_arg = required_argument,
			.flag = NULL,
			.val = 't'
		},
		{
		}
	};
	while (1)
	{
		int c = getopt_long(argc, argv, "n:t:", longopts, NULL);
		if (c == -1)
		{
			break;
		}
		switch (c)
		{
			
			case 'n':
				if (optarg)
				{
					printf("option 'n' with '%s'\n", optarg);
					number = atoi(optarg);
				}
				else
				{
					printf("option 'n' witout argument\n");
				}
				break;
			case 't':
				if (optarg)
				{
					printf("option 't' with '%s'\n", optarg);
					timeout = atoi(optarg);
				}
				else
				{
					timeout = 1;
					printf("option 't' witout argument\n");
				}
				break;
			case '-':
				printf("option 'd'\n");
				break;
			default:
				char temp = c + '0'; 
				printf("%s \n", temp);
				printf(optarg);
				break;
		}
	}
	char str[] = "texter";
	int t=0;
	while (t<number)
	{
		printf("%d %s\n", t, argv[argc-1]);
		sleep(timeout);
		t = t+1;
	}
	return 0;
}

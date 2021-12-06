#include <stdio.h>
#include <getopt.h>
int main(int argc, char *argv[])
{
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
		.has_arg = optional_argument,
		.flag = NULL,
		.val = 't'
		},
		{
		.name = "",
		.has_arg = required_argument,
		.flag = NULL,
		.val = '-'
		},
	};

	while(1) 
	{
		int c = getopt_long(argc, argv, "nt::-", longopts, NULL);
		if (c == -1) 
		{
			break;
		}
	switch (c)
	{
		case 'n':
			printf("-- n -- %d --\n", optarg);
			break;
		
		case 't':
			if (optarg)
			{
				printf("-- t -- %d --\n", optarg);
			} 
			else
			{
				printf("-- t ---\n");
			}
			break;
		
		case '-':
			printf("-- %s --\n", optarg);
			break;
	
	}	
	}
	printf("-- %d --\n", argc);
	printf("Hello World!\n");	
	
	return 0;
}

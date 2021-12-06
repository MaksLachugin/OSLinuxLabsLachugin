#include <getopt.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct option longopts[] =
	{
		{
			.name = "advanced",
			.has_arg = no_argument,
			.flag = NULL,
			.val = 'a'
		},
		{
			.name = "base address",
			.has_arg = required_argument,
			.flag = NULL,
			.val = 'b'
		},
		{
			.name = "cursor",
			.has_arg = required_argument,
			.flag = NULL,
			.val = 'c'
		},
		{
			.name = "debug",
			.has_arg = no_argument,
			.flag = NULL,
			.val = 'd'
		},
		{
		}
	};
	while (1)
	{
		int c = getopt_long(argc, argv, "ab:c::d", longopts, NULL);
		if (c == -1)
		{
			break;
		}
		switch (c)
		{
			case 'a':
				printf("option 'a'\n");
				break;
			case 'b':
				printf("option 'b' with '%s'\n", optarg);
				break;
			case 'c':
				if (optarg)
				{
					printf("option 'c' with '%s'\n", optarg);
				}
				else
				{
					printf("option 'c' witout argument\n");
				}
				break;
			case 'd':
				printf("option 'd'\n");
				break;
		}
	}
	return 0;
}

#include <stdio.h>
#include <unistd.h>
int main()
{
	pid_t pid = fork();
	if (pid == -1)
	{
	  perror("fork");
	  return 1;
	}
	else if (!pid) {
	  while (1)
	  {
	    for (int i = 0; i < 10; i++)
	    {
	      putchar('C'); fflush(stdout);
	   	  usleep(10000 /* us */); 
	    }
	    putchar('\n');
	  }
	}
	
  while (1)
  {
    for (int i = 0; i < 10; i++)
    {
      putchar('P'); fflush(stdout);
   	  usleep(10000 /* us */); 
    }
    putchar('\n');
  }
  
  return 0;
}

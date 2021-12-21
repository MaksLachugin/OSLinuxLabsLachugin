#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>

struct sembuf acquire_sem = {.sem_op = -1 };
struct sembuf release_sem = {.sem_op = 1 };


int main()
{
	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);

	pid_t pid = fork();
	if (pid == -1)
	{
	  perror("fork");
	  return 1;
	}
	else if (!pid) {
	  while (1)
	  {
		if ()
		semop(1, &acquire_sem, 1);
	  
	    for (int i = 0; i < 10; i++)
	    {
	      putchar('C'); fflush(stdout);
	   	  usleep(10000 /* us */); 
	    }
	    putchar('\n');
		semop(1, &release_sem, 1);

	  }
	}
	
  while (1)
  {
	semop(1, &acquire_sem, 1);

    for (int i = 0; i < 10; i++)
    {
      putchar('P'); fflush(stdout);
   	  usleep(10000 /* us */); 
    }
    putchar('\n');
	semop(1, &release_sem, 1);

  }
  
  return 0;
}

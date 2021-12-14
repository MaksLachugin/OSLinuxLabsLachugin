#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{

	pid_t pid = fork();
	if (pid == 0)
	{	
		int fd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, 1);
		execl(argv[1], NULL);
		close(fd);	
		perror("execl");
	}	
	int code;
	pid_t cpid = wait(&code);
	printf("child %d is done with code %d \n", cpid, code);
	
	return 0;
}

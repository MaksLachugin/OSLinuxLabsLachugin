#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
struct sembuf start_sem = {.sem_op = -1 };
struct sembuf finish_sem = {.sem_op = 1 };
int main()
{
    const int sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    semctl(sem_id, 0, SETVAL, 1);
    const pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    else if (!pid) {
        while (1) {
            semop(sem_id, &start_sem, 1);
            for (int i = 0; i < 10; i++) {
                putchar('C');
                fflush(stdout);
                usleep(10000);
            }
            putchar('\n');
            semop(sem_id, &finish_sem, 1);
        }
    }
    while (1) {
        semop(sem_id, &start_sem, 1);
        for (int i = 0; i < 10; i++) {
            putchar('P');
            fflush(stdout);
            usleep(10000);
        }
        putchar('\n');
        semop(sem_id, &finish_sem, 1);
    }
    return 0;
}

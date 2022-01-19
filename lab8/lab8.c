#include <stdio.h>

#include <stdlib.h>
#include <unistd.h> // fork()
#include <sys/shm.h> // shmget(), shmat(), shmdt()
#include <stdatomic.h> // atomic_fetch_add()
#include <sys/wait.h> // wait()
#include <time.h>
#include <sys/msg.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
struct message {
    long mtype;
    pid_t client_id;
    char text[40];
};
sem_t sems[5];
int pids[5];
int main()
{
    key_t msgkey = ftok("msg", 1);
    int msgid = msgget(msgkey, IPC_CREAT | 0666);
    int shmid = shmget(IPC_PRIVATE, sizeof(_Atomic long), 0660);
    _Atomic long* counter = shmat(shmid, NULL, 0);
    *counter = 1;
    shmdt(counter);
    pid_t pid;
    for (int i = 0; i < 5; i++) {
        sem_init(&sems[i], 1, 1);
    }
    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            char str[40];
            _Atomic long* counter = shmat(shmid, NULL, 0);
            long id = atomic_fetch_add(counter, 1);
            pids[id] = getpid();
            shmdt(counter);
            srand(id);
            struct message message = {
                .mtype = 1,
                .client_id = id
            };
            sprintf(str, "%d %s", id, "meditates");
            strncpy(message.text, str, 40);
            msgsnd(msgid, &message, sizeof(pid_t) + 40, 0);
            while (1) {
                int fL = id - 1;
                int sL = id - 2;
                if (sL < 0) {
                    sL = 4;
                }
                int mTime = rand() % 10;
                clock_t end_t;
                clock_t start_t = clock();
                do {
                    end_t = clock();
                } while (((double)(end_t - start_t) / CLOCKS_PER_SEC - mTime) <= 1e-10);
                sprintf(message.text, "%d %s", id, "starving");
                msgsnd(msgid, &message, sizeof(pid_t) + 40, 0);
                sem_wait(&sems[fL]);
                sem_wait(&sems[sL]);
                sprintf(message.text, "%d %s", id, "eating");
                msgsnd(msgid, &message, sizeof(pid_t) + 40, 0);
                mTime = rand() % 10;
                sleep(mTime);
                sprintf(str, "%d %s", id, "meditates");
                strncpy(message.text, str, 40);
                msgsnd(msgid, &message, sizeof(pid_t) + 40, 0);
                sem_post(&sems[sL]);
                sem_post(&sems[fL]);
            }
            return 0;
        }
    }
    if (pid != 0) {
        while (1) {
            struct message m = {};
            int num = msgrcv(msgid, &m, sizeof(pid_t) + 40, 1, 0);
            if (num < 0) {
                perror("msgrcv");
            }
            else {
                printf("philosohper %.*s \n", num, m.text);
            }
        }
    }
    return 0;
}

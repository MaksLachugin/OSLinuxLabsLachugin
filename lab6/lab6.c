#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h> // poll
#include <string.h> // strsignal
#include <fcntl.h> // open
int main(int argc, char* argv[])
{
    char* file = "reqests";
    int code = 0;
    sigset_t sig;
    sigemptyset(&sig);
    sigaddset(&sig, SIGINT);
    sigaddset(&sig, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sig, NULL);
    pid_t pid = fork();
    if (pid == 0) {
        int parent = getppid();
        while (1) {
            sleep(3);
            kill(parent, SIGUSR1);
        }
    }
    else if (pid > 0) {
        mkfifo(file, 0666);
        int fd = open(file, O_RDONLY | O_NONBLOCK);
        int sigfd = signalfd(-1, &sig, 0);
        struct pollfd pfd[] = {
            {.fd = sigfd, .events = POLLIN },
            {.fd = fd, .events = POLLIN }
        };
        while (1) {
            poll(pfd, 2, -1);
            if ((pfd[0].revents & POLLIN) != 0) {
                struct signalfd_siginfo siginfo = {};
                read(sigfd, &siginfo, sizeof(siginfo));
                if (siginfo.ssi_signo == SIGINT) {
                    break;
                }
                else if (siginfo.ssi_signo == SIGUSR1) {
                    printf("CUSTOM SIGNAL= %s\n",
                        strsignal(siginfo.ssi_signo));
                }
            }
            if ((pfd[1].revents & POLLIN) != 0) // именнованный канал
            {
                char buf[16];
                int n = read(fd, buf, sizeof(buf));
                if (n != 0) {
                    printf("%.*s", n, buf);
                }
            }
        }
        kill(0, SIGTERM);
        pid_t child = wait(&code);
        printf("child process code = %d \n", code);
        close(fd);
        unlink(file);
    }
    return 0;
}

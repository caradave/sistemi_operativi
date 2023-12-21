#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigManager(int sig){
    if(sig == SIGUSR1){
        printf("segnale padre\n");
    }else if(sig == SIGUSR2){
        printf("segnale figlio\n");
    }
}

int main(void){
    pid_t pid;

    if(signal(SIGUSR1, sigManager) == SIG_ERR){
        printf("signal handler error\n");
        return (1);
    }

    if(signal(SIGUSR2, sigManager) == SIG_ERR){
        printf("signal handler error\n");
        return (1);
    }

    pid = fork();

    

    for(int i=0; i<5; i++){
        if(pid != 0){
            pause();
            sleep(2);
            kill(pid, SIGUSR1);
        }else{
            sleep(2);
            kill(getppid(), SIGUSR2);
            pause();
        }
    }

    return 0;
}
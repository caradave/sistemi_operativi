#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>

#define PID_STRING_SIZE 10

void sigManager(int sig);
void inputChild(int myPipe[]);
void outputChild(int myPipe[]);


int main(void){
    int myPipe[2];
    char pid1S[PID_STRING_SIZE], pid2S[PID_STRING_SIZE];
    pid_t pid1, pid2;
    size_t size = PID_STRING_SIZE;


    if(signal(SIGUSR1, sigManager) == SIG_ERR){
        printf("signal handler error\n");
        return (1);
    }

    if(signal(SIGUSR2, sigManager) == SIG_ERR){
        printf("signal handler error\n");
        return (1);
    }

    setbuf (stdout, 0);

    pipe(myPipe);

    pid1 = fork();

    if(pid1 != 0){
        pid2 = fork();
        if(pid2 != 0){
            close(myPipe[0]);
            printf("processo padre che ha chiuso la pipe in lettura e attende i figli\n");
            fprintf(stdout, "pid dei figli: %d %d\n", pid1, pid2);

            sprintf(pid1S, "%d", pid1);
            sprintf(pid2S, "%d", pid2);
            write(myPipe[1], pid1S, size);
            write(myPipe[1], pid2S, size);

            kill(pid1, SIGUSR1);
            wait((int *) pid1);
            kill(pid2, SIGUSR2);
            wait((int *) pid2);
            fprintf(stdout, "termine del programma\n");
        }else{
            pause();
            fprintf(stdout, "%s","child output\n");
            outputChild(myPipe);
            exit(0);
        }
    }else{
        pause();
        fprintf(stdout, "%s", "child input\n");
        inputChild(myPipe);
        exit(0);
    }
}


void sigManager(int sig){
    return;
}

void inputChild(int myPipe[]){
    int n1=0, n2=0;
    char pid1S[PID_STRING_SIZE], pid2S[PID_STRING_SIZE], str[50];
    pid_t selfPid = getpid();
    size_t size = PID_STRING_SIZE, sizeStr = 50;

    n1 = read(myPipe[0], pid1S, size);
    n2 = read(myPipe[0], pid2S, size);

    if(n1 <= 0 || n2 <= 0){
        printf("impossibile leggere i pid dalla pipe");
        exit(2);
    }

    close(myPipe[0]);

    fprintf(stdout, "%s", "inserire una stringa di massimo 50 caratteri: ");
    scanf("%s", str);
    
    write(myPipe[1], pid1S, size);
    write(myPipe[1], pid2S, size);

    //lseek(myPipe[1], 2*PID_STRING_SIZE, SEEK_SET);
    write(myPipe[1], str, sizeStr);

    if(atoi(pid1S) == selfPid)
        kill(atoi(pid2S), SIGUSR2);
    else
        kill(atoi(pid1S), SIGUSR2);

    return;
}

void outputChild(int myPipe[]){
    int n1=0, n2=0, i=0;
    char pid1S[PID_STRING_SIZE], pid2S[PID_STRING_SIZE], str[50];
    size_t size = PID_STRING_SIZE, sizeStr = 50;


    n1 = read(myPipe[0], pid1S, size);
    n2 = read(myPipe[0], pid2S, size);

    fprintf(stdout, "pid trovati nella pipe: %s %s, n1 = %d, n2 = %d\n", pid1S, pid2S, n1, n2);

    
    read(myPipe[0], str, sizeStr);
    while(i<50 && str[i]!= NULL){
        fprintf(stdout, "%c", toupper(str[i]));
        i++;
    }
    fprintf(stdout, "%c", '\n');

    return;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

#define PID_STRING_SIZE 10

void sigManager(int sig);
void printPidPipe(int myPipe[], char pid1S[], char pid2S[]);
int inputChild(int myPipe[], int check);
int outputChild(int myPipe[], int check);
int checkEnd(char str[]);


int main(void){
    int myPipe[2], check = 1;
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
            while(check>0){
                pause();
                check = outputChild(myPipe, check);
                if(check > 0)
                    kill(check, SIGUSR1);
            }
        }
    }else{
        while(check>0){
            pause();
            check = inputChild(myPipe, check);
            if(check > 0)
                kill(check, SIGUSR2);
        }
    }
}


void sigManager(int sig){
    return;
}

int inputChild(int myPipe[], int check){
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

    fprintf(stdout, "%s", "inserire una stringa di massimo 50 caratteri: ");
    scanf("%s", str);
    
    printPidPipe(myPipe, pid1S, pid2S);

    write(myPipe[1], str, sizeStr);

    if(checkEnd(str) < 0){
        return -1;
    }

    if(atoi(pid1S) == selfPid)
        return atoi(pid2S);
    else
        return atoi(pid1S);

}

int outputChild(int myPipe[], int check){
    int n1=0, n2=0, i=0;
    char pid1S[PID_STRING_SIZE], pid2S[PID_STRING_SIZE], str[50];
    pid_t selfPid = getpid();
    size_t size = PID_STRING_SIZE, sizeStr = 50;


    n1 = read(myPipe[0], pid1S, size);
    n2 = read(myPipe[0], pid2S, size);

    read(myPipe[0], str, sizeStr);
    while(i<50 && str[i]!= NULL){
        fprintf(stdout, "%c", toupper(str[i]));
        i++;
    }
    fprintf(stdout, "%c", '\n');

    printPidPipe(myPipe, pid1S, pid2S);

    if(checkEnd(str) < 0){
        return -1;
    }

    if(atoi(pid1S) == selfPid)
        return atoi(pid2S);
    else
        return atoi(pid1S);

}

void printPidPipe(int myPipe[], char pid1S[], char pid2S[]){
    size_t size = PID_STRING_SIZE;

    write(myPipe[1], pid1S, size);
    write(myPipe[1], pid2S, size);
}

int checkEnd(char str[]){
    int len = strlen(str);

    if(tolower(str[len-1]) == 'd' && tolower(str[len-2]) == 'n' && tolower(str[len-3]) == 'e')
        return -1;
    return 1;
}
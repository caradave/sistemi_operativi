/*
Scrivere un programma che mediante l'utilizzo di segnali
sincronizzi due processi (un padre e un figlio) in modo che
stampino alternativamente uno specifico messaggio.
Il seguente e' un esempio di output:

Child Woke-up
Father Woke-up
Child Woke-up
Father Woke-up
Child Woke-up
Father Woke-up
Child Woke-up
Father Woke-up
...

Inserire sleep opportune per evitare corse critiche.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char readFile(int inF);

int main(void){
    int pipefd[2];
    char check, zero = '0', uno = '1', i=0;

    // pipe(pipefd);
    // write(pipefd[1], &uno, sizeof(char));

    pid_t pid = fork();

    while(i<5){
        // processo figlio

        if(pid == 0){
            if(readFile(pipefd[0]) == uno){
                printf("figlio\n");
                write(pipefd[1], &zero, sizeof(char));
                i++;
            }
            wait((int *) 1);
        }else{            
            if(readFile(pipefd[0]) == zero){
                printf("padre\n");
                write(pipefd[1], &uno, sizeof(char));
                i++;
            }
            wait((int *) 1);
        }
    }



    return 0;
}

char readFile(int inF){
    char check, lastCheck;
    int loop = 1;
    while(loop == 1){
        if(read(inF, &check, sizeof(char)) >= sizeof(char)){
            lastCheck = check;
        }else{
            loop = 0;
        }
    }
    printf("%c\n", lastCheck);
    return lastCheck;
}

/*
pos 0 figlio deve leggere in pos 0 e scrive in pos 1
pos 1 padre deve leggere in pos 1 e scrivere in pos 2
pos 2 figlio deve leggere in pos 2 e scrivere 1 bit in pos 3
pos 3 padre deve leggere in pos 3 e scrivere in pos 4
*/
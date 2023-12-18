#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int t, n;
    pid_t pid1, pid2;

    // controllo sul numero di elementi passati
    if(argc !=3){
        printf("passato un numero errato di argomenti\n");
        return(-1);
    }


    // controllo sulla conversione in intero
    if((n = atoi(argv[1])) == 0 || (t = atoi(argv[2])) == 0){
        printf("inserire dei valori numerici");
        return(-2);
    }

    // inizio delle fork
    for(int i=0; i<n; i++){
		pid1 = fork();
		if (pid1 != 0){
			pid2 = fork();
			if (pid2 != 0){
				printf("padre che termina\n");
				exit(0);
			}
		}
    }
    printf("figlio che attende\n");
    sleep(t);
    printf("figlio che termina\n");
    return 0;
}
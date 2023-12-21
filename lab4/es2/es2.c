#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int manipulateFile(int inf, int pipe[], int pos);

int main(int argc, char* argv[]){
    int inf, myPipe[2];
    int *n1 = malloc(sizeof(int)), *n2 = malloc(sizeof(int));

    char *buf = malloc(3*sizeof(char));
    pid_t pid;
    
    if(argc != 2){
        printf("numero errato di argomenti");
        return(-1);
    }

    inf = open(argv[1], O_RDONLY);
    if(inf < 0){
        printf("impossibile aprire il file");
        return(-2);
    }

    pipe(myPipe);

    while(read(inf, buf, sizeof(char))){
        
        int num = atoi(buf);
        printf("%d\n", num);
        write(myPipe[1], num, sizeof(int));
    }

    printf("\n\n\n");
    for(int i=0; i<12; i++){
        for(int j=0; j<11; j++){
            pid = fork();
            if(pid == 0){
                lseek(myPipe[0], j*sizeof(int), SEEK_SET);
                read(myPipe[0], n1, sizeof(int));
                read(myPipe[0], n2, sizeof(int));
    if(n1>n2){
        printf("n1>n2");
    }
    printf("%d %d", *n1, *n2);
                exit(0);
            }
            wait(pid);
        }
    }

    close(inf);
    free(buf);
    return 0;
}

/*
int manipulateFile(int inf, int pipe[], int pos){
    int *n1 = malloc(sizeof(int)), *n2 = malloc(sizeof(int));
    
    lseek(pipe[0], pos*sizeof(int), SEEK_SET);
    read(pipe[0], n1, sizeof(int));
    read(pipe[0], n2, sizeof(int));
    if(n1>n2){
        printf("n1>n2");
    }
    printf("%d %d", *n1, *n2);
}
*/
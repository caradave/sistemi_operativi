#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int inf, myPipe[2];
    char *buf = malloc(3*sizeof(char));
    
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

    while(read(inf, buf, sizeof(char)>0)){
        printf("%c", *buf);
    }


    close(inf);
    free(buf);
    return 0;
}


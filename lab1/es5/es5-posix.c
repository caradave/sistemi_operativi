#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int inf, outf, nr;
    char car;

    if(argc != 3){
        printf("fornito numero di argomenti errato");
        return(-1);
    }

    inf = open(argv[1], O_RDONLY);
    outf = open(argv[2], O_WRONLY);

    if (inf < 1 || outf < 1){
        printf("impossibile aprire i file");
        return -2;
    }

    while((nr = read(inf, &car, sizeof(char))) > 0){
        write(outf, &car, nr); 
    }

    close(inf);
    close(outf);

    return (0);
}
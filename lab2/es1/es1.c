#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>


// scrivere un programma che riceva sulla riga 
// di comando il path assoluto o relativo di un albero
// di direttori 

// visualizzare *ricorsivamente* il contenuro di 
// tale albero

void explore_tree(int i, char path[]);

int main(int argc, char *argv[]){
    struct dirent *dirdp;
    struct stat statbuf;
    DIR *dp;
    
    if(argc != 2){
        printf("wrong number of argument\n");
        exit(1);
    }

    if (lstat(argv[1], &statbuf)<0){
        printf("invalid path or error in path\n");
        exit(1);
    }

    if(S_ISDIR(statbuf.st_mode) != 1){
        if(S_ISDIR(statbuf.st_mode) == 0){
            printf("expected a tree of direcotry, recived a file\n");
        }else{
            printf("null path\n");
        }
        exit(1);
    }

    if((dp = opendir(argv[1])) == NULL){
        printf("cannot open the directory\n");
        exit(0);
    }

    if(dp == NULL){
        printf("bestemmia");
    }

    char string[500];
    strcpy(string, argv[1]);

    explore_tree(0, string);

    closedir(dp);
    free(dirdp);

    return 0;
}

void explore_tree(int i, char path[]){
    // apro il path della cartella
    DIR *dp = opendir(path);

    // struct utili per l'esplorazione
    struct dirent *dir;
    struct stat statbuf;

    // stringa per scrivere il nuovo path
    char new_path[500];

    // finchè l'esporazione non è completata vai avanti
    while((dir = readdir(dp)) != NULL){
        // costruzione del path completo del file/cartella
        strcpy(new_path, "");
        strcpy(new_path, path);
        strcat(new_path, "/");
        strcat(new_path, dir->d_name);


        lstat(new_path, &statbuf);

        for(int k=0; k<i; k++){
            printf(" ");
        }

        printf("%s\n", dir->d_name);

        if(S_ISDIR(statbuf.st_mode) != 0 && strcmp(".", dir->d_name) != 0 && strcmp("..", dir->d_name) != 0){
            explore_tree(i+=2, new_path);
        }   
    }
    
    closedir(dp);
    
    return;

}
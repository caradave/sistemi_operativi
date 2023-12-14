#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]){
    FILE *infile;
    FILE *outfile;


    if(argc == 3){
        infile = fopen(argv[1], "r");
        outfile = fopen(argv[2], "w");

        if(!infile || !outfile){
            printf("file invalidi");
            exit(0);
        }


        while(!feof(infile)){
            char buf = fgetc(infile);
            fputc(buf, outfile);
        }
    }


    return (0);
}
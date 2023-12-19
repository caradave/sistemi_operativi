#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void exec_command(char string[60]);

int main(void){
    pid_t pid = fork();
    FILE *inf = fopen("comandi.txt", O_RDONLY);
    char command[60];


    while(fgets(command, 50, inf)>0){
        system(command);
    }

    return 0;
}


void exec_command(char string[60]){
    system(string);
}
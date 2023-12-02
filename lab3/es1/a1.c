#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    int i;
    for (i=1; i<=2; i++) {
        if (!fork ())
            printf ("%d\n", i);
        }
    printf ("%d\n", i);

    return 0;
}

/*
per i valori da 1 a 2
    se sono nel padre
        stampa il valore 
*/
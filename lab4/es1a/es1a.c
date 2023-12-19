/*
A.
Scrivere un programma C in grado di leggere dei valori
interi e stampare su standard output
fprintf (stdout, ...);
i numeri pari e su standard error (stderr)
fprintf (stderr, ...);
i numeri dispari.
Il programma termini una volta introdotto il valore nullo.

Si utilizzi la ridirezione per:
- leggere gli interi dal file "inFile.txt",
  invece che da standard input
- scrivere i valori pari su file "pariFile.txt",
  invece che su standard output
- scrivere i valori dispari su file "dispariFile.txt",
  invece che su standard error.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){
    char input[10];

    setbuf(stdout, 0);
    setbuf(stderr, 0);

    while(scanf("%s", input) > 0){
        if(atoi(input)%2 == 0)
            fprintf(stdout, "stdout: %s\n", input);
        else
            fprintf(stderr, "stderr: %s\n", input);
    }

    return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void binary(int n);

int main(int argc, char *argv[]){
    int n=0;

    if(argc != 2){
        printf("passato un numero errato di argomenti");
        exit(-1);
    }

    n = atoi(argv[1]); 
    binary(n);


    return 0;
}


void binary(int n){
    for(int i=0; i<n; i++){
        printf("%d\n", i);
    }

}
*/

#include <stdio.h>

void stampa_numeri_binari(int num_bit) {
    if (num_bit <= 0) {
        printf("Il numero di bit deve essere maggiore di zero.\n");
        return;
    }

    for (int i = 0; i < (1 << num_bit); i++) {
        for (int j = num_bit - 1; j >= 0; j--) {
            printf("%d", (i >> j) & 1);
        }
        printf("\n");
    }
}

int main() {
    // Esempio di utilizzo
    int numero_di_bit = 3;
    stampa_numeri_binari(numero_di_bit);

    return 0;
}
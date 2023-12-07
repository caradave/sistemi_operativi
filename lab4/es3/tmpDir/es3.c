/*
Un file contiene delle stringhe logicamente raggruppate in
insiemi distinti.
Ogni insieme di stringhe indica un comando Unix/Linux e i
relativi parametri.
Ogni insieme e' terminato dalla stringa "end".
Il seguente e' un esempio corretto di file:

ls -laR end
less mioFile.c end
mkdir tmpDir end
cp mioFile.c tmpDir end

Si osservi che, se si preferisce, si puo' supporre la stringa
"end" non sia presente nel file e sia invece il carattere di
fine riga '\n' a indicare la fine delle stringhe associate
a un certo comando.

Scrivere un programma che, ricevuto il nome del file sulla
riga di comando, esegua i comandi Unix/linux indicati
nel file utilizzando:
* la system call system, eseguendo un comando dopo l'altro
* la system call exec eseguendo un comando ogni 3 secondi.
  (e' facolta' decidere quale versione della exec
  utilizzare).
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void exec_command(char **command, int i);

int main(void){
    FILE *infile = fopen("comandi.txt", "r");
    char **comandi = malloc(10*(sizeof(char *)));
    int i = 0;

    while(!feof(infile)){
        comandi[i] = malloc(50*sizeof(char));
        fgets(comandi[i], 50, infile);
        i++;
    }

    for(int k=0; k<i; k++){
        if(fork()){
            exec_command(comandi, k);
            exit(0);            
        }
        sleep(2);
    }

    return 0;
}

void exec_command(char **command, int i){
    printf("%s\n", command[i]);
    system(command[i]);
}
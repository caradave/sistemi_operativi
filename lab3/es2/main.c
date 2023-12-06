#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/*
Esercizio 02
System call fork e comandi di shell per processi
------------------------------------------------

Un programma riceve due valori interi sulla riga di comando,
denominati n e t.
Il programma (processo padre) deve eseguire 2 figli e terminare.
Ciascun figlio deve eseguire a sua volta due figli e terminare.
Il procedimento deve andare avanti sino a quando sono in esecuzione
i 2^n processi sulle foglie dell'albero.
Questi ultimi aspettano per t secondi e visualizzano (a video)
un messaggio di terminazione.
Si noti che ogni processo (ad albero) ne esegue altri due.
Solo quelli sulle foglie dell'albero dormono e visualizzano un
messaggio.
Qual e' l'ordine di terminazione dei processi?
E' sempre lo stesso?
Come si possono riconoscere (ppid)?

Una volta eseguito il programma:
A. cercare il pid dei vari processi con il comando ps
   - dalla stessa shell
   - da un'altra shell
B. terminare l'esecuzione di alcuni processi
   con il comando kill eseguito
   - dalla stessa shell
   - da un'altra shell
*/
int main(int argc, char *argv[]){
    int n, t;


    if(argc != 3){
        printf("numero di argmoenti errato");
        return -1;
    }

    if((n = atoi(argv[1])) == 0 || (t = atoi(argv[2])) == 0){
        printf("impossibile convertire in numerico");
        return -1;
    }

    printf("%d %d\n", n, t);

    for(int i=0; i < n; i++){
        if (!fork())
            wait(t);
        if(!fork())
            wait(t);
    }
    printf("fine programma");


    return 0;
}
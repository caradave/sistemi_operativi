/*
Premessa numero 1.
L'algoritmo di ordinamento per scambio (exchange-sort o
bubble-sort) ordina un vettore mediante il confronto di
elementi contigui.
La seguente e' una possibile implementazione (con ordinamento
del vettore v di n elementi):

for (i=0; i<n-1; i++) {
  for (j=0; j<n-1-i; j++) {
    if (v[j] > v[j+1]) {
       val = v[j];
       v[j] = v[j+1];
       v[j+1] = val;
    }
  }
}

Premessa numero 2.
Un  file binario puo' essere scritto (funzione UNIX write)
e letto (funzione unix read) in maniera casuale utilizzando
la funzione lseek.

Ad esempio, il programma
lab05ex02.c
una volta ricevuto il nome di un file sulla riga di comando,
- scrive nel file il vettore vet di 12 elementi
- rilegge il file a partire dall'ultima riga.

Specifiche dell'esercizio.
Si implementi in maniera *concorrente* e *multi-processo*
l'algortimo di bubble-sort.
L'algoritmo, utilizzando le system call fork e wait e
condividendo dati su file (i.e., leggendo e scrivendo dati sullo
stesso file) deve effettuare l'ordinamento del file stesso.

Il programma (il padre):
- riceve sulla riga di comando il nome di un file contenente
  un numero predefinito n di interi.
- a ogni iterazione del ciclo esterno "simula" l'azione
  del ciclo interno generando (n-1-i) processi figlio.

Ognuno dei figli
  - legge due elementi adiacenti nel file
  - ne effettua lo scambio qualora necessario
  - li riscrive su file
  - si sincronizza con gli altri processi figli per
    generare l'effetto globale di ordinamento (i.e.,
    a ogni iterazione del ciclo esterno il valore
    maggiore tra quelli rimanenti, viene spostato in
    fondo al file)
  - termina.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    
    if(argc != 2){
        printf("passato il numero sbagliato di argomenti");
        return -1;
    }
    


    return 0;
}
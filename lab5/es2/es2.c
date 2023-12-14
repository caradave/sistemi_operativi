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
#include <fcntl.h>

#define N 12

int main(int argc, char *argv[]){
  int array[12] = {12, 4, 5, 7, 4, 6, 9, 0, 33, 23, 5, 4};
  int outf, inf, c1, c2, v1, v2;

  if(argc != 2){
    printf("passato il numero sbagliato di argomenti\n");
      return -1;
  }

  if((outf = creat(argv[1], 0666) == -1)){
    printf("impossibile aprire il file\n");
    exit(-1);
  }

  printf("dati contenuti nel file: ");
  for(int i=0; i<12; i++){
    write(outf, &array[i], sizeof(int));
    printf("%d ", array[i]);
  }

  close(outf);


  // sto aprendo un file con un intero con permesso solo di read
  inf = open(argv[1], O_RDONLY);
  if(inf == -1){
    printf("impossibile aprire il file");
    exit(-1);
  }

  printf("\nvettore pre ordinamento: ");
  for(int i=0; i<12; i++){
    printf("%d ", array[i]);
    write(inf, "%d\n", array[i]);
  }
  printf("\n");


  fprintf (stdout, "SEQUENTIAL ordering ...\n");
  for (int i=0; i<N-1; i++) {
    for (int j=0; j<N-1-i; j++) {
      lseek (inf, j*sizeof (int), SEEK_SET);
      c1 = read (inf, &v1, sizeof (int));
      //lseek (fd, (j+1)*sizeof (int), SEEK_SET);
      c2 = read (inf, &v2, sizeof (int));
      if (c1<=0 || c2<=0){
        fprintf (stderr, "Error reading file\n");
        exit (-1);
      }
      if (v1 > v2) {
        lseek (inf, j*sizeof (int), SEEK_SET);
        c1 = write (inf, &v2, sizeof (int));
        //lseek (fd, (j+1)*sizeof (int), SEEK_SET);
        c2 = write (inf, &v1, sizeof (int));
      }
    }
  }

  close(inf);

  inf = open (argv[1], O_RDONLY);
  if (inf == -1){
    fprintf(stderr, "Cannot open file %s\n", argv[1]);
    exit(-1);
  }

  fprintf (stdout, "File after  ordering    : ");
  for (int i=0; i<N; i++) {
    lseek (inf, i*sizeof (int), SEEK_SET);
    int c = read (inf, &v1, sizeof (int));
    if (c <= 0){
      fprintf (stderr, "Error reading file\n");
      exit (-1);
    }
    fprintf (stdout, "%2d ", v1);
  }
  fprintf (stdout, "\n");

  close (inf);

  return 0;
}
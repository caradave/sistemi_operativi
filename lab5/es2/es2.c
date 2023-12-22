/*
grazie chat gpt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MESSAGE_SIZE 50

int main() {
    int pipe_fd_parent_to_child[2];
    int pipe_fd_child_to_parent[2];

    // Creazione delle pipe
    if (pipe(pipe_fd_parent_to_child) == -1 || pipe(pipe_fd_child_to_parent) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        // Processo padre
        close(pipe_fd_parent_to_child[0]); // Chiude la lettura dalla pipe padre-figlio
        close(pipe_fd_child_to_parent[1]); // Chiude la scrittura dalla pipe figlio-padre

        int message_count = 10; // Numero di messaggi alternati

        for (int i = 0; i < message_count; ++i) {
            // Invia messaggio al figlio
            char message[MESSAGE_SIZE];
            snprintf(message, MESSAGE_SIZE, "I'm the father (PID=%d)\n", getpid());
            write(pipe_fd_parent_to_child[1], message, MESSAGE_SIZE);

            // Legge la risposta dal figlio
            read(pipe_fd_child_to_parent[0], message, MESSAGE_SIZE);
            printf("%s", message);
        }

        // Invia un messaggio di terminazione al figlio
        char terminate_message[] = "Terminate";
        write(pipe_fd_parent_to_child[1], terminate_message, sizeof(terminate_message));

        // Chiude le pipe
        close(pipe_fd_parent_to_child[1]);
        close(pipe_fd_child_to_parent[0]);
    } else {
        // Processo figlio
        close(pipe_fd_parent_to_child[1]); // Chiude la scrittura dalla pipe padre-figlio
        close(pipe_fd_child_to_parent[0]); // Chiude la lettura dalla pipe figlio-padre

        while (1) {
            // Legge il messaggio dal padre
            char message[MESSAGE_SIZE];
            read(pipe_fd_parent_to_child[0], message, MESSAGE_SIZE);

            // Verifica se è il messaggio di terminazione
            if (strncmp(message, "Terminate", sizeof("Terminate")) == 0) {
                break;
            }

            printf("%s", message);

            // Invia un messaggio di risposta al padre
            snprintf(message, MESSAGE_SIZE, "I'm the child  (PID=%d)\n", getpid());
            write(pipe_fd_child_to_parent[1], message, MESSAGE_SIZE);
        }

        // Chiude le pipe
        close(pipe_fd_parent_to_child[0]);
        close(pipe_fd_child_to_parent[1]);
    }

    return 0;
}

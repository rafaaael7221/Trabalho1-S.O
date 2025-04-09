#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2]; // fd[0] para leitura, fd[1] para escrita
    pid_t pid;
    char mensagem[] = "Olá do processo pai!";
    char buffer[100];

    // Criar o pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork(); // Criar processo filho

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid > 0) {
        // Processo pai
        close(fd[0]); // Fecha o lado de leitura
        write(fd[1], mensagem, strlen(mensagem) + 1); // Escreve no pipe
        close(fd[1]); // Fecha o lado de escrita
    } else {
        // Processo filho
        close(fd[1]); // Fecha o lado de escrita
        read(fd[0], buffer, sizeof(buffer)); // Lê do pipe
        printf("Filho recebeu: %s\n", buffer);
        close(fd[0]); // Fecha o lado de leitura
    }

    return 0;
}
















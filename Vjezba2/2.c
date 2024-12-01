#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void create_processes(int num_processes) {
    for (int i = 1; i <= num_processes; i++) {
        printf("Roditelj #%d\n", i);
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork error");
            exit(1);
        } else if (pid == 0) {
            printf("Dijete #%d\n", i); 
            exit(0); 
        } else {
            wait(NULL);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Upotreba: %s <broj_procesa>\n", argv[0]);
        exit(1);
    }

    int num_processes = atoi(argv[1]);
    if (num_processes <= 0) {
        printf("Broj procesa mora biti pozitivan cijeli broj.\n");
        exit(1);
    }

    setbuf(stdout, NULL);

    create_processes(num_processes);

    return 0;
}

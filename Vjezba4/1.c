#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Za funkciju wait()

// Globalna varijabla zbroj
int zbroj = 0;

void stvaranjeProcesa(int brProcesa) 
{
    for (int i = 0; i < brProcesa; i++) 
    {
        pid_t pid = fork();
        if (pid < 0) 
        {
            perror("Greška pri stvaranju procesa");
            exit(1); // Završiti program u slučaju greške
        }

        if (pid == 0) 
        { 
            // Kod djeteta
            zbroj += 1; // Uvećavanje globalne varijable unutar djeteta
            //printf("Dijete PID: %d, zbroj = %d\n", getpid(), zbroj);
            exit(0); // Dijete završava
        }
    }

    // Roditelj čeka da sva djeca završe
    for (int i = 0; i < brProcesa; i++) 
    {
        wait(NULL); // Čeka završetak jednog djeteta
    }
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Upotreba: %s <broj procesa>\n", argv[0]);
        return 1;
    }

    int brojProcesa = atoi(argv[1]);

    if (brojProcesa <= 0) 
    {
        printf("Broj procesa mora biti veći od 0!\n");
        return 1;
    }

    stvaranjeProcesa(brojProcesa);

    // Ispis globalne varijable zbroj u roditeljskom procesu
    printf("Roditelj PID: %d, konačna vrijednost zbroja = %d\n", getpid(), zbroj);

    return 0;
}

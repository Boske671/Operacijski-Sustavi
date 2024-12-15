#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Globalna varijabla zbroj
int zbroj = 0;
// Funkcija koju izvršava svaka dretva
void* povecajZbroj(void* arg) 
{
    zbroj += 1; // Povećavanje globalne varijable
    pthread_exit(NULL);
}

int stvaranjeThreads(int brThreads)
{


    pthread_t dretve[brThreads];

    // Stvaranje dretvi
    for (int i = 0; i < brThreads; i++) 
    {
        if (pthread_create(&dretve[i], NULL, povecajZbroj, NULL) != 0) 
        {
            perror("Greška pri stvaranju dretve");
            return 1;
        }
        //printf("Unutar thread-a! - Broj thread-a: %d.\n", i + 1);
    }

    // Čekanje da sve dretve završe
    for (int i = 0; i < brThreads; i++) 
    {
        pthread_join(dretve[i], NULL);
    }

    return 0;
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Upotreba: %s <broj dretvi>\n", argv[0]);
        return 1;
    }

    int brojDretvi = atoi(argv[1]);
    if (brojDretvi <= 0) 
    {
        fprintf(stderr, "Broj dretvi mora biti veći od 0.\n");
        return 1;
    }


    stvaranjeThreads(brojDretvi);

    // Ispis konačne vrijednosti zbroja
    printf("Konačna vrijednost zbroja: %d\n", zbroj);

    return 0;
}


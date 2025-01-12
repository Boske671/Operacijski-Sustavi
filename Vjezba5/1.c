#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mutex;
int polje[100] = { 0 };
int brThreads = 100;

int RandomBroj(int min, int max)
{
    int randomNumber = min + rand() % (max - min + 1);
    return randomNumber;
}

void kasnjenje(int min, int max)
{
    int randomNumber = RandomBroj(min, max);
    sleep(randomNumber);
}

void* korisnikCheckIn(void* arg) 
{
    pthread_mutex_lock(&mutex);
    int korisnikID = *(int*)arg;
    printf("Spajanje na Microsoft cloud sustav!\n");
    //kasnjenje(1, 5);

    while (1)
    {
        printf("Korisnik %d dohvaća slobodno sjedalo...\n", korisnikID);
        //kasnjenje(1, 3); 
        int brojSjedala = RandomBroj(0, 99);
        int prihvacaLiPutnik = RandomBroj(1, 2);
        if (polje[brojSjedala] == 0) // AKO NIJE ZAUZETO
        {
            printf("Korisniku je predloženo slobodno mjesto!\n");
            if (prihvacaLiPutnik % 2 == 0) //PRIHVACA PUTNIK 
            {
                printf("Korisnik '%d' PRIHVAĆA slobodno mjesto broj '%d'.\n", korisnikID, brojSjedala);
                polje[brojSjedala] = 1;
                break;
            }
            else 
            {
                 printf("Korisnik '%d' ODBIJA slobodno mjesto broj '%d'.\n", korisnikID, brojSjedala);
            }
        }
        else 
        {
            printf("Korisniku %d je predloženo zauzeto mjesto!\n", korisnikID);
        }
    }
    //kasnjenje(1, 2);
    printf("Korisnik %d završava check-in.\n", korisnikID);
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[]) 
{
    pthread_mutex_init(&mutex, NULL);
    srand(time(NULL));

    pthread_t dretve[brThreads];

    // Stvaranje dretvi
    for (int i = 0; i < brThreads; i++) 
    {
        int* korisnikID = malloc(sizeof(int));
        *korisnikID = i + 1;
        if (pthread_create(&dretve[i], NULL, korisnikCheckIn, korisnikID) != 0) //nit, atribut, funckija, parametar za funkciju
        {
            perror("Greška pri stvaranju dretve");
            return 1;
        }
    }

    // Čekanje da sve dretve završe
    for (int i = 0; i < brThreads; i++)
    {
        pthread_join(dretve[i], NULL);
    }
    
    int brojac = 0;
    int polje2[100] = { 0 };
    for (int i = 0; i < brThreads; i++)
    {
        printf("%d. Sjedalo: %d \n", i + 1, polje[i]);
        if(polje[i] == 0)
		{
		polje2[brojac] = (i + 1);
		brojac++;
		}
		
    }


	printf("Broj ne zauzetih mjesta: %d\n", brojac);
	printf("Ne zauzeta mjesta: ");
	for(int i = 0; i < brojac; i++)
	{
		printf("%d ", polje2[i]);
	}
	printf("\n");


    return 0;
}


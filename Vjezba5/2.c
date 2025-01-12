#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h> 


int brJela;
pthread_mutex_t mutex;
//: čokolada, čevapi, janjetina, štrukle, grah, keksi, kelj, jabuka. 
//        0       1       2         3       4     5     6       7  
int jelaNaStolu[8] = { 0 }; //niti jedno jelo nije stavljeno za sad na stol zato je = { 0 }
bool stolJePun = false;
int najnovijeJelo = -1;

int jeliSu = 0;
int odbijenaHrana = 0;
int stolJeBioPrazan = 0;

int RandomBroj(int min, int max)
{
    return min + rand() % (max - min + 1);
}


void kasnjenje(int min, int max)
{
    sleep(RandomBroj(min, max));
}


void spava(const char* string)
{
    printf("%s sada spava.\n", string);
    kasnjenje(5, 10);
}

int faktorijel(int rng)
{
    if (rng == 1 || rng == 0)
    {
        return 1;
    }
    return rng * faktorijel(rng - 1);
}


void programira(const char* string)
{
    printf("%s sada programira.\n", string);
    int rng = RandomBroj(1, 10);
    int fakt = faktorijel(rng);
    printf("Faktorijel od %d je %d\n", rng, fakt);
}


void jede(const char* string)
{
    pthread_mutex_lock(&mutex);
    printf("%s sada jede.\n", string);
    kasnjenje(2, 4);
    if (stolJePun == true)
    {
        if (strcmp(string, "Tin") == 0)
        {
            if(najnovijeJelo == 1 || najnovijeJelo == 2)
            {
                printf("Tin je odbio hranu.\n");
                odbijenaHrana++;
            }
            else 
            {
                printf("Tin je prihvatio hranu sa stola.\n");
                jeliSu++;
                stolJePun = false;
            }
        }
        else if (strcmp(string, "Davor") == 0)
        {
            if(najnovijeJelo == 0 || najnovijeJelo == 5)
            {
                printf("Davor je odbio hranu.\n");
                odbijenaHrana++;
            }
            else 
            {
                printf("Davor je prihvatio hranu sa stola.\n");
                jeliSu++;
                stolJePun = false;
            }
        }
        else if (strcmp(string, "Ivica") == 0)
        {
            if(najnovijeJelo == 4 || najnovijeJelo == 6)
            {
                printf("Ivica je odbio hranu.\n");
                odbijenaHrana++;
            }
            else 
            {
                printf("Ivica je prihvatio hranu sa stola.\n");
                jeliSu++;
                stolJePun = false;
            }
        }
        else if (strcmp(string, "Ivan") == 0)
        {
            if(najnovijeJelo == 3)
            {
                printf("Ivan je odbio hranu.\n");
                odbijenaHrana++;
            }
            else 
            {
                printf("Ivan je prihvatio hranu sa stola.\n");
                jeliSu++;
                stolJePun = false;
            }
        }        
    }
    else 
    {
        stolJeBioPrazan++;
    }
    
    pthread_mutex_unlock(&mutex);
}


void vozi_auto_na_servis(const char* string)
{
    printf("%s sada vozi auto na servis.\n", string);
    kasnjenje(2, 4);
}


void igra_tenis(const char* string)
{
    printf("%s sada igra tenis.\n", string);
    kasnjenje(2, 4);
}


void slusa_sviranje_klavira(const char* string)
{
    printf("%s sada slusa sviranje klavira.\n", string);
    kasnjenje(2, 4);
}


void gleda_tv(const char* string)
{
    printf("%s sada gleda tv.\n", string);
    kasnjenje(2, 4);
}


void* TinFunkcija(void* arg)
{
    const char* string = (const char*)arg;
    spava(string);
    spava(string);
    programira(string);
    jede(string);
    vozi_auto_na_servis(string);
    return NULL;
}

void* DavorFunkcija(void* arg)
{
    const char* string = (const char*)arg;
    spava(string);
    programira(string);
    jede(string);
    gleda_tv(string);
    return NULL;
}

void* IvicaFunkcija(void* arg)
{
    const char* string = (const char*)arg;
    spava(string);
    igra_tenis(string);
    jede(string);
    programira(string);
    return NULL;
}

void* IvanFunkcija(void* arg)
{
    const char* string = (const char*)arg;
    spava(string);
    slusa_sviranje_klavira(string);
    jede(string);
    programira(string);
    return NULL;
}
void kuha_jelo()
{
    sleep(RandomBroj(1, 2));
}

void odmara_se()
{
    sleep(RandomBroj(1, 2));
}

void stavljaNaStol()
{
    if (stolJePun == false)
    {
        int randomJelo = RandomBroj(0, 7);
        while (jelaNaStolu[randomJelo] == 1) //ako vec ima jelo to onda samo novi rand dok ne dode "novo jelo"
        {
            randomJelo = RandomBroj(0, 7);
        }
        jelaNaStolu[randomJelo] = 1;
        najnovijeJelo = randomJelo;
        printf("Kuharica na stol stavlja: %d\n", najnovijeJelo);
        stolJePun = true;
    }
}

void * kuharicaFunkcija()
{
    for (int i = 0; i < brJela; i++)
    {
        kuha_jelo();
        stavljaNaStol();
        odmara_se();
    }   
}



int main(int argc, char* argv[]) 
{
    pthread_mutex_init(&mutex, NULL);
    srand(time(NULL));


    printf("Unesi broj jela: \n");
    scanf("%d", &brJela);
    if (brJela <= 0)
    {
        printf("Los unos jela.");
    }
    
    pthread_t Tin, Davor, Ivica, Ivan, Kuharica;
    const char* TinString = "Tin";
    const char* DavorString = "Davor";
    const char* IvicaString = "Ivica";
    const char* IvanString = "Ivan";

    if (pthread_create(&Tin, NULL, TinFunkcija, (void*)TinString) != 0)
    {
        perror("Greška pri stvaranju Tin dretve!\n");
        return 1;
    }
    if (pthread_create(&Davor, NULL, DavorFunkcija, (void*)DavorString) != 0)
    {
        perror("Greška pri stvaranju Davor dretve!\n");
        return 1;
    }
    if (pthread_create(&Ivica, NULL, IvicaFunkcija, (void*)IvicaString) != 0)
    {
        perror("Greška pri stvaranju Ivica dretve!\n");
        return 1;
    }
    if (pthread_create(&Ivan, NULL, IvanFunkcija, (void*)IvanString) != 0)
    {
        perror("Greška pri stvaranju Ivan dretve!\n");
        return 1;
    }
    if (pthread_create(&Kuharica, NULL, kuharicaFunkcija, NULL) != 0)
    {
        perror("Greška pri stvaranju Kuharica dretve!\n");
        return 1;
    }


    pthread_join(Tin, NULL);
    pthread_join(Davor, NULL);
    pthread_join(Ivica, NULL);
    pthread_join(Ivan, NULL);
    pthread_join(Kuharica, NULL);


    printf("\nSvi procesi su završeni.\n");
    printf("Jeli su: %d\n", jeliSu);
    printf("Stol je prazan: %d\n", stolJeBioPrazan);
    printf("Odbijena hrana: %d\n", odbijenaHrana);

    return 0;
}
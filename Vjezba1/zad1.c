#include <stdio.h>
#include <stdlib.h>

void kopiranje(const char *original, const char *novi, size_t buffer_velicina)
{
    FILE* originalFile = fopen(original, "r");
    if (original == NULL)
    {
        printf("Problem kod otvaranja originalne datoteke!\n");
        exit(1);
    }

    FILE* noviFile = fopen(novi, "w");
    if (noviFile == NULL)
    {
        printf("Problem kod otvaranja nove datoteke!\n");
        exit(1);
    }

    char* buffer = (char*)malloc(buffer_velicina);
    if (buffer == NULL)
    {
        printf("Problem sa alokacijom memorije za buffer!\n");
        exit(1);
    }

    size_t procitani_bajtovi;
    while ((procitani_bajtovi = fread(buffer, 1, buffer_velicina, originalFile)) > 0)
    {
        fwrite(buffer, 1, procitani_bajtovi, noviFile);
    }


	free(buffer);
    fclose(originalFile);
    fclose(noviFile);

    printf("Uspjesno kopiranje!\n");

}


int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Predan krivi broj argumenata!\n");
        printf("Upotreba: %s <izvor> <odrediste> <velicina buffera>\n", argv[0]);
    }

    size_t buffer_velicina = (size_t)atoi(argv[3]);
    kopiranje(argv[1], argv[2], buffer_velicina);
    return 0;
}


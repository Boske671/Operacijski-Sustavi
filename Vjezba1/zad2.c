#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void kopiranje(const char *original, const char *novi, size_t buffer_velicina) 
{
    int originalFile = open(original, O_RDONLY);
    if (originalFile == -1) 
    {
        printf("Problem kod otvaranja originalne datoteke!\n");
        exit(1);
    }

    int noviFile = open(novi, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (noviFile == -1) 
    {
        printf("Problem kod otvaranja nove datoteke!\n");
        close(originalFile);
        exit(1);
    }

    char *buffer = (char *)malloc(buffer_velicina);
    if (buffer == NULL) 
    {
        printf("Problem sa alokacijom memorije za buffer!\n");
        close(originalFile);
        close(noviFile);
        exit(1);
    }

    ssize_t bytes_read;
    while ((bytes_read = read(originalFile, buffer, buffer_velicina)) > 0) 
    {
        ssize_t bytes_written = write(noviFile, buffer, bytes_read);
        if (bytes_written == -1) 
        {
            perror("Greska pri pisanju u file.");
            free(buffer);
            close(originalFile);
            close(noviFile);
            exit(1);
        }
    }

    if (bytes_read == -1) 
    {
        perror("Greska pri citanju iz filea.");
    }

    free(buffer);
    close(originalFile);
    close(noviFile);
    printf("Uspjesno kopiranje.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 4)
    {
        printf("Predan krivi broj argumenata!\n");
        printf("Upotreba: %s <izvor> <odrediste> <velicina buffera>\n", argv[0]);
    }

    size_t buffer_velicina = (size_t)atoi(argv[3]);
    kopiranje(argv[1], argv[2], buffer_velicina);
    return 0;
}

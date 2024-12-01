#include <stdio.h>populate_frames
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

#define VEL 100000

char polje[VEL];

void popuni_polje() {
    for (int i = 0; i < VEL; i++) {
        polje[i] = (rand() % 2 == 0) ? -1 : 1;
    }
}

void ispis() {
    for (int i = 0; i < VEL; i++) {
        printf("%d\n", polje[i]);
    }
}

int main() {
    srand(time(NULL));

    popuni_polje();

    ispis();

    sleep(10);

    return 0;
}

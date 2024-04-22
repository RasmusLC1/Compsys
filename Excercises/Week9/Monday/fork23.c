#include "csapp.h"

int counter = 0;

void handler (int sig) {
    counter++;
    // sleep(1);
    return;
}

int main () {

    int i;

    Signal(SIGUSR2, handler);

    if (Fork() == 0) {
        for (i = 0; i < 7; i++) {
            Kill(getppid(), SIGUSR2);
            printf ("Sent SIGUSR2 to parent \n");
        }
        exit (0);
    }

    Wait (NULL);
    printf("Counter = %d\n", counter);
    exit(0);
}
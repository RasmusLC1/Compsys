#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "Exec.h"

int exec() {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    char *filename = "fork.c"; //File that will be used
    printf("%d\n", rc);
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        // printf("%d\n", rc);
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc"); // program: "wc" (word count)
        myargs[1] = strdup(filename); // argument: file to count
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs); // runs word count
        printf("this shouldn’t print out");
    } else { // parent goes down this path (main)
        // printf("%d\n", rc);
        int rc_wait = wait(NULL);
        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",
        rc, rc_wait, (int) getpid());
    }
    return 0;
}
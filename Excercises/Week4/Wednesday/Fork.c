#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "Exec.h"
#include "Fork.h"

int x = 100;

int fork1() {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else { // parent goes down this path (main)
        printf("hello, I am parent of %d (pid:%d)\n",
        rc, (int) getpid());
    }
    return 0;
}

int forkWait() {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("%d\n",x);
        x = 20;
        printf("%d\n",x);
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else { // parent goes down this path (main)
        printf("%d\n",x);
        x = 15;
        printf("%d\n",x);
        int rc_wait = wait(NULL);
        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    }
    return 0;
}
int forkHello(){
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello ");
    } else { // parent goes down this path (main)
        int rc_wait = wait(NULL); //This cannot run before the other fork has finished
        printf("World!");
    }
    return 0;
}
int RevforkHello(){
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        int rc_wait = wait(NULL); //This cannot run before the other fork has finished
        printf("hello ");
    } else { // parent goes down this path (main)
        printf("World!");
    }
    return 0;
}
int forkFile(){
    char test[100];
    int rc = fork();
    int c;
    int i = 0;
    FILE *file;
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        file = fopen("test.txt", "r");
        if (file != NULL) {
        while ((c = getc(file)) != EOF ){
             test[i] = c;
             i++;
        }
        }
        printf("%s\n", test);
    } else { // parent goes down this path (main)
        int rc_wait = wait(NULL);
        file = fopen("test.txt", "r");
        if (file != NULL) {
            while ((c = getc(file)) != EOF ){
                test[i] = c;
                i++;
            }
        }
        printf("%s\n", test);
    }
    return 0;
}




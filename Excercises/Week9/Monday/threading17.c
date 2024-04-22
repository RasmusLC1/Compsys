#include "csapp.h"

void *thread(void *vargp);

int main(){
        pthread_t tid;
        Pthread_create(&tid, NULL, thread, NULL);
        Pthread_exit(&tid);
}

void *thread(void *vargp){
    sleep(1);
    printf("hello\n");
    return NULL;
}
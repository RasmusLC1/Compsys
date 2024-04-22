#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "Exec.h"
#include "Fork.h"


int main () {
    // int x = 200;
    int c = forkHello();
    return c;
}

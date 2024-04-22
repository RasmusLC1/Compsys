#include <stdio.h>

int partition(int *array, int p, int j) {
    // printf("p value: %d\n", p);
    int pivot = array[p];
    int i=p-1;
    while (1) {
        do { j--; } while (pivot < array[j]);
            do { i++; } while (array[i] < pivot);
                if (i < j) {
                    
                    int tmp = array[i];       
                    array[i] = array[j];
                    array[j] = tmp;
                } else {
                    printf("j value: %d \n", j+1);
                    printf("i value: %d \n", i);
                    return j+1;
                }
    }
}

void quicksort(int *array, int start, int end) {
    // printf("end start value: %d\n", start);
    if (end-start < 2) {
        return;
    }
    int q = partition(array, start, end);
    // printf("q value: %d\n", q);
    // printf("start value: %d \n", start);
    // printf("end value: %d \n", end);
    // printf("_________\n");
    quicksort(array, start, q);
    printf("test\n");
    printf("q value%d\n", q);
    printf("end value: %d\n__________________", end);
    // printf("test1\n\n");
    quicksort(array, q, end);
}

int main(){
    // int test[] = {5, 3, 2, 8, 6, 9};  
    int test[] = {100, 100, 100000, 255, 0, 123, 4, 50};  
    quicksort(test, 0, 8);
    return 1;
}



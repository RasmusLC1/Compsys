#include <stdio.h>

int partition(int *array, int p, int j) {
    printf("p value: %d\n", p);
    int pivot = array[p];
    int i=p-1;
    while (1) {
        printf("_________\n");
        printf("pivot value: %d\n", pivot);
        printf("Initial i array value: %d\n", array[i]);
        printf("Initial i value: %d\n", i+1);
        printf("Initial j array value: %d\n", array[j]); 
        printf("Initial j value: %d\n", j-1); 
        do { j--; } while (pivot < array[j]);
            do { i++; } while (array[i] < pivot);
                if (i < j) {
                    int tmp = array[i];       
                    array[i] = array[j];
                    array[j] = tmp;
                    printf("_________\n");
                    printf("pivot value: %d\n", pivot);
                    printf("Initial i array value: %d\n", array[i]);
                    printf("Initial i value: %d\n", i+1);
                    printf("Initial j array value: %d\n", array[j]); 
                    printf("Initial j value: %d\n", j-1); 
                    printf("test: %d\n", tmp);
                } else {
                    return j+1;
                }
    }
}

void quicksort(int *array, int start, int end) {
    if (end-start < 2) {
        return;
    }
    int q = partition(array, start, end);
    quicksort(array, start, q);
    quicksort(array, q, end);
}

int main(){
    int test[] = {5, 3, 2, 8, 6, 9};  
    partition(test, 0, 5);
    return 1;
}



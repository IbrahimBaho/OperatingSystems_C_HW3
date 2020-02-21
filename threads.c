#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "threads.h"

// prototypes
void *sort(void *arg);
void *merge(void *arg);
void heapify(double *arr, int n, int i);
void swap(double *xp, double *yp);
void printarray(double *arr, int size, char *s);

int main (int argc, char *argv[]) {

    if(argc != 2) {
        printf("Incorrect number of parameters\n");
        exit(1);
    }

    int size = (atoi(argv[1]));
    pthread_t thread1, thread2, thread3;

    int i, j, one, two, three;
    int fl = (int)(floor((double)size/2));  //half of array (lower half if odd)
    int roof = (int)(ceil((double)size/2)); //half of array (bigger half if odd)

    // Mallocing space for arrays that will be used
    double *arr = (double*) malloc(size * sizeof(double));  // original array with randomized elements
    if(arr == NULL) {exit(1);}

    double *first = (double*) malloc(fl * sizeof(double)); // first half of original array
    if(arr == first) {exit(1);}

    double *second = (double*) malloc(roof * sizeof(double)); // second half of original array
    if(arr == second) {exit(1);}

    double *total = (double*) malloc(size * sizeof(double)); // empty array of original array size used to store the merging of the first and second arrays
    if(arr == total) {exit(1);}

    sth uno, dos, other;    // sth struct used to be passed into sorting arrays function
    mth notoriousBIG;   // mth struct used to be passed in to the merge function

    for(i = 0; i < size; i++) { // storing random doubles between 1.0 and 100.0
        arr[i] = (double)rand() / RAND_MAX;
        arr[i] = 1.0 - arr[i] * 1.0 + arr[i] * 100.0;
    }
    printf("Original array:\n");
    printarray( arr, size, "A");

    j = 0;
    for(i = 0; i < fl; i++) {   // first half of the array
        first[i] = arr[i];
        j++;
    }
    printf("first half: \n");
    printarray(first, fl, "A1");

    for(i = 0; i < roof; i++) { //second half of the array
        second[i] = arr[j];
        j++;
    }
    printf("second half: \n");
    printarray(second, roof, "A2");

    uno.arr = first;
    uno.sz = fl;

    dos.arr = second;
    dos.sz = roof;


    //creating both threads passing both half arrays and sorting them
    one = pthread_create(&thread1, NULL, sort, (void *) &uno);
    two = pthread_create(&thread2, NULL, sort, (void *) &dos);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    notoriousBIG.sz1 = fl;
    notoriousBIG.sz2 = roof;
    notoriousBIG.arr1 = uno.arr;
    notoriousBIG.arr2 = dos.arr;
    notoriousBIG.arr3 = total;

    // merging thread
    three = pthread_create(&thread3, NULL, merge, (void *) &notoriousBIG);
    pthread_join(thread3, NULL);


    printf("Sorted Array:\n");
    printarray(total, size, "A");

    
    free(uno.arr);
    free(dos.arr);
    free(notoriousBIG.arr3);
    free(arr);
    
}

// I used heap sort, since heap sort is much faster than bubble sort, one thread will be faster for a higher bound of elements before two threads surpass one thread in speed
void *sort(void *arg) {
    sth *table;
    table = (sth *) arg;

    int size = table->sz;
    int i;

    // Build heap (rearrange array)
    for (i = size / 2 - 1; i >= 0; i--) {
        heapify(table->arr, size, i);
    }

    // One by one extract an element from heap
    for (i = size - 1; i >= 0; i--) {
        // Move current root to end
        swap(&table->arr[0], &table->arr[i]);

        // call max heapify on the reduced heap
        heapify(table->arr, i, 0);
    }

    pthread_exit(NULL);

}

// heapify makes sure the arr is satisfying heap properties
void heapify(double *arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1 l = 3
    int r = 2*i + 2; // right = 2*i + 2 r = 4

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// merge two sorted half arrays
void *merge(void *arg) {
    mth *table;
    table = (mth *) arg;

    int i = 0, j = 0, k = 0;

    while (i < table->sz1 && j < table->sz2) {
        if (table->arr1[i] < table->arr2[j]) {
            table->arr3[k] = table->arr1[i];
            k++; i++;
        } else {
            table->arr3[k] = table->arr2[j];
            k++; j++;
        }
    }

    // Store remaining elements of first array
    while (i < table->sz1) {
        table->arr3[k] = table->arr1[i];
        k++; i++;
    }

    // Store remaining elements of second array
    while (j < table->sz2) {
        table->arr3[k] = table->arr2[j];
        k++; j++;
    }

    pthread_exit(NULL);
}

// swap used sort and heapify
void swap(double *xp, double *yp) {
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// function used to print array to avoid constantly making for loops
void printarray(double *arr, int size, char *s) {
    int i;

    for(i = 0; i < size; i++) {
        printf("%s[%i] = %d\t", s, i,(int) arr[i]);
    }
    printf("\n");
}


#ifndef THREADS_H
#define THREADS_H

typedef struct sortingThreads {
    int sz;
    double *arr;
} sth;

typedef struct mergingThreads {
    int sz1;
    int sz2;
    double *arr1;
    double *arr2;
    double *arr3;
} mth;

#endif //THREADS_H


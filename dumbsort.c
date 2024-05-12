/**
 * Dumb Sort Algorithm
 * Copyright (C) 2024 Meowing Cat <meowingcate@gmail.com> (https://meowingcat.io)
 * Licensed under the MIT License (https://opensource.org/licenses/MIT)
 * 
 * This stoopid sorting way, I just got this idea and wanted to try.
 * It is so stoopid but it works.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void random_array(int* array, int size, int min, int max) {
    FILE* urandom = fopen("/dev/urandom", "r");
    int number;

    for (int i = 0; i < size; i++) {
        fread(&number, sizeof(int), 1, urandom);
        array[i] = abs((number % (max - min + 1)) + min);
    }

    fclose(urandom);
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quick_sort(int* array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        quick_sort(array, low, pi - 1);
        quick_sort(array, pi + 1, high);
    }
}

int* dumb_sort_new(int max) {
    int* buffer = malloc(max * sizeof(int));
    return buffer;
}

void dumb_sort(int* array, int size, int* buffer, int max) {
    memset(buffer, -1, max * sizeof(int));
    for (int i = 0; i < size; i++) buffer[array[i]] = array[i];
    for (int i = 0, j = 0; i < max; i++) {
        if (j == size) break;
        if (buffer[i] != -1) buffer[j++] = buffer[i];
    }
}

int main() {
    int size = 100000;
    int max = 2147483;
    int* array = malloc(size * sizeof(int));

    int tests = 10;

    int start;
    int end;
    
    start = clock();
    int* dumb_sorted = dumb_sort_new(max);
    end = clock();

    int init_time = end - start;

    printf("[Dumb Sort (init)] Time: %f seconds\n", (double)(init_time) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < tests; i++) {
        random_array(array, size, 0, max);
        dumb_sort(array, size, dumb_sorted, max);
    }
    end = clock();
    printf("[Dumb Sort] Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("[Dumb Sort (total)] Time: %f seconds\n", (double)((end - start) + init_time) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < tests; i++) {
        random_array(array, size, 0, max);
        quick_sort(array, 0, size - 1);
    }
    end = clock();
    printf("[Quick Sort] Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
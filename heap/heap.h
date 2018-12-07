/*
 * Heap Header File
 */

#include <stdio.h>

#define MAX_ELEMENTS 64

int insert(int **heap, int *num, int value);
int extract_max(int **heap, int *num);
int max(int **heap, int num);
int max_heapify_up(int **heap, int num, int index);
int max_heapify_down(int **heap, int num, int index);
void build_max_heap(int **array, int num);
void heap_sort(int **array, int *num);

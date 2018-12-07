#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

/*
 * Insert value into the heap while maintaining the max heap property
 * Return 1 if there is no more memory, 0 if added successfully
 */
int insert(int **heap, int *num, int value) {
	// if (*num == sizeof(*heap) / sizeof(heap[0])) {
	//     // There is no more memory in this heap
	//     return 1;
	// }

	(*heap)[(*num)++] = value;
	return max_heapify_up(heap, *num, *num - 1);
}

/*
 * Extract the max value of the heap and return it
 */
int extract_max(int **heap, int *num) {
	if (*num == 0) {
		// The heap is empty
		return -1;
	}

	int max = (*heap)[0];
	(*heap)[0] = (*heap)[--(*num)];

	max_heapify_down(heap, *num, 0);

	return max;
}

/*
 * Return the max value of the heap but don't extract
 */
int max(int **heap, int num) {
	if (num == 0) {
		// The heap is empty
		return -1;
	}

	return (*heap)[0];
}

/*
 * Maintain the max heap property in the heap going up
 */
int max_heapify_up(int **heap, int num, int index) {
	if (index >= num) {
		// The index is invalid
		return -1;
	}

	// Calculate the index of the parent
	int parent = (index - 1) / 2;

	if (num > 0 && (*heap)[index] > (*heap)[parent]) {
		// The value at index is less than the vlaue of its parent
		int temp = (*heap)[index];
		(*heap)[index] = (*heap)[parent];
		(*heap)[parent] = temp;
		return max_heapify_up(heap, num, parent);
	}

	return 0;
}

/*
 * Maintain the max heap property in the heap going down
 * Compares the element at index with its children
 * This is used for heap_sort to achieve O(n log n) run time
 * This is also used for extract_max to achieve O(log n) run time
 */
int max_heapify_down(int **heap, int num, int index) {
	if (index >= num) {
		// The index is invalid
		return -1;
	}

    // Calculate the indices
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < num && (*heap)[index] < (*heap)[left] && (*heap)[left] > (*heap)[right]) {
		// The value at index is greater than the value of its left child
		int temp = (*heap)[index];
		(*heap)[index] = (*heap)[left];
		(*heap)[left] = temp;
		return max_heapify_down(heap, num, left);
	} else if (right < num && (*heap)[index] < (*heap)[right]) {
		// The value at index is greater than the value of its right child
		int temp = (*heap)[index];
		(*heap)[index] = (*heap)[right];
		(*heap)[right] = temp;
		return max_heapify_down(heap, num, right);
	}

	return 0;
}

/*
 * Convert the array pointed to by heap into a heap
 */
void build_max_heap(int **array, int num) {
    for (int i = num / 2 - 1; i >= 0; i--) {
        max_heapify_down(array, num, i);
    }
}

/*
 * Sort array in ascending order
 */
void heap_sort(int **array, int *num) {
    build_max_heap(array, *num);
    for (int i = *num - 1; i >= 0; i--) {
        (*array)[i] = extract_max(array, num);
    }
}


int main() {
	int num = 0;
	int *heap = malloc(MAX_ELEMENTS * sizeof(int));
	if (heap == NULL) {
		perror("malloc");
		exit(1);
	}

    // Testing insert, max and extract_max
	printf("Return value of Insert: %d\n", insert(&heap, &num, 3));
	printf("Return value of Insert: %d\n", insert(&heap, &num, 4));
	printf("Return value of Insert: %d\n", insert(&heap, &num, 7));
	printf("Return value of Insert: %d\n", insert(&heap, &num, 1));
	printf("Return value of Insert: %d\n", insert(&heap, &num, 2));
	printf("Return value of Insert: %d\n", insert(&heap, &num, 8));

	printf("Max: %d\n", max(&heap, num));
	printf("Extract Max: %d\n", extract_max(&heap, &num));
	printf("Extract Max: %d\n", extract_max(&heap, &num));
	printf("Extract Max: %d\n", extract_max(&heap, &num));
	printf("Max: %d\n", max(&heap, num));

    num = 64;
    int temp_num = num;
    int *array = malloc(num * sizeof(int));
    for (int i = 0; i < num; i++) {
        array[i] = random() % 10;
    }
    heap_sort(&array, &num);
    for (int i = 0; i < temp_num; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

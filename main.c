#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_SIZE 1000

#define SIZE 0
#define MAX 1
#define MIN 2

#define START 0
#define STOP 1

typedef struct array {
    int *item;
    int size;
} tArray;

void printArray(tArray *array) {
    for (unsigned int i = 0; i < array->size; i++) {
        printf("%d ", array->item[i]);
    }
    printf("\n");
}

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int compInc(int x, int y) {
    return x > y;
}

int compDec(int x, int y) {
    return y > x;
}

void bubbleSort(tArray *array, int (*Compare)(int, int)) {
    /* https://github.com/allen0099/advancedC/blob/week14/main.c */
    for (int i = 0; i < array->size - 1; i++) {
        for (int j = 0; j < array->size - 1 - i; j++) {
            if (Compare(array->item[j], array->item[j + 1])) {
                swap(&array->item[j], &array->item[j + 1]);
            }
        }
    }
}

void exchange_sort(tArray *array) {
    /* Same as bubble Sort */
    for (int i = 0; i < array->size - 1; i++) {
        for (int j = 0; j < array->size - 1 - i; j++) {
            if (compInc(array->item[j], array->item[j + 1])) {
                swap(&array->item[j], &array->item[j + 1]);
            }
            printArray(array);
        }
    }
}

void merge(tArray *front, tArray *rear, tArray *array) {
    /* input two sorted arrays, and merge them into one sorted array */
    int countFront = 0, countRear = 0, countArray = 0;
    while (countFront < front->size && countRear < rear->size) {
        if (front->item[countFront] < rear->item[countRear]) {
            array->item[countArray++] = front->item[countFront];
            countFront++;
        } else {
            array->item[countArray++] = rear->item[countRear];
            countRear++;
        }
    }
    /* Copy the rest into array */
    if (countFront == front->size) {
        for (int i = countRear; i < rear->size; i++) {
            array->item[countArray++] = rear->item[i];
        }
    } else {
        for (int i = countFront; i < front->size; i++) {
            array->item[countArray++] = front->item[i];
        }
    }
    printArray(array);
}

void merge_sort(tArray *array) {
    if (array->size > 1) {
        int frontArraySize = array->size / 2;
        int rearArraySize = array->size - frontArraySize;

        tArray *front, *rear;
        front = (tArray *) malloc(sizeof(tArray));
        rear = (tArray *) malloc(sizeof(tArray));

        front->item = (int *) malloc(sizeof(int) * frontArraySize);
        front->size = (int) frontArraySize;
        rear->item = (int *) malloc(sizeof(int) * rearArraySize);
        rear->size = (int) rearArraySize;

        for (int i = 0; i < frontArraySize; i++)
            front->item[i] = array->item[i];
        for (int j = 0; j < rearArraySize; j++)
            rear->item[j] = array->item[frontArraySize + j];
        merge_sort(front);
        merge_sort(rear);
        merge(front, rear, array);
    }
}

void partition(tArray *array, tArray *left, tArray *right) {
    int pivotItem = array->item[0];
    int j = 0;
    for (int i = 0; i < array->size; i++) {
        if (array->item[i] < pivotItem) {
            j++;
            swap(&array->item[i], &array->item[j]);
        }
    }
    swap(array->item, &array->item[j]);

    left->item = array->item;
    left->size = j;
    right->item = array->item + j + 1;
    right->size = array->size - j - 1;
}

void quick_sort(tArray *array) {
    /* pivot is the first of the array */
    if (array->size <= 1) {
        return;
    }
    tArray *left, *right;
    left = (tArray *) malloc(sizeof(tArray));
    right = (tArray *) malloc(sizeof(tArray));
    partition(array, left, right);
    quick_sort(left);
    quick_sort(right);

    printArray(array);
}

void counting_sort(tArray *array, int min, int max) {
    unsigned int index = 0;
    unsigned short *count = calloc(max - min + 1, sizeof(unsigned short));
    for (int i = 0; i < array->size; i++) {
        count[array->item[i] - min]++;
    }
    for (int i = 0; i < max - min + 1; i++) {
        while (count[i]--) {
            array->item[index++] = min + i;
        }
    }
    printArray(array);
    free(count);
}

int main() {
    double TIME_SHIFT[2];
    long CONST_NUM[3];
    long choose;

    /* fgets storage define */
    char str[INPUT_SIZE];
    char *ptr;

    /* Init random seed */
    srand(time(NULL));
//    srand(5);

    printf("======= Basic =======\n");
    printf("Array size: ");
    fgets(str, INPUT_SIZE, stdin);
    CONST_NUM[SIZE] = strtol(str, &ptr, 10);

    printf("Array max: ");
    fgets(str, INPUT_SIZE, stdin);
    CONST_NUM[MAX] = strtol(str, &ptr, 10);

    printf("Array min: ");
    fgets(str, INPUT_SIZE, stdin);
    CONST_NUM[MIN] = strtol(str, &ptr, 10);

    /* Initial array */
    tArray *array = (tArray *) malloc(sizeof(tArray));
    array->item = (int *) malloc(sizeof(int) * CONST_NUM[SIZE]);
    array->size = (int) CONST_NUM[SIZE];

    /* Init array with random values */
    for (int i = 0; i < array->size; i++) {
        array->item[i] = rand() % (CONST_NUM[MAX] - CONST_NUM[MIN] + 1) + CONST_NUM[MIN];
    }

    printf("======= Datatype =======\n");
    printf("(1) Sorted array\n");
    printf("(2) Reverse sorted array\n");
    printf("(3) Random array\n");

    fgets(str, INPUT_SIZE, stdin);
    choose = strtol(str, &ptr, 10);

    switch (choose) {
        case 1: // sorted
            bubbleSort(array, compInc);
            break;
        case 2: // reverse sorted
            bubbleSort(array, compDec);
            break;
        default:
            break;
    }
    printf("Original array:\n");
    printArray(array);

    printf("======= Algorithm =======\n");
    printf("(1) Exchange sort\n");
    printf("(2) Merge sort\n");
    printf("(3) Quick sort\n");
    printf("(4) Counting sort\n");
    printf("(5) Heap sort\n");

    fgets(str, INPUT_SIZE, stdin);
    choose = strtol(str, &ptr, 10);

    switch (choose) {
        case 1: // exchange sort
            TIME_SHIFT[START] = clock();
            exchange_sort(array);
            TIME_SHIFT[STOP] = clock();
            break;
        case 2: // merge sort
            TIME_SHIFT[START] = clock();
            merge_sort(array);
            TIME_SHIFT[STOP] = clock();
            break;
        case 3: // quick sort
            TIME_SHIFT[START] = clock();
            quick_sort(array);
            TIME_SHIFT[STOP] = clock();
            break;
        case 4: // counting sort
            TIME_SHIFT[START] = clock();
            counting_sort(array, (int) CONST_NUM[MIN], (int) CONST_NUM[MAX]);
            TIME_SHIFT[STOP] = clock();
            break;
        case 5: // heap sort
            TIME_SHIFT[START] = clock();
//            b_sort(); // implement this
            TIME_SHIFT[STOP] = clock();
            break;
        default:
            printf("Choice unknown, exiting...\n");
            return 0;
    }
    printf("======= Time =======\n");
    printf("CLOCKS_PER_SEC in Posix system is 1000000, so multiply it with 1000\n");
    printf("==> Execute time: %.3f seconds\n", (TIME_SHIFT[STOP] - TIME_SHIFT[START]) / CLOCKS_PER_SEC * 1000);
    printf("==> Total time: %.3f seconds\n", (double) clock() / CLOCKS_PER_SEC * 1000);

    return 0;
}

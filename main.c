#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_SIZE 30

void printArray(const int *array, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", *(array + i));
    }
    printf("\n");
}

int compInc(int x, int y) {
    return x > y;
}

int compDec(int x, int y) {
    return y > x;
}

void bubbleSort(int *array, int arraySize, int (*Compare)(int, int)) {
    /* https://github.com/allen0099/advancedC/blob/week14/main.c */
    for (int i = 0; i < arraySize - 1; i++) {
        for (int j = 0; j < arraySize - 1 - i; j++) {
            if (Compare(*(array + j), *(array + j + 1))) {
                array[j] ^= array[j + 1] ^= array[j] ^= array[j + 1];
            }
        }
    }
}

void exchange_sort(int *array, int arraySize) {
    /* Same as bubble Sort */
    for (int i = 0; i < arraySize - 1; i++) {
        for (int j = 0; j < arraySize - 1 - i; j++) {
            if (compInc(*(array + j), *(array + j + 1))) {
                array[j] ^= array[j + 1] ^= array[j] ^= array[j + 1];
            }
            printArray(array, arraySize);
        }
    }
}

void merge(int frontArraySize, int rearArraySize,
           const int *frontArray, const int *rearArray, int *array) {
    /* input two sorted arrays, and merge them into one sorted array */
    int countFront = 0, countRear = 0, countArray = 0;
    while (countFront < frontArraySize && countRear < rearArraySize) {
        if (frontArray[countFront] < rearArray[countRear]) {
            array[countArray++] = frontArray[countFront];
            countFront++;
        } else {
            array[countArray++] = rearArray[countRear];
            countRear++;
        }
    }
    /* Copy the rest into array */
    if (countFront == frontArraySize) {
        for (int i = countRear; i < rearArraySize; i++) {
            array[countArray++] = rearArray[i];
        }
    } else {
        for (int i = countFront; i < frontArraySize; i++) {
            array[countArray++] = frontArray[i];
        }
    }
    printArray(array, frontArraySize + rearArraySize);
}

void merge_sort(int *array, int arraySize) {
    if (arraySize > 1) {
        int frontArraySize = arraySize / 2;
        int rearArraySize = arraySize - frontArraySize;
        int *frontArray = (int *) malloc(sizeof(int) * frontArraySize);
        int *rearArray = (int *) malloc(sizeof(int) * rearArraySize);
        for (int i = 0; i < frontArraySize; i++)
            frontArray[i] = array[i];
        for (int j = 0; j < rearArraySize; j++)
            rearArray[j] = array[frontArraySize + j];
        merge_sort(frontArray, frontArraySize);
        merge_sort(rearArray, rearArraySize);
        merge(frontArraySize, rearArraySize, frontArray, rearArray, array);
    }
}

void quick_sort() {

}

void a_sort() {

}

void b_sort() {

}

int main() {
    double START, END;
    long ARRAY_SIZE, MAX_NUM, MIN_NUM;
    long choose;

    char str[INPUT_SIZE];
    char *ptr;

    /* Init random seed */
    srand(time(NULL));
//    srand(5);

//    int fa[5] = {1, 2, 3, 5, 5};
//    int ra[6] = {1, 1, 2, 3, 5, 5};
//    int *a = (int *) malloc(sizeof(int) * 11);

    printf("======= Basic =======\n");
    printf("Array size: ");
    fgets(str, INPUT_SIZE, stdin);
    ARRAY_SIZE = strtol(str, &ptr, 10);

    printf("Array max: ");
    fgets(str, INPUT_SIZE, stdin);
    MAX_NUM = strtol(str, &ptr, 10);

    printf("Array min: ");
    fgets(str, INPUT_SIZE, stdin);
    MIN_NUM = strtol(str, &ptr, 10);

    /* Initial array */
    int *array;
    array = (int *) malloc(sizeof(int) * ARRAY_SIZE);

    printf("======= Datatype =======\n");
    printf("(1) Sorted array\n");
    printf("(2) Reverse sorted array\n");
    printf("(3) Random array\n");

    fgets(str, INPUT_SIZE, stdin);
    choose = strtol(str, &ptr, 10);

    switch (choose) {
        case 1: // sorted
            for (int i = 0; i < ARRAY_SIZE; i++) {
                *(array + i) = (int) (rand() % (MAX_NUM - MIN_NUM + 1) + MIN_NUM);
            }
            bubbleSort(array, (int) ARRAY_SIZE, compInc);
            break;
        case 2: // reverse sorted
            for (int i = 0; i < ARRAY_SIZE; i++) {
                *(array + i) = (int) (rand() % (MAX_NUM - MIN_NUM + 1) + MIN_NUM);
            }
            bubbleSort(array, (int) ARRAY_SIZE, compDec);
            break;
        case 3: // random
            for (int i = 0; i < ARRAY_SIZE; i++) {
                *(array + i) = (int) (rand() % (MAX_NUM - MIN_NUM + 1) + MIN_NUM);
            }
            break;
        default:
            printf("Choice unknown, exiting...\n");
            return 0;
    }
    printf("Original array:\n");
    printArray(array, (int) ARRAY_SIZE);

    printf("======= Algorithm =======\n");
    printf("(1) Exchange sort\n");
    printf("(2) Merge sort\n");
    printf("(3) Quick sort\n");
    printf("(4)  sort\n");
    printf("(5)  sort\n");

    fgets(str, INPUT_SIZE, stdin);
    choose = strtol(str, &ptr, 10);

    switch (choose) {
        case 1: // exchange sort
            START = clock();
            exchange_sort(array, (int) ARRAY_SIZE);
            END = clock();
            break;
        case 2: // merge sort
            START = clock();
            merge_sort(array, (int) ARRAY_SIZE);
            END = clock();
            break;
        case 3: // quick sort
            START = clock();
            quick_sort();
            END = clock();
            break;
        case 4: // a sort
            START = clock();
            a_sort(); // implement this
            END = clock();
            break;
        case 5: // b sort
            START = clock();
            b_sort(); // implement this
            END = clock();
            break;
        default:
            printf("Choice unknown, exiting...\n");
            return 0;
    }
    printf("======= Time =======\n");
    printf("CLOCKS_PER_SEC in Posix is 1000000, so multiply it by 1000\n");
    printf("==> Execute time: %.3f seconds\n", (END - START) / CLOCKS_PER_SEC * 1000);
    printf("==> Total time: %.3f seconds\n", (double) clock() / CLOCKS_PER_SEC * 1000);

    return 0;
}

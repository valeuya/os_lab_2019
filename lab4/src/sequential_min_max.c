#include <stdio.h>

#include <stdlib.h>

#include "find_min_max.h"

#include "utils.h"

int main(int argc, char **argv) {

if (argc != 3) {

printf("Usage: %s seed arraysize\n", argv[0]); /* проверка на непустую строку*/

return 1;

}

int seed = atoi(argv[1]);

if (seed <= 0) {

printf("seed is a positive number\n"); /* проверка на неотрицательность целого значения,

используемого для рандомизации псевдо-случайных чисел, генерируемых алгоритмом.

*/

return 1;

}

int array_size = atoi(argv[2]);

if (array_size <= 0) {

printf("array_size is a positive number\n"); /* размер массива должен быть положительным*/

return 1;

}

int *array = malloc(array_size * sizeof(int));/* выделение памяти под массив*/

GenerateArray(array, array_size, seed); /* вызов функции для генерации массива случайных чисел*/

struct MinMax min_max = GetMinMax(array, 0, array_size); /* получение минимального и максимального

значения массива */

free(array); /* отчистка памяти*/

printf("min: %d\n", min_max.min);

printf("max: %d\n", min_max.max);

return 0;

}
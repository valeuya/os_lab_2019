#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "revert_string.h"

int main(int argc, char *argv[])
{
    if (argc != 2)/* argc должен быть 2, для правильного выполнения */
    {
        printf("Usage: %s string_to_revert\n", argv[0]);/* Мы печатаем argv [0], предполагая, что это имя программы */
        return -1;
    }

    char *reverted_str = malloc(sizeof(char) * (strlen(argv[1]) + 1));/*выделяем память для строки размером
    в данном случае sizeof (char) 1 байт в n раз больше (длина строки argv[1]+1)*/

    strcpy(reverted_str, argv[1]);/*копируем изначальную строку в выделенный бок памяти*/

    RevertString(reverted_str); /*Функция для переворачивания строки*/

    printf("Reverted: %s\n", reverted_str); /*печатаем результат*/
    free(reverted_str); /*освобождаем память, выделенную в куче*/
    return 0;
}
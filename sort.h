#ifndef SORT
#define SORT
#include "stringProcessor.h"
#include <cstring> // Потрібно для strcmp

// Функція для обміну двох вказівників на рядки місцями
void swap(char** a, char** b)
{
    char* temp = *a;
    *a = *b;
    *b = temp;
}

// Допоміжна функція для розділення масиву (Partition)
int partition(char** arr, int low, int high)
{
    char* pivot = arr[high]; // Обираємо останній елемент як опорний
    int i = (low - 1); // Індекс меншого елемента

    for (int j = low; j <= high - 1; j++)
    {
        // Порівнюємо рядки лексикографічно (за абеткою)
        // strcmp повертає < 0, якщо рядок ліворуч "менший" за правий
        if (strcmp(arr[j], pivot) < 0)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Рекурсивна функція сортування
void quick_sort_recursive(char** arr, int low, int high)
{
    if (low < high)
    {
        // pi - індекс розділення (partitioning index)
        int pi = partition(arr, low, high);

        // Рекурсивно сортуємо елементи до і після розділення
        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

// Головна функція, яку викликає тест
void quick_sort(char** arr, size_t length)
{
    if (length > 1) {
        // Запускаємо рекурсію від 0 до останнього індексу
        quick_sort_recursive(arr, 0, (int)length - 1);
    }
}
#endif // !SORT
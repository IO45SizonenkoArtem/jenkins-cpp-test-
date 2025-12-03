#ifndef STRING_PROCESSOR
#define STRING_PROCESSOR
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>
#include <stdio.h>
#include "sort.h"

#define STRING_MAX 512ull

// Реалізація зчитування рядка (безпечна)
const int32_t get_str(const char const* msg, char* str, const int32_t limit)
{
    if (msg != NULL) {
        printf("%s", msg);
    }

    if (fgets(str, limit, stdin) != NULL) {
        // Видаляємо символ нового рядка, якщо він є
        size_t len = 0;
        while (str[len] != '\0' && str[len] != '\n') {
            len++;
        }
        if (str[len] == '\n') {
            str[len] = '\0';
        }
        return (int32_t)len;
    }
    return 0;
}

// Реалізація визначення довжини рядка
const size_t strlenn(const char* str)
{
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Реалізація копіювання рядка
void strcopy(char* fStr, char* sStr, size_t until)
{
    size_t i;
    for (i = 0; i < until && sStr[i] != '\0'; i++) {
        fStr[i] = sStr[i];
    }
    fStr[i] = '\0';
}

// Реалізація порівняння рядків
int32_t strcmpp(const char* fStr, const char* sStr)
{
    while (*fStr && (*fStr == *sStr)) {
        fStr++;
        sStr++;
    }
    return *(const unsigned char*)fStr - *(const unsigned char*)sStr;
}

// Реалізація конкатенації (приєднання) рядків
char* strcatt(char* fStr, const char* sStr)
{
    char* ptr = fStr + strlenn(fStr);
    while (*sStr != '\0')
    {
        *ptr++ = *sStr++;
    }
    *ptr = '\0';
    return fStr;
}

bool is_string_valid(char* str)
{
    bool isThereString = false;
    bool isThereColon = false;
    const size_t size = strlenn(str);
    for (size_t i = 0; i < size; i++)
    {
        if ((str[i] == ':' || str[i] == ';' || str[i] == ',') && i == 0ull)
        {
            return false;
        }
        if (str[i] == ':')
        {
            isThereColon = true;
        }
        else if (isThereColon)
        {
            if (str[i] == ',')
            {
                if (!isalpha(str[i - 1ull]) && str[i - 1ull] != ' ')
                {
                    return false;
                }
                else
                {
                    isThereString = true;
                }
            }
            if (str[i] == ';')
            {
                if (!isThereString || (!isalpha(str[i - 1ull]) && str[i - 1ull] != ' '))
                {
                    return false;
                }
                else
                {
                    isThereColon = false;
                }
            }
            if (str[i] == ':')
            {
                return false;
            }
        }
        else
        {
            isThereString = false;
        }
    }
    return true;
}

char* process_string(char* str)
{
    const size_t length = strlenn(str);
    // Виділяємо пам'ять із запасом, бо результуючий рядок може бути довшим
    char* result = (char*)calloc(length * 2 + STRING_MAX, sizeof(char));
    if (!result) return NULL;

    for (size_t i = 0; i < length; i++)
    {
        if (str[i] != ':')
        {
            char temp[2] = { str[i], '\0' };
            strcatt(result, temp);
            continue;
        }
        // Перевірка виходу за межі масиву
        if (i + 1 >= length || str[i + 1] != ' ')
        {
            free(result);
            return NULL;
        }
        strcatt(result, ": ");
        const size_t strsPreCnt = 100;
        char** arr = (char**)calloc(strsPreCnt, sizeof(char*));
        if (!arr) { free(result); return NULL; }

        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++)
        {
            arr[strsCnt] = (char*)calloc(STRING_MAX, sizeof(char));
        }

        size_t strRealCnt = 0ull;
        for (size_t j = i + 2ull; j < length; j++)
        {
            if (str[j] == ',')
            {
                ++strRealCnt;
                ++j; // пропускаємо пробіл після коми
            }
            else if (str[j] == ';')
            {
                // Сортуємо масив слів
                quick_sort(arr, ++strRealCnt);

                for (size_t k = 0; k < strRealCnt; k++)
                {
                    strcatt(result, arr[k]);
                    if (k == strRealCnt - 1ull)
                    {
                        strcatt(result, ";");
                    }
                    else
                    {
                        strcatt(result, ", ");
                    }
                }
                i = j;
                break;
            }
            else
            {
                char temp[2] = { str[j], '\0' };
                strcatt(arr[strRealCnt], temp);
            }
        }
        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++)
        {
            free(arr[strsCnt]);
        }
        free(arr);
    }
    return result;
}
#endif
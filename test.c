#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>


int is_palindrome(wchar_t *str);

int main() {
    setlocale(LC_CTYPE, "");
// wchar_t str[] = L"Привет мир ENGLISH!";
// wprintf(L"%ls\n", str);

// system("chcp 65001 > nul");
    wchar_t str[100];

    while (1) {
        wprintf(L"Введите слово (или пустую строку для выхода): \n");
        fgetws(str, 100, stdin);
        wprintf(L"123 %ls", str);
// Удаление символа новой строки, который fgets() добавляет в конец строки
        str[wcslen(str) - 1] = L'\0';

// Если пользователь ввел пустую строку, завершаем цикл
        if (wcslen(str) == 0 && iswalpha(str[0])) {
            break;
        }

// Проверка на корректность
        int valid = 1;
        for (int i = 0; i < wcslen(str); i++) {
            if (!iswalpha(str[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            wprintf(L"Ошибка: введенное слово содержит некорректные символы\n");
            continue;
        }

        if (is_palindrome(str)) {
            wprintf(L"Слово \"%ls\" - палиндром\n", str);
        } else {
            wprintf(L"Слово \"%ls\" - не палиндром\n", str);
        }
    }

    return 0;
}

int is_palindrome(wchar_t *str) {
    int length = wcslen(str);
    for (int i = 0; i < length / 2; i++) {
        if (towlower(str[i]) != towlower(str[length - i - 1])) {
            return 0;
        }
    }
    return 1;
}
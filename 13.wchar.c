// enum, union
#include <stdio.h>
#include <wchar.h>
#include <locale.h>


int main(void)
{
    //русские символы и не только
    setlocale(LC_ALL, "");
    
    wchar_t ru = L'п';
    wprintf(L"%lc \n", ru);
    
    wchar_t en = L'w';
    wprintf(L"%lc \n", en);
    
    wchar_t other = L'λ';
    wprintf(L"%lc \n", other);
    
    
    // чтение строки
    // char str[10]
    wchar_t str[10];  // 40 байт занимает
    scanf(" %ls", str);  // !нужен пробел, чтобы не считывался символ enter "\n", чтобы scanf работал подряд
    wprintf(L"%ls \n", str);

    // чтение символа
    wchar_t iwch;
    scanf(" %lc", &iwch);  // !нужен пробел, чтобы не считывался символ enter "\n", чтобы scanf работал подряд
    // wscanf(L" %lc", &iwch);
    wprintf(L"%lc \n", iwch);
    

    //размер занимаемый переменными
    int t = 5;
    char mass[] = "привет"; // занимает 13 байт
    wprintf(L"%d \n", sizeof(mass)); //! спросить
    
    
    char *pointer = "привет"; // занимает 13 байт
    int i = 0;
    while(*(pointer + i) != '\0') // идет побайтово, поэтому в сумме 12 байт плюс ноль
    {
        i++;
    }
    i++;
    wprintf(L"%d \n", i);

    
    return 0;
}
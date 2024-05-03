#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    unsigned short n;
    cin >> n;

    map<string, unsigned short> substring_counts;

    char c;
    string substring = "";
    // Считывание "ненужного" символа-пробела
    c = cin.get();
    // Получение первых n символов
    for (unsigned short i = 0; i < n; i++)
        substring += cin.get();
    substring_counts[substring]++;
    // Считывание по одному символу и удаление по одному символу сначала подстроки получая новые и увеличивая счетчики в map'е
    while ((c = cin.get()) != EOF)
    {
        substring += c;
        substring.erase(0, 1);
        substring_counts[substring]++;
    }
    // Нахождение подстрокки с максимальный кол-вом попаданий. Map уже отсортирован в лексикографическом порядке, поэтому достаточно строгого сравнения в случае нескольких максимально часто встречающихся строк
    substring = "";
    n = 0;
    // Прохождение по элементам map'а. Entry - пары <ключ, значение>
    for (const auto &entry : substring_counts)
    {
        if (entry.second > n)
        {
            n = entry.second;
            substring = entry.first;
        }
    }

    cout << substring << endl;

    return 0;
}
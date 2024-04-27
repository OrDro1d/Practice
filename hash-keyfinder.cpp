#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    unsigned short n;
    unsigned long long p = 1, hash = 0;
    vector<unsigned long long> sublinesHashes;
    string line;

    cin >> n >> line;

    // Вычисляем p
    for (unsigned short i = 0; i < n; i++)
        p *= 27;

    // Нахождение хэша первой подстроки строки line длины n
    for (unsigned short i = 0; i < n; i++)
        hash += (line[i] - 96) * (p /= 27);
    sublinesHashes.push_back(hash);

    // Вычисляем p (снова)
    p = 1;
    for (unsigned short i = 0; i < n; i++)
        p *= 27;

    // Нахождение остальных подстрок строки line длины n
    p /= 27;
    for (unsigned int i = n; i < line.length(); i++)
    {
        hash = (hash % p) * 27 + line[i] - 96;
        sublinesHashes.push_back(hash);
    }

    // Сортировка хэшей
    sort(sublinesHashes.begin(), sublinesHashes.end());

    // Поиск самого часто встречаемого хэша
    unsigned int max = 0;
    for (unsigned int i = 0, j = 0; i < sublinesHashes.size(); i = j)
    {
        for (j = i; j < sublinesHashes.size() && sublinesHashes[j] == sublinesHashes[i]; j++)
            ;
        if (j - i > max)
        {
            max = j - i;
            hash = sublinesHashes[i];
        }
    }

    // Вывод самой часто встречающейся строки
    for (unsigned short i = 0; i < n; i++)
    {
        cout << (char)(hash / p + 96);
        hash %= p;
        p /= 27;
    }
    cout << endl;

    return 0;
}
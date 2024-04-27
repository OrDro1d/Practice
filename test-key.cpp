#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    unsigned int n, maximum = 0;
    cin >> n;

    string our_key, subline = "";
    map<string, unsigned int> sublines_counter;

    char c;
    cin.get(c);

    for (unsigned int i = 0; i < n; i++)
    {
        cin.get(c);
        subline += c;
    }

    (sublines_counter.count(subline) != 0)
        ? sublines_counter[subline] += 1
        : sublines_counter[subline] = 1;

    if (sublines_counter[subline] > maximum || (sublines_counter[subline] == maximum && subline < our_key))
    {
        our_key = subline;
        maximum = sublines_counter[subline];
    }

    while (true)
    {
        cin.get(c);
        if (c == EOF)
            break;

        subline += c;
        subline.replace(0, 1, "");

        (sublines_counter.count(subline) != 0)
            ? sublines_counter[subline] += 1
            : sublines_counter[subline] = 1;

        if (sublines_counter[subline] > maximum || (sublines_counter[subline] == maximum && subline < our_key))
        {
            our_key = subline;
            maximum = sublines_counter[subline];
        }
    }

    cout << our_key << endl;

    return 0;
}
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    unsigned int n, maximum = 0;
    cin >> n;

    string message, our_key, subline;
    cin >> message;

    map<string, unsigned int> sublines_counter;

    for (unsigned int i = 0; i < message.length() - n + 1; i++)
    {
        subline = "";
        for (unsigned int j = i; j < n + i; j++)
        {
            subline += message[j];
        }

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
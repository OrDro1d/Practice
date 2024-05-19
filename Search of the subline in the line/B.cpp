#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

long long culc_hash(const string &line)
{
    long long hash = 0;
    for (unsigned i = 0; i < line.length(); i++)
        hash = (hash << 5) + (int)(line[i] - 'a');
    return hash;
}

string hash_to_str(long long hash, long long key_length)
{
    string result = "";
    while (key_length--)
    {
        result += (char)(hash % 32 + 'a');
        hash >>= 5;
    }
    reverse(result.begin(), result.end());
    return result;
}

int main()
{
    long long key_length;
    string message;
    cin >> key_length >> message;

    long long sublines_number, hash, maximum = 1;
    sublines_number = message.length() - key_length + 1;
    long long sublines[sublines_number] = {0};

    for (unsigned i = 0; i < sublines_number; i++)
    {
        string subline = message.substr(i, key_length);
        hash = culc_hash(subline);
        sublines[i] = hash;
    }

    sort(sublines, sublines + sublines_number);

    int sum = 1;
    hash = sublines[0];
    for (unsigned i = 1; i < sublines_number; i++)
    {
        if (sublines[i] == sublines[i - 1])
        {
            sum++;
            if (sum > maximum)
            {
                maximum = sum;
                hash = sublines[i];
            }
        }
        else
            sum = 1;
    }

    cout << hash_to_str(hash, key_length) << endl;

    return 0;
}
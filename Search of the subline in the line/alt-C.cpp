#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> culc_prefix(const string &pattern)
{
    int m = pattern.size();
    vector<int> pi(m, 0);

    for (unsigned i = 1; i < m; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j])
        {
            j++;
        }
        pi[i] = j;
    }

    return pi;
}

void find_all_occurances(const string &text, const string &pattern)
{
    int n = text.size(), m = pattern.size();
    vector<int> pi = culc_prefix(pattern), result;

    int j = 0, counter = 0;
    for (unsigned i = 0; i < n; i++)
    {
        while (j > 0 && text[i] != pattern[j])
        {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j])
        {
            j++;
        }
        if (j == m)
        {
            result.push_back(i - m + 2);
            j = pi[j - 1];
            counter++;
        }
    }

    cout << counter << endl;
    if (result.size() > 0)
    {
        for (int i = 0; i < result.size() - 1; i++)
            cout << result[i] << " ";
        cout << result[result.size() - 1] << endl;
    }
}

int main()
{
    string line, subline;
    cin >> line >> subline;

    find_all_occurances(line, subline);

    return 0;
}
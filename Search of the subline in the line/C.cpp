#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> culc_prefixes(string subline)
{
    vector<int> pi;
    for (int i = 0; i < subline.length(); i++)
    {
        pi.push_back(0);
    }

    int j = 0, i = 1;

    while (i < subline.length())
    {
        if (subline[j] == subline[i])
        {
            pi[i] = j + 1;
            i++;
            j++;
        }
        else
        {
            if (j == 0)
            {
                pi[i] = 0;
                i++;
            }
            else
            {
                j = pi[j - 1];
            }
        }
    }
    return pi;
}

int find_subline(string line, string subline, vector<int> pi)
{
    int i = 0, j = 0;
    while (i < line.length())
    {
        if (line[i] == subline[j])
        {
            i++;
            j++;
            if (j == subline.length())
            {
                return i;
            }
        }
        else
        {
            if (j > 0)
            {
                j = pi[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
    if (i == line.length())
        return -1;
}

int main()
{
    string line, subline;
    cin >> line >> subline;

    if (line.length() < subline.length())
    {
        cout << 0 << endl;
        return 0;
    }

    vector<int> pi = culc_prefixes(subline);
    vector<int>
        sublines_indexes;
    int index_corrector = 0;

    while (line.length() >= subline.length())
    {
        int subline_index = find_subline(line, subline, pi);

        if (subline_index == -1)
            break;

        sublines_indexes.push_back(subline_index - subline.length() + index_corrector + 1);
        index_corrector = subline_index - subline.length() + 1;
        line.erase(0, index_corrector);
    }

    cout << sublines_indexes.size() << endl;

    if (sublines_indexes.size() > 0)
    {
        for (int i = 0; i < sublines_indexes.size() - 1; i++)
            cout << sublines_indexes[i] << " ";
        cout << sublines_indexes[sublines_indexes.size() - 1] << endl;
    }

    return 0;
}
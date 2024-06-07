#include <iostream>
#include <map>
using namespace std;

int main()
{
    unsigned int n;
    cin >> n;

    pair<int, int> points[n];
    for (unsigned i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points[i] = make_pair(x, y);
    }
    map<pair<pair<int, int>, pair<int, int>>, unsigned> points_sums;
    unsigned sum = 0;
    for (unsigned i = 0; i < n; i++)
        for (unsigned j = i + 1; j < n; j++)
        {
            if (!points_sums.count(make_pair(points[j], points[i])))
                points_sums[make_pair(points[j], points[i])] = (points[j].first - points[i].first) * (points[j].first - points[i].first) + (points[j].second - points[i].second) * (points[j].second - points[i].second);
            sum += points_sums[make_pair(points[j], points[i])];
        }

    cout << sum;

    return 0;
}
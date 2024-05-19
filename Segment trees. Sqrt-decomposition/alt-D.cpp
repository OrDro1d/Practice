#include <iostream>
using namespace std;

void fill_array(unsigned int diff_arr[], unsigned int commands[][3], unsigned int m, unsigned int p1 = 0, unsigned int p2 = 0)
{
    if (p2 == 0)
        p2 = m;

    for (int i = p1; i < p2; i++)
    {
        if (commands[i][0] == 1)
        {
            diff_arr[commands[i][1] - 1] += 1;
            diff_arr[commands[i][2]] -= 1;
        }
        else
            fill_array(diff_arr, commands, m, commands[i][1] - 1, commands[i][2]);
    }
}

int main()
{
    unsigned int n, m;
    cin >> n >> m;

    unsigned int A[n];

    unsigned int commands[m][3];
    for (int i = 0; i < m; i++)
        cin >> commands[i][0] >> commands[i][1] >> commands[i][2];

    unsigned int diff_arr[n + 1];
    for (int i = 0; i < n + 1; i++)
        diff_arr[i] = 0;

    fill_array(diff_arr, commands, m);

    A[0] = diff_arr[0];
    cout << A[0] << " ";
    for (int i = 1; i < n - 1; i++)
    {
        A[i] = A[i - 1] + diff_arr[i];
        cout << A[i] << " ";
    }
    if (n > 1)
        cout << A[n - 2] + diff_arr[n - 1] << endl;

    return 0;
}
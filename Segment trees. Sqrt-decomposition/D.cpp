#include <iostream>
using namespace std;

void fill_array(unsigned int diff_arr[], unsigned int A[], unsigned int n, unsigned int commands[][3], unsigned int m, unsigned int p1 = 0, unsigned int p2 = 0)
{
    if (p2 == 0)
        p2 = m;

    for (unsigned int i = p1; i < p2; i++)
    {
        if (commands[i][0] == 1)
        {
            diff_arr[commands[i][1] - 1] += 1;
            diff_arr[commands[i][2]] -= 1;
        }
        else
            fill_array(diff_arr, A, n, commands, m, commands[i][1] - 1, commands[i][2]);
    }
}

int main()
{
    unsigned int n, m;
    cin >> n >> m;

    unsigned int A[n];
    for (unsigned int i = 0; i < n; i++)
        A[i] = 0;

    unsigned int commands[m][3];
    for (unsigned int i = 0; i < m; i++)
        cin >> commands[i][0] >> commands[i][1] >> commands[i][2];

    unsigned int diff_arr[n + 1];
    for (unsigned int i = 0; i < n + 1; i++)
        diff_arr[i] = 0;

    fill_array(diff_arr, A, n, commands, m);

    A[0] = diff_arr[0];
    for (unsigned int i = 1; i < n + 1; i++)
        A[i] = A[i - 1] + diff_arr[i];

    {
        unsigned int i = 0;
        while (i < n - 1)
        {
            cout << A[i] << " ";
            i++;
        }
        cout << A[i] << endl;
    }

    return 0;
}
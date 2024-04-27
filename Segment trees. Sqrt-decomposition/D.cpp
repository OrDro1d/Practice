#include <iostream>
using namespace std;

void fillArray(unsigned int A[], unsigned int commands[][3], unsigned int command[])
{
    if (command[0] == 1)
    {
        for (unsigned int i = command[1] - 1; i < command[2]; i++)
            A[i]++;
    }
    else
    {
        for (unsigned int i = command[1] - 1; i < command[2]; i++)
            fillArray(A, commands, commands[i]);
    }
}

int main()
{
    unsigned int N, M;
    cin >> N >> M;

    unsigned int A[N];
    for (unsigned int i = 0; i < N; i++)
        A[i] = 0;

    unsigned int commands[M][3];
    for (unsigned int i = 0; i < M; i++)
        cin >> commands[i][0] >> commands[i][1] >> commands[i][2];

    for (unsigned int i = 0; i < M; i++)
        fillArray(A, commands, commands[i]);

    unsigned int i = 0;
    while (i < N - 1)
    {
        cout << A[i] << " ";
        i++;
    }
    cout << A[i] << endl;

    return 0;
}
#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n + 1, 0);
    std::vector<int> prefix_sum(n + 1, 0);

    for (int i = 1; i <= m; ++i)
    {
        int t, l, r;
        std::cin >> t >> l >> r;

        if (t == 1)
        {
            // Увеличиваем все элементы в диапазоне [l, r] на 1
            prefix_sum[l] += 1;
            prefix_sum[r + 1] -= 1;
        }
        else
        {
            // Выполняем все команды в диапазоне [l, r]
            a[l] += prefix_sum[i];
            a[l] %= MOD;
            a[r + 1] -= prefix_sum[i];
            a[r + 1] = (a[r + 1] + MOD) % MOD;
        }
    }

    // Вычисляем окончательный массив A
    for (int i = 1; i <= n; ++i)
    {
        a[i] += a[i - 1];
        a[i] %= MOD;
        std::cout << a[i] << " ";
    }

    return 0;
}
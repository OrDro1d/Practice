#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class SegTree
{
private:
    unsigned int n;
    vector<int> seg_tree;

public:
    SegTree(int arr[], const int &n);

    int get(int index, int real_index, int left_brunch, int right_brunch) const;
    void set(int index, int real_index, int value, int left_brunch, int right_brunch);

    unsigned int get_n() const;
    void print_st() const;
};

void fill_st(SegTree &seg_tree, unsigned int commands[][3], unsigned int m, unsigned int p1 = 0, unsigned int p2 = 0);

int main()
{
    unsigned int n, m;
    cin >> n >> m;

    int A[n];
    for (int i = 0; i < n; i++)
        A[i] = 0;

    unsigned int commands[m][3];
    for (int i = 0; i < m; i++)
    {
        cin >> commands[i][0] >> commands[i][1] >> commands[i][2];
        commands[i][1]--;
    }

    SegTree st = SegTree(A, n);
    fill_st(st, commands, m);

    for (int i = 0; i < n - 1; i++)
        cout << st.get(i, 0, 0, st.get_n() - 1) << " ";
    cout << st.get(n - 1, 0, 0, st.get_n() - 1) << endl;

    return 0;
}

SegTree::SegTree(int arr[], const int &n)
{
    // Создание массива размера равному степени двойки и ближайшему к исходному
    this->n = trunc(pow(2, ceil(log2(n))));

    if (this->n < 2)
        this->n = 2;
    // Заполнение массива нулями
    seg_tree.resize(this->n * 2, 0);
}

int SegTree::get(int index, int real_index, int left_brunch, int right_brunch) const
{
    // Возвращение элемента по индексу
    if (left_brunch == right_brunch)
        return seg_tree[real_index];

    int sum = seg_tree[real_index];
    int middle_brunch = (left_brunch + right_brunch) / 2;
    index <= middle_brunch
        ? sum += get(index, real_index * 2 + 1, left_brunch, middle_brunch)
        : sum += get(index, real_index * 2 + 2, middle_brunch + 1, right_brunch);
    return sum;
}

void SegTree::set(int left, int right, int real_index, int left_brunch, int right_brunch)
{
    // Изменение дерева отрезков, увеличивая все элементы массива в данном промежутке
    // Выход из рекурсии при выходе за указанный промежуток
    if (right < left_brunch || left > right_brunch)
        return;
    // Увеличение значения узла и выход из рекурсии при попадании исходного промежутка
    // в промежуток дерева отрезков
    if (left <= left_brunch && right_brunch <= right)
    {
        seg_tree[real_index]++;
        return;
    }
    // Если выше указанные условия не выполняются (т. е. данный промежуток частично лежит в промежутке дерева отрезков),
    // то рекурсия делится надвое в две стороны
    int middle_brunch = (left_brunch + right_brunch) / 2;
    set(left, right, real_index * 2 + 1, left_brunch, middle_brunch);
    set(left, right, real_index * 2 + 2, middle_brunch + 1, right_brunch);
}

unsigned int SegTree::get_n() const
{
    return n;
}

void SegTree::print_st() const
{
    cout << n << endl;

    int counter = 0;
    for (int i = 0; i < log2(n * 2); i++)
    {
        for (int j = 0; j < n - trunc(pow(2, i)); j++)
            cout << ".";

        cout << " ";
        for (int j = 0; j < trunc(pow(2, i)); j++)
        {
            cout << seg_tree[counter] << " ";
            counter++;
        }

        for (int j = 0; j < n - trunc(pow(2, i)); j++)
            cout << ".";
        cout << endl;
    }

    // for (int i = 0; i < n * 2; i++)
    //     cout << seg_tree[i] << " ";
    // cout << endl;
}

void fill_st(SegTree &seg_tree, unsigned int commands[][3], unsigned int m, unsigned int p1, unsigned int p2)
{
    if (p2 == 0)
        p2 = m;

    for (unsigned int i = p1; i < p2; i++)
    {
        if (commands[i][0] == 1)
        {
            seg_tree.set(commands[i][1], commands[i][2] - 1, 0, 0, seg_tree.get_n() - 1);
        }
        else
        {
            fill_st(seg_tree, commands, m, commands[i][1], commands[i][2]);
        }
    }
}
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

    int sum(int left, int right, int real_index, int left_brunch, int right_brunch) const;
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
        cout << st.sum(0, i, 0, 0, st.get_n() - 1) << " ";
    cout << st.sum(0, n - 1, 0, 0, st.get_n() - 1) << endl;

    return 0;
}

SegTree::SegTree(int arr[], const int &n)
{
    this->n = trunc(pow(2, ceil(log2(n))));

    if (this->n < 2)
        this->n = 2;

    seg_tree.resize(this->n * 2, 0);
}

int SegTree::sum(int left, int right, int real_index, int left_brunch, int right_brunch) const
{
    if (right < left_brunch || left > right_brunch)
        return 0;

    if (left <= left_brunch && right_brunch <= right)
        return seg_tree[real_index];

    int middle_brunch = (left_brunch + right_brunch) / 2;
    return sum(left, right, real_index * 2 + 1, left_brunch, middle_brunch) + sum(left, right, real_index * 2 + 2, middle_brunch + 1, right_brunch);
}

void SegTree::set(int index, int real_index, int value, int left_brunch, int right_brunch)
{
    if (left_brunch == right_brunch)
    {
        seg_tree[real_index] += value;
        return;
    }

    int middle_brunch = (left_brunch + right_brunch) / 2;
    if (index <= middle_brunch)
    {
        set(index, real_index * 2 + 1, value, left_brunch, middle_brunch);
    }
    else
    {
        set(index, real_index * 2 + 2, value, middle_brunch + 1, right_brunch);
    }

    seg_tree[real_index] = seg_tree[real_index * 2 + 1] + seg_tree[real_index * 2 + 2];
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
            seg_tree.set(commands[i][1], 0, 1, 0, seg_tree.get_n() - 1);
            seg_tree.set(commands[i][2], 0, -1, 0, seg_tree.get_n() - 1);
        }
        else
        {
            fill_st(seg_tree, commands, m, commands[i][1], commands[i][2]);
        }
    }
}
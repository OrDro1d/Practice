#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class SegTree
{
private:
    int new_n;
    vector<int> seg_tree;

    void build(const vector<int> &arr, int index, int left_brunch, int right_brunch);

public:
    SegTree(vector<int> &arr, const int &n);
    void print_st();
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> A;
    A.resize(n, 1);

    unsigned int commands[m][3];
    for (unsigned int i = 0; i < m; i++)
        cin >> commands[i][0] >> commands[i][1] >> commands[i][2];

    SegTree st = SegTree(A, n);
    st.print_st();

    return 0;
}

SegTree::SegTree(vector<int> &arr, const int &n)
{
    new_n = (int)pow(2, ceil(log2(n)));
    seg_tree.resize(new_n * 2, 0);
}

void SegTree::build(const vector<int> &arr, int index, int left_brunch, int right_brunch)
{
    if (left_brunch == right_brunch - 1)
    {
        cout << index << " " << left_brunch << endl;
        seg_tree[index] = arr[left_brunch];
    }
    else
    {
        int middle_brunch = (left_brunch + right_brunch) / 2;
        build(arr, index * 2 + 1, left_brunch, middle_brunch);
        build(arr, index * 2 + 2, middle_brunch, right_brunch);
        seg_tree[index] = seg_tree[index * 2 + 1] + seg_tree[index * 2 + 2];
    }
}

void SegTree::print_st()
{
    for (int elem : seg_tree)
        cout << elem << " ";
}
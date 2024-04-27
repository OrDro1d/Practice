#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_N = 100;
vector<int> dx, dy;

int m, n, p, q;
int x1, y1, x2, y2;
int dist[MAX_N][MAX_N];
pair<int, int> prev_cell[MAX_N][MAX_N];

bool is_inside(int x, int y)
{
    return x >= 1 && x <= m && y >= 1 && y <= n;
}

void bfs()
{
    queue<pair<int, int>> queue;
    queue.push(make_pair(x1, y1));
    dist[x1][y1] = 0;

    while (!queue.empty())
    {
        int x = queue.front().first;
        int y = queue.front().second;
        queue.pop();

        for (int i = 0; i < (p != q ? 8 : 4); ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (is_inside(nx, ny) && dist[nx][ny] == -1)
            {
                dist[nx][ny] = dist[x][y] + 1;
                prev_cell[nx][ny] = make_pair(x, y);
                queue.push(make_pair(nx, ny));
            }
        }
    }
}

int main()
{
    cin >> m >> n >> p >> q >> x1 >> y1 >> x2 >> y2;

    if (p != q)
    {
        dx.push_back(-p);
        dy.push_back(-q);
        dx.push_back(-p);
        dy.push_back(q);
        dx.push_back(p);
        dy.push_back(-q);
        dx.push_back(p);
        dy.push_back(q);

        dx.push_back(-q);
        dy.push_back(-p);
        dx.push_back(-q);
        dy.push_back(p);
        dx.push_back(q);
        dy.push_back(-p);
        dx.push_back(q);
        dy.push_back(p);
    }
    else
    {
        dx.push_back(-p);
        dy.push_back(-q);
        dx.push_back(-p);
        dy.push_back(q);
        dx.push_back(p);
        dy.push_back(-q);
        dx.push_back(p);
        dy.push_back(q);
    }

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            dist[i][j] = -1;

    bfs();

    if (dist[x2][y2] == -1)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << dist[x2][y2] << endl;
        vector<pair<int, int>> path;
        int x = x2, y = y2;
        while (x != x1 || y != y1)
        {
            path.push_back(make_pair(x, y));
            x = prev_cell[x][y].first;
            y = prev_cell[x][y].second;
            cout << x << " " << y << endl;
        }
        path.push_back(make_pair(x1, y1));
        for (int i = path.size() - 1; i >= 0; --i)
        {
            cout << path[i].first << " " << path[i].second << endl;
        }
    }

    return 0;
}
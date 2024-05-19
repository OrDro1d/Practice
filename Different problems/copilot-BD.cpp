#include <iostream>
#include <vector>
using namespace std;

struct Point
{
    int x, y;
};

bool isInsidePolygon(const vector<Point> &polygon, const Point &p)
{
    int n = polygon.size();
    int cnt = 0; // Количество пересечений луча

    for (int i = 0; i < n; ++i)
    {
        const Point &a = polygon[i];
        const Point &b = polygon[(i + 1) % n];

        if ((a.y <= p.y && b.y > p.y) || (a.y > p.y && b.y <= p.y))
        {
            // Проверяем, пересекает ли ребро луч
            double xIntersect = (a.x * (b.y - p.y) + b.x * (p.y - a.y)) / (double)(b.y - a.y);
            if (p.x < xIntersect)
                ++cnt;
        }
    }

    return cnt % 2 == 1; // Нечётное количество пересечений
}

int main()
{
    int n;
    Point p;
    cin >> n >> p.x >> p.y;

    vector<Point> polygon(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> polygon[i].x >> polygon[i].y;
    }

    if (isInsidePolygon(polygon, p))
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }

    return 0;
}

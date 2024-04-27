#include <iostream>
#include <map>
using namespace std;

bool is_convex(pair<int, int> points[], unsigned int n);
bool intersection(map<pair<pair<int, int>, pair<int, int>>, pair<pair<double, bool>, double>> equations_map,
                  pair<pair<int, int>, pair<int, int>> segment1, pair<pair<int, int>, pair<int, int>> segment2);
pair<pair<double, bool>, double> culc_equation(pair<int, int> point1, pair<int, int> point2);

int main()
{
    unsigned int n;
    cin >> n;

    pair<int, int> points[n + 1];
    for (unsigned int i = 0; i < n; i++)
    {
        int first, second;
        cin >> first >> second;
        points[i] = make_pair(first, second);
    }

    (is_convex(points, n)) ? cout << "YES" << endl : cout << "NO" << endl;

    return 0;
}

bool is_convex(pair<int, int> points[], unsigned int n)
{
    points[n] = points[0];
    // Создание словаря, где ключи - это пара точек (точки также, в свою очередь, являются парами целых чисел),
    // а значения - уровнения прямых, пересекающих эти точки, представленные в виде пары из пары дробного числа m и булевого значения,
    // отвечающего за вертикальность прямой, и дробного числа b
    map<pair<pair<int, int>, pair<int, int>>, pair<pair<double, bool>, double>> equations_map;
    // Заполнение словаря отрезками и соответствующими им уравнениями прямых
    for (unsigned int i = 0; i < n; i++)
    {
        pair<pair<int, int>, pair<int, int>> segment = make_pair(points[i], points[i + 1]);
        equations_map[segment] = culc_equation(segment.first, segment.second);
        // Проверка заполнения
        // cout << "(" << segment.first.first << ", " << segment.first.second << "), "
        //      << "(" << segment.second.first << ", " << segment.second.second << "): "
        //      << "(" << equations_map[segment].first.first << ", " << equations_map[segment].first.second << ", "
        //      << equations_map[segment].second << ")"
        //      << endl;
    }
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            // cout << points[i].first << " " << points[i].second << ", " << points[i + 1].first << " " << points[i + 1].second << ", " << points[j].first << " " << points[j].second << ", " << points[j + 1].first << " " << points[j + 1].second << endl;
            if (i != j && intersection(equations_map, make_pair(points[i], points[i + 1]), make_pair(points[j], points[j + 1])))
                return false;
        }
    }
    return true;
}

bool intersection(map<pair<pair<int, int>, pair<int, int>>, pair<pair<double, bool>, double>> equations_map,
                  pair<pair<int, int>, pair<int, int>> segment1, pair<pair<int, int>, pair<int, int>> segment2)
{
    // Получение уравнений вида y = mx + b для наших двух прямых
    // При этом, если какая-то из прямых является строго вертикальной, то значение m.second будет равно false
    double b1, b2;
    pair<double, bool> m1, m2;
    m1 = equations_map[segment1].first;
    b1 = equations_map[segment1].second;
    m2 = equations_map[segment2].first;
    b2 = equations_map[segment2].second;
    // cout << m1.first << " " << m1.second << " " << b1 << " " << m2.first << " " << m2.second << " " << b2 << endl;
    // Если угловые коэффициенты равны, соответственно прямые либо параллельны и иметь общих точек не могут,
    // либо они лежат друг на друге и все множество точек одной прямой полностью совпадает со всем множеством точек другой
    // (что в контексте данной задачи невозможно)
    if (m1.first == m2.first && (m1.second && m2.second || !m1.second && !m2.second))
        return false;
    // Если хоть одна прямая строго вертикальна, то она имеет вид x = b и начинает рассматриваться задачей совершенно по другому
    if (!m1.second)
    {
        double y = m2.first * b1 + b2;
        if ((segment1.first.second < y && y < segment1.second.second) || (segment1.first.second > y && y > segment1.second.second))
            return true;
        return false;
    }
    if (!m2.second)
    {
        double y = m1.first * b2 + b1;
        if ((segment2.first.second < y && y < segment2.second.second) || (segment2.first.second > y && y > segment2.second.second))
            return true;
        return false;
    }
    // Нахождение точки пересечения двух прямых в общем случае
    double x, y;
    x = (double)(b2 - b1) / (m1.first - m2.first);
    y = m1.first * x + b1;
    if (((segment2.first.first < x && x < segment2.second.first) || (segment2.first.first > x && x > segment2.second.first)) && ((segment2.first.second < y && y < segment2.second.second) || (segment2.first.second > y > segment2.second.second)))
        return true;
    return false;
}

pair<pair<double, bool>, double> culc_equation(pair<int, int> point1, pair<int, int> point2)
{
    // Является ли прямая прямая строго вертикальной
    if (point2.first - point1.first != 0)
    {
        // Нет: строим уравнение обычного вида y = mx + b
        // Переменной m.second присваиваем значение true, что в дальнейшем будет означать вертикальность данной прямой
        double m = (double)(point2.second - point1.second) / (point2.first - point1.first);
        double b = point1.second - m * point1.first;
        return make_pair(make_pair(m, true), b);
    }
    else
        // Да: строим уравнение вида x = b
        // В таком случае значение m нам не важно, т. к. оно равно 0 и не будет учитываться в дальнейших вычислениях.
        // Переменной m.second присваиваем значение false, что в дальнейшем будет означать вертикальность данной прямой
        return make_pair(make_pair(0, false), point1.first);
}
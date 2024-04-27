#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

bool is_outside(pair<int, int> our_point, pair<int, int> points[], unsigned int n);
bool belonging(map<pair<pair<int, int>, pair<int, int>>, pair<pair<double, bool>, double>> equations_map,
               pair<int, int> our_point,
               pair<pair<int, int>, pair<int, int>> segment);
bool intersection(map<pair<pair<int, int>, pair<int, int>>, pair<pair<double, bool>, double>> equations_map,
                  pair<int, int> our_point, pair<pair<double, bool>, double> our_equation, pair<int, int> points[],
                  pair<pair<int, int>, pair<int, int>> segment, unsigned int &counter, unsigned int n);
bool intersection(map<pair<pair<int, int>, pair<int, int>>, pair<pair<double, bool>, double>> equations_map,
                  pair<double, double> our_point, pair<pair<double, bool>, double> our_equation,
                  pair<pair<int, int>, pair<int, int>> segment);
template <typename T>
pair<pair<double, bool>, double> culc_equation(pair<T, T> point1, pair<T, T> point2);

vector<pair<pair<int, int>, pair<int, int>>> intersections;

int main()
{
    unsigned int n;
    cin >> n;

    pair<int, int> our_point;
    {
        int first, second;
        cin >> first >> second;
        our_point = make_pair(first, second);
    }

    pair<int, int> points[n + 1];
    for (unsigned int i = 0; i < n; i++)
    {
        int first, second;
        cin >> first >> second;
        points[i] = make_pair(first, second);
    }

    is_outside(our_point, points, n)
        ? cout << "NO" << endl
        : cout << "YES" << endl;

    return 0;
}

bool is_outside(pair<int, int> our_point, pair<int, int> points[], unsigned int n)
{
    points[n] = points[0];
    // Пара точек, через который проходит наш луч
    pair<pair<int, int>, pair<int, int>> our_beam = make_pair(our_point, make_pair(our_point.first + 1, our_point.second));
    // Уравнение прямой, на которой лежит наш луч
    pair<pair<double, bool>, double>
        our_equation = culc_equation(our_point, make_pair(our_point.first + 1, our_point.second));
    // Создание словаря, где ключи - это пара точек (точки также, в свою очередь, являются парами целых чисел),
    // а значения - уровнения прямых, пересекающих эти точки, представленные в виде пары из пары дробного числа m и булевого значения,
    // отвечающего за вертикальность прямой, и дробного числа b
    map<pair<pair<int, int>, pair<int, int>>, pair<pair<double, bool>, double>> equations_map;
    // Заполнение словаря отрезками и соответствующими им уравнениями прямых
    for (unsigned int i = 0; i < n; i++)
    {
        pair<pair<int, int>, pair<int, int>> segment = make_pair(points[i], points[i + 1]);
        equations_map[segment] = culc_equation(segment.first, segment.second);
    }
    unsigned int counter = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        // cout << our_point.first << " " << our_point.second << ", "
        //      << points[i].first << " " << points[i].second << ", "
        //      << points[i + 1].first << " " << points[i + 1].second << " - " << counter << endl;
        if (belonging(equations_map, our_point, make_pair(points[i], points[i + 1])))
            return false;
        if (intersection(equations_map, our_point, our_equation, points, make_pair(points[i], points[i + 1]), counter, n))
            counter++;
    }

    if (counter % 2 == 0)
        return true;
    return false;
}

bool belonging(map<pair<pair<int, int>, pair<int, int>>, pair<pair<double, bool>, double>> equations_map,
               pair<int, int> our_point,
               pair<pair<int, int>, pair<int, int>> segment)
{
    if (equations_map[segment].first.second)
    {
        if (abs(abs(our_point.second) - abs(equations_map[segment].first.first * our_point.first + equations_map[segment].second)) < 1e-12 && ((segment.first.first <= our_point.first && our_point.first <= segment.second.first) || (segment.first.first >= our_point.first && our_point.first >= segment.second.first)) && ((segment.first.second <= our_point.second && our_point.second <= segment.second.second) || (segment.first.second >= our_point.second && our_point.second >= segment.second.second)))
        {
            // cout << segment.first.first << " " << segment.first.second << " " << segment.second.first << " " << segment.second.second << " ++ 0" << endl;
            return true;
        }
        return false;
    }
    else
    {
        if (our_point.first == segment.first.first && ((segment.first.second <= our_point.second && our_point.second <= segment.second.second) || (segment.first.second >= our_point.second && our_point.second >= segment.second.second)))
        {
            // cout << segment.first.first << " " << segment.first.second << " " << segment.second.first << " " << segment.second.second << " -- 0" << endl;
            // cout << our_point.first << " " << segment.first.first << endl;
            return true;
        }
        return false;
    }
}

bool intersection(map<pair<pair<int, int>, pair<int, int>>, pair<pair<double, bool>, double>> equations_map,
                  pair<int, int> our_point, pair<pair<double, bool>, double> our_equation, pair<int, int> points[],
                  pair<pair<int, int>, pair<int, int>> segment, unsigned int &counter, unsigned int n)
{
    // Получение уравнений вида y = mx + b для наших двух прямых
    // При этом, если какая-то из прямых является строго вертикальной, то значение m.second будет равно false
    double b1, b2;
    pair<double, bool> m1, m2;
    m1 = our_equation.first;
    b1 = our_equation.second;
    m2 = equations_map[segment].first;
    b2 = equations_map[segment].second;
    // cout << m1.first << " " << m1.second << " " << b1 << " " << m2.first << " " << m2.second << " " << b2 << " " << counter << endl;
    // Если угловые коэффициенты равны, соответственно прямые либо параллельны и иметь общих точек не могут,
    // либо они лежат друг на друге и все множество точек одной прямой полностью совпадает со всем множеством точек другой
    if (m1.first == m2.first && m2.second)
    {
        // Если прямые лежат друг на друге, то проверяем границы отрезка и убеждаемся, что луч "достигает" его
        if (b1 == b2 && (segment.first.first > our_point.first || segment.second.first > our_point.first))
            for (unsigned int i = 0; i < n; i++)
                if (count(intersections.begin(), intersections.end(), make_pair(points[i], points[i + 1])) == 0 && intersection(equations_map, make_pair(our_point.first - 0.1, our_point.second - 0.1), culc_equation(make_pair(our_point.first - 0.1, our_point.second - 0.1), make_pair(our_point.first + 0.9, our_point.second - 0.1)), make_pair(points[i], points[i + 1])))
                {
                    intersections.push_back(make_pair(points[i], points[i + 1]));
                    counter++;
                }
        return false;
    }
    // Если хоть одна прямая строго вертикальна, то она имеет вид x = b и начинает рассматриваться задачей совершенно по другому
    if (!m2.second)
    {
        double y = m1.first * b2 + b1;
        if (((segment.first.second < y && y < segment.second.second) || (segment.first.second > y && y > segment.second.second)) && segment.first.first > our_point.first)
            return true;
        if (y == segment.first.second || y == segment.second.second)
            for (unsigned int i = 0; i < n; i++)
                if (count(intersections.begin(), intersections.end(), make_pair(points[i], points[i + 1])) == 0 && intersection(equations_map, make_pair(our_point.first - 0.1, our_point.second - 0.1), culc_equation(make_pair(our_point.first - 0.1, our_point.second - 0.1), make_pair(our_point.first + 0.9, our_point.second - 0.1)), make_pair(points[i], points[i + 1])))
                {
                    intersections.push_back(make_pair(points[i], points[i + 1]));
                    counter++;
                }
        return false;
    }
    // Нахождение точки пересечения двух прямых в общем случае
    double x, y;
    x = (double)(b2 - b1) / (m1.first - m2.first);
    y = m1.first * x + b1;
    // cout << " -- " << x << " " << y << " -- " << endl;
    if (((segment.first.first < x && x < segment.second.first) || (segment.first.first > x && x > segment.second.first)) && x > our_point.first)
        return true;
    if (x == segment.first.first || x == segment.second.first)
        for (unsigned int i = 0; i < n; i++)
            if (count(intersections.begin(), intersections.end(), make_pair(points[i], points[i + 1])) == 0 && intersection(equations_map, make_pair(our_point.first - 0.1, our_point.second - 0.1), culc_equation(make_pair(our_point.first - 0.1, our_point.second - 0.1), make_pair(our_point.first + 0.9, our_point.second - 0.1)), make_pair(points[i], points[i + 1])))
            {
                intersections.push_back(make_pair(points[i], points[i + 1]));
                counter++;
            }
    return false;
}

bool intersection(map<pair<pair<int, int>, pair<int, int>>, pair<pair<double, bool>, double>> equations_map,
                  pair<double, double> our_point, pair<pair<double, bool>, double> our_equation,
                  pair<pair<int, int>, pair<int, int>> segment)
{
    // Получение уравнений вида y = mx + b для наших двух прямых
    // При этом, если какая-то из прямых является строго вертикальной, то значение m.second будет равно false
    double b1, b2;
    pair<double, bool> m1, m2;
    m1 = our_equation.first;
    b1 = our_equation.second;
    m2 = equations_map[segment].first;
    b2 = equations_map[segment].second;
    // cout << " -- " << m1.first << " " << m1.second << " " << b1 << " " << m2.first << " " << m2.second << " " << b2 << endl;
    // Если угловые коэффициенты равны, соответственно прямые либо параллельны и иметь общих точек не могут,
    // либо они лежат друг на друге и все множество точек одной прямой полностью совпадает со всем множеством точек другой
    if (m1.first == m2.first && m2.second)
        return false;
    // Если хоть одна прямая строго вертикальна, то она имеет вид x = b и начинает рассматриваться задачей совершенно по другому
    if (!m2.second)
    {
        double y = m1.first * b2 + b1;
        if (((segment.first.second < y && y < segment.second.second) || (segment.first.second > y && y > segment.second.second)) && segment.first.first > our_point.first)
            return true;
        if (y == segment.first.second || y == segment.second.second)
            return true;
        return false;
    }
    // Нахождение точки пересечения двух прямых в общем случае
    double x, y;
    x = (double)(b2 - b1) / (m1.first - m2.first);
    y = m1.first * x + b1;
    if (((segment.first.first < x && x < segment.second.first) || (segment.first.first > x && x > segment.second.first)) && segment.first.first > our_point.first)
        return true;
    if (x == segment.first.first || x == segment.second.first)
        return true;
    return false;
}

template <typename T>
pair<pair<double, bool>, double> culc_equation(pair<T, T> point1, pair<T, T> point2)
{
    // Является ли прямая прямая строго вертикальной
    if (abs(abs(point2.first) - abs(point1.first)) >= 1e-12)
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
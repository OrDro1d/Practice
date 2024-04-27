def culc_equation(point1, point2):
    """Вычисление уравнения прямой в виде y = mx + b по двум данным точкам"""
    # Является ли прямая прямая строго вертикальной
    if point2[0] - point1[0] != 0:
        # Нет: строим уравнение обычного вида y = mx + b
        m = (point2[1] - point1[1]) / (point2[0] - point1[0])
        b = point1[1] - m * point1[0]
        return (m, b)
    else:
        # Да: строим уравнение вида x = b. Переменной m присваиваем значение None, что в дальнейшем будет означать вертикальность данной прямой
        return (None, point1[0])


def intersection(point1, point2, point3, point4):
    """Определение есть ли точка пересечения двух отрезков или нет"""
    # Получение уравнений вида y = mx + b для наших двух прямых. При этом, если какая-то из прямых является строго вертикальной, то значение m будет равно None
    m1, b1 = equations_dict[point1, point2]
    m2, b2 = equations_dict[point3, point4]
    # Если угловые коэффициенты равны, соответственно прямые либо параллельны и иметь общих точек не могут, либо они лежат друг на друге и все множество точек одной прямой полностью совпадает со всем множеством точек другой (что в контексте данной задачи невозможно)
    if m1 == m2:
        return False
    # Если хоть одна прямая строго вертикальна, то она имеет вид x = b и начинает рассматриваться задачей совершенно по другому
    if m1 == None:
        y = m2 * b1 + b2
        # Мы рассматриваем по условию задачи не прямые, а отрезки. Соответственно, нам важно, чтобы точка пересечения попадала в четкие границы
        print(y)
        print(m1, b1, m2, b2, point1, point2)
        if point1[1] < y < point2[1] or point1[1] > y > point2[1]:
            return True
        return False
    if m2 == None:
        y = m1 * b2 + b1
        # Мы рассматриваем по условию задачи не прямые, а отрезки. Соответственно, нам важно, чтобы точка пересечения попадала в четкие границы
        print(y)
        print(m1, b1, m2, b2, point3, point4)
        if point3[1] < y < point4[1] or point3[1] > y > point4[1]:
            return True
        return False
    # Нахождение точки пересечения двух прямых в общем случае
    x = (b2 - b1) / (m1 - m2)
    y = m1 * x + b1
    print(x, y)
    print(m1, b1, m2, b2)
    # Мы рассматриваем по условию задачи не прямые, а отрезки. Соответственно, нам важно, чтобы точка пересечения попадала в четкие границы
    if (point3[0] < x < point4[0] or point3[0] > x > point4[0]) and (
        point3[1] < y < point4[1] or point3[1] > y > point4[1]
    ):
        return True
    return False


def isconvex(points):
    """Определение выпуклости многоугольника по полученному списку точек"""
    points.append(points[0])
    # Создание словаря, где ключи - это точки, а значения - уровнения прямых, пересекающих эти точки
    for i in range(0, len(points) - 1):
        equations_dict[(points[i], points[i + 1])] = culc_equation(
            points[i], points[i + 1]
        )
    print(equations_dict)

    for i in range(0, len(points) - 1):
        for j in range(0, len(points) - 1):
            print(points[i], points[i + 1], points[j], points[j + 1])
            if i != j and intersection(
                points[i], points[i + 1], points[j], points[j + 1]
            ):
                return False
    return True


# Текст программы
N = int(input())
points, equations_dict = [], {}
for i in range(0, N):
    points.append(tuple(map(int, input().split())))
print("YES") if isconvex(points) else print("NO")

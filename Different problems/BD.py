from math import acos, pi


def main():
    # Считываем количество вершин n и точку, местоположение которой необходимо определить, our_point
    n = input().split()
    our_point = tuple(map(int, n[1:]))
    n = int(n[0])
    # Считываем координаты вершин многоугольника в список points
    points = []
    for _ in range(0, n):
        points.append(tuple(map(int, input().split())))
    # Добавляем в конец списка points первый элемент (понадобится дальше в цикле при нахождении углов между лучами)
    # и преобразовываем список в кортеж (т. к. редактирование списка в дальнейшем программой не подразумевается)
    points = tuple(points + [points[0]])
    # Если проверяемая точка our_point является вершиной многоугольника, то выводим "YES" и завершаем программу
    # (если не сделать этой проверки на этом этапе, то в дальнейшем возможно возникновение ошибки DivisionByZero при вычислении косинуса)
    if our_point in points:
        print("YES")
        return
    # Иначе ищем сумму углов между соседними лучами многоугольника sum
    sum = 0
    for i in range(0, n + 1):
        # Вычисляем длины двух соседних лучей и стороны многоугольника, для нахождения косинуса угла между ними
        # Луч №1
        a = (
            (points[i - 1][0] - our_point[0]) ** 2
            + (points[i - 1][1] - our_point[1]) ** 2
        ) ** 0.5
        # Луч №2
        b = (
            (points[i][0] - our_point[0]) ** 2 + (points[i][1] - our_point[1]) ** 2
        ) ** 0.5
        # Сторона многоугольника
        c = (
            (points[i - 1][0] - points[i][0]) ** 2
            + (points[i - 1][1] - points[i][1]) ** 2
        ) ** 0.5
        # Находим косинус по трем сторонам
        cos = acos(round((a * a + b * b - c * c) / (2 * a * b), 13)) * 180 / pi
        if round(cos) == 180:
            print("YES")
            return
        # Теперь ищем определитель по координатам лучей, для получения его знака
        a_coordinates = (points[i - 1][0] - our_point[0]), (
            points[i - 1][1] - our_point[1]
        )
        b_coordinates = (points[i][0] - our_point[0]), (points[i][1] - our_point[1])
        determinant = (
            a_coordinates[0] * b_coordinates[1] - a_coordinates[1] * b_coordinates[0]
        )
        # Прибавляем к общей сумме sum значение косинуса меняя знак в соответствии с полуенным определителем determinant:
        # если детерминант отрицательный, то determinant.as_tuple()[0] == 1, иначе - 0
        sum += -cos if determinant <= 1e-14 else cos
    print("NO" if round(sum / 360) == 0 else "YES")


main()

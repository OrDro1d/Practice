def culc_equation(point1, point2):
    m = (point2[1] - point1[1]) / (point2[0] - point1[0])
    b = point1[1] - m * point1[0]
    return (m, b)


def belonging():
    pass


def intersection(m1, b1, m2, b2):
    x = (b2 - b1) / (m1 - m2)
    y = m1 * x + b1
    return (x, y)


N, our_point = int(input()), tuple(map(int, input().split()))
points = []
for _ in range(0, N):
    points.append(tuple(map(int, input().split())))

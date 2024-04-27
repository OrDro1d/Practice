from math import acos, pi


def isconvex(points):
    def culc_angle(point1, point2, point3):
        def culc_side(point1, point2):
            return ((point2[0] - point1[0]) ** 2 + (point2[1] - point1[1]) ** 2) ** 0.5

        points = (point1, point2, point3, point1)
        sides = tuple(
            culc_side(points[i], points[i + 1]) for i in range(0, len(points) - 1)
        )
        return (
            acos(
                round(
                    (sides[0] ** 2 + sides[1] ** 2 - sides[2] ** 2)
                    / (2 * sides[0] * sides[1]),
                    14,
                )
            )
            * 180
            / pi
        )

    points.insert(0, points[-1])
    points.append(points[1])

    actual_angles_sum = 0
    for i in range(0, len(points) - 2):
        angle = culc_angle(points[i], points[i + 1], points[i + 2])
        actual_angles_sum += angle
    if abs(actual_angles_sum - ANGLES_SUM) > 1e-12:
        return False
    return True


N = int(input())
ANGLES_SUM = (N - 2) * 180
points = []
for _ in range(0, N):
    points.append(tuple(map(int, input().split())))
print("YES") if isconvex(points) else print("NO")

n = int(input())
points = []
for _ in range(n):
    points.append(tuple(map(int, input().split())))

points_dict = {}
for point in points:
    if point not in points_dict.keys():
        points_dict[point] = points.count(point)

sum = 0
for i in range(n):
    for j in range(i + 1, n):
        sum += (
            (points[i][0] - points[j][0]) ** 2 + (points[i][1] - points[j][1]) ** 2
        ) * (points_dict[points[j]] - 1)

print(sum)

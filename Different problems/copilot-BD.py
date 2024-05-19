# def point_in_polygon(vertices, point):
#     n = len(vertices)
#     crossings = 0

#     for i in range(n):
#         x1, y1 = vertices[i]
#         x2, y2 = vertices[(i + 1) % n]

#         if (y1 > point[1]) != (y2 > point[1]):
#             x_intersection = x1 + (x2 - x1) * (point[1] - y1) / (y2 - y1)
#             if point[0] < x_intersection:
#                 crossings += 1

#     return "YES" if crossings % 2 == 1 else "NO"


# point = input().split()

# n = int(point[0])
# point = tuple(map(int, point[1:]))

# vertices = []
# for _ in range(n):
#     vertices.append(tuple(map(int, input().split())))

# print(point_in_polygon(vertices, point))


def is_inside_polygon(vertices, point):
    n = len(vertices)
    inside = False

    for i in range(n):
        x1, y1 = vertices[i]
        x2, y2 = vertices[(i + 1) % n]

        if (y1 > point[1]) != (y2 > point[1]):
            x_intersection = x1 + (x2 - x1) * (point[1] - y1) / (y2 - y1)
            if point[0] < x_intersection:
                inside = not inside

    return inside


point = input().split()

n = int(point[0])
point = tuple(map(int, point[1:]))

vertices = []
for _ in range(n):
    vertices.append(tuple(map(int, input().split())))

print("YES") if is_inside_polygon(vertices, point) else print("NO")

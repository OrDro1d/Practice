def is_inside(x, y, m, n):
    return 1 <= x <= m and 1 <= y <= n


def bfs(m, n, p, q, x1, y1, x2, y2):
    if p != q:
        dx = [p, p, -p, -p, q, q, -q, -q]
        dy = [q, -q, q, -q, p, -p, p, -p]
    else:
        dx = [p, p, -p, -p]
        dy = [q, -q, q, -q]

    dist = [[-1] * (n + 1) for _ in range(m + 1)]
    prev_x = [[0] * (n + 1) for _ in range(m + 1)]
    prev_y = [[0] * (n + 1) for _ in range(m + 1)]

    queue = [(x1, y1)]
    dist[x1][y1] = 0

    while queue:
        x, y = queue.pop(0)
        for i in range(8 if p != q else 4):
            nx, ny = x + dx[i], y + dy[i]
            if is_inside(nx, ny, m, n) and dist[nx][ny] == -1:
                dist[nx][ny] = dist[x][y] + 1
                prev_x[nx][ny] = x
                prev_y[nx][ny] = y
                queue.append((nx, ny))

    if dist[x2][y2] == -1:
        return -1, []
    else:
        path = []
        x, y = x2, y2
        while x != x1 or y != y1:
            path.append((x, y))
            x, y = prev_x[x][y], prev_y[x][y]
        path.append((x1, y1))
        return dist[x2][y2], path[::-1]


m, n, p, q, x1, y1, x2, y2 = map(int, input().split())
k, path = bfs(m, n, p, q, x1, y1, x2, y2)

print(k)
if k != -1:
    for x, y in path:
        print(x, y)

from collections import deque


def is_valid_move(x, y, m, n):
    return 0 <= x < m and 0 <= y < n


def bfs(m, n, p, q, start, end):
    moves = [(p, q), (p, -q), (-p, q), (-p, -q), (q, p), (q, -p), (-q, p), (-q, -p)]
    visited = [[False] * n for _ in range(m)]
    queue = deque([(start, 0)])
    visited[start[0]][start[1]] = True

    while queue:
        (x, y), step = queue.popleft()
        if (x, y) == end:
            return step
        for dx, dy in moves:
            nx, ny = x + dx, y + dy
            if is_valid_move(nx, ny, m) and not visited[nx][ny]:
                visited[nx][ny] = True
                queue.append(((nx, ny), step + 1))
    return -1


def print_path(parent, end):
    path = []
    while end:
        path.append(end)
        end = parent[end]
    return path[::-1]


def find_path(m, n, p, q, x1, y1, x2, y2):
    start = (x1, y1)
    end = (x2, y2)
    parent = {start: None}
    moves = [(p, q), (p, -q), (-p, q), (-p, -q), (q, p), (q, -p), (-q, p), (-q, -p)]
    visited = [[False] * n for _ in range(m)]
    queue = deque([start])
    visited[x1][y1] = True

    while queue:
        x, y = queue.popleft()
        if (x, y) == end:
            return print_path(parent, end)
        for dx, dy in moves:
            nx, ny = x + dx, y + dy
            if is_valid_move(nx, ny, m, n) and not visited[nx][ny]:
                visited[nx][ny] = True
                parent[(nx, ny)] = (x, y)
                queue.append((nx, ny))
    return -1


# Пример входных данных
m, n, p, q, x1, y1, x2, y2 = map(int, input().split())

# Нахождение минимального числа ходов
min_moves = bfs(m, n, p, q, (x1, y1), (x2, y2))
print(min_moves)

# Если путь существует, выводим его
if min_moves != -1:
    path = find_path(m, n, p, q, x1, y1, x2, y2)
    for position in path:
        print(position)

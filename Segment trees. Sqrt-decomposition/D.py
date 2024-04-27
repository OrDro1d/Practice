def fill_the_array(command):
    if command[0] == 1:
        for i in range(command[1] - 1, command[2]):
            A[i] += 1
    else:
        for i in range(command[1] - 1, command[2]):
            fill_the_array(commands[i])


N, M = list(map(int, input().split()))
commands = tuple(tuple(map(int, input().split())) for _ in range(0, M))
A = [0] * N
for i in range(0, M):
    fill_the_array(commands[i])
print(*A)

def optimized_fill_array(A, commands):
    # Создаем разностный массив
    diff = [0] * (len(A) + 1)

    # Применяем команды к разностному массиву
    for command in commands:
        if command[0] == 1:
            # Увеличиваем значение в начальном индексе
            diff[command[1] - 1] += 1
            # Уменьшаем значение в конечном индексе + 1, чтобы обнулить эффект после конечного индекса
            if command[2] < len(A):
                diff[command[2]] -= 1
        else:
            # Для команды типа 2 рекурсивно применяем ссылочные команды
            for i in range(command[1] - 1, command[2]):
                optimized_fill_array(A, [commands[i]])

    # Строим исходный массив из разностного массива
    A[0] = diff[0]
    for i in range(1, len(A)):
        A[i] = A[i - 1] + diff[i]


# Пример использования:
A = [0] * 5  # Предполагаем массив размером 5
commands = [
    [1, 1, 2],
    [1, 4, 5],
    [2, 1, 2],
    [2, 1, 3],
    [2, 3, 4],  # Эта команда ссылается на первые две команды
]
optimized_fill_array(A, commands)
print(A)
# Пример использования:
# N, M = list(map(int, input().split()))
# A = [0] * N
# commands = []
# [commands.append(list(map(int, input().split()))) for _ in range(0, M)]
# print(A)
# print(commands)
# optimized_fill_array(A, commands)
# print(A)

def move(moves, x_1, y_1, moves_history):
    global best_result, the_whole_moves_history
    print(moves_history, the_whole_moves_history)
    if x_1 == x_2 and y_1 == y_2 and (moves < best_result or moves == -1):
        best_result = moves
        the_whole_moves_history = moves_history

    variety = [
        (y_1 + P, x_1 - Q),
        (y_1 + P, x_1 + Q),
        (x_1 + P, y_1 + Q),
        (x_1 + P, y_1 - Q),
        (y_1 - P, x_1 + Q),
        (y_1 - P, x_1 - Q),
        (x_1 - P, y_1 - Q),
        (x_1 - P, y_1 + Q),
    ]

    for p, q in variety:
        if 0 <= p <= M and 0 <= q <= N and (p, q) not in the_whole_moves_history:
            the_whole_moves_history.append((p, q))
            move(moves + 1, p, q, moves_history + [(p, q)])


M, N, P, Q, x_1, y_1, x_2, y_2 = map(int, input().split())
best_result = -1
the_whole_moves_history = [(x_1, y_1)]
move(
    0,
    x_1,
    y_1,
    [(x_1, y_1)],
)
print(best_result, *the_whole_moves_history, sep="\n")

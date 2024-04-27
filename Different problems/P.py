def proof(worms):
    for i in range(0, len(worms)):
        for j in range(0, len(worms)):
            for k in range(0, len(worms)):
                if i != j and i != k and j != k and worms[i] == worms[j] + worms[k]:
                    return (i + 1, j + 1, k + 1)
    return (-1,)


n = int(input())
worms = tuple(map(int, input().split()))
print(*proof(worms))

line = input()
subline = input()

sublines_indexes = []

for i in range(len(line) - len(subline) + 1):
    for j in range(len(subline)):
        if line[i + j] != subline[j]:
            break
    else:
        sublines_indexes.append(i + 1)

print(len(sublines_indexes))
print(*sublines_indexes)

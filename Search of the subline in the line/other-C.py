def culc_prefixes(subline):
    pi = [0] * len(subline)
    j, i = 0, 1

    while i < len(subline):
        if subline[j] == subline[i]:
            pi[i] = j + 1
            i += 1
            j += 1
        elif j == 0:
            pi[i] = 0
            i += 1
        else:
            j = pi[j - 1]
    return pi


def find_subline(line, subline, pi):
    i, j = 0, 0
    while i < len(line):
        if line[i] == subline[j]:
            i += 1
            j += 1
            if j == len(subline):
                return i
        else:
            if j > 0:
                j = pi[j - 1]
            else:
                i += 1
    if i == len(line):
        return -1


line = input()
subline = input()

pi = culc_prefixes(subline)
sublines_indexes = []
index_corrector = 0

while True:
    subline_index = find_subline(line, subline, pi)

    if subline_index == -1:
        break

    sublines_indexes.append(subline_index - len(subline) + index_corrector + 1)
    index_corrector = subline_index - len(subline) + 1
    line = line[index_corrector:]


print(len(sublines_indexes))
print(*sublines_indexes)

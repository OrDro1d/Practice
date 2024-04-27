N, numbers = int(input()), list(map(int, input().split()))
list_of_sums = []
for i in range(0, N):
    lower_and_previous = [number for number in numbers[:i] if number < numbers[i]]
    list_of_sums.append(sum(lower_and_previous))
print(sum(list_of_sums))

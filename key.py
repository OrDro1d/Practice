n, message = input().split()
n = int(n)

possible_keys_counter, key, max_count = {}, "z" * n, 0
for i in range(0, len(message) - n + 1):
    if message[i : i + n] in possible_keys_counter:
        possible_keys_counter[message[i : i + n]] += 1
    else:
        possible_keys_counter[message[i : i + n]] = 1

    if (
        possible_keys_counter[message[i : i + n]] > max_count
        or possible_keys_counter[message[i : i + n]] == max_count
        and message[i : i + n] < key
    ):
        max_count = possible_keys_counter[message[i : i + n]]
        key = message[i : i + n]
print(key)

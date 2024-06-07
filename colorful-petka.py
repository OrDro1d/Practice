color_order = input()
first_colors = input()
second_colors = input()
# forward_order - булевый список. При нахождении первой и(или) второй последовательности в строке
# значение(-я) False переменятся на True
forward_order = [False, False]
# Ищем первую последовательность цветов в строке
for i in range(len(color_order) - len(first_colors) + 1):
    print(color_order[i : i + len(first_colors)])
    if first_colors == color_order[i : i + len(first_colors)]:
        forward_order[0] = True
# Ищем вторую последовательность цветов в строке
print("--")
for i in range(
    color_order.find(first_colors), len(color_order) - len(second_colors) + 1
):
    print(color_order[i : i + len(second_colors)])
    if second_colors == color_order[i : i + len(second_colors)]:
        forward_order[1] = True
print("--")
# forward_order - булевый список. При нахождении первой и(или) второй последовательности в строке
# значение(-я) False переменятся на True.
# В отличие от forward_order backward_order отражает присутствие последовательностей на обратном пути
color_order = "".join(reversed(color_order))
backward_order = [False, False]
print(color_order)
# Ищем первую последовательность цветов в строке
for i in range(len(color_order) - len(first_colors) + 1):
    print(color_order[i : i + len(first_colors)])
    if first_colors == color_order[i : i + len(first_colors)]:
        backward_order[0] = True
print("--")
# Ищем первую последовательность цветов в строке
for i in range(
    color_order.find(first_colors), len(color_order) - len(second_colors) + 1
):
    print(color_order[i : i + len(second_colors)])
    if second_colors == color_order[i : i + len(second_colors)]:
        backward_order[1] = True

print("--")
print(forward_order)
print(backward_order)
print(all(forward_order))
print(all(backward_order))
print(color_order[-1:-3:-1])
print(color_order[::-1])

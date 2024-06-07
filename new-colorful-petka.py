color_order = input()
first_colors = input()
second_colors = input()
# forward_order - булевый список. При нахождении первой и(или) второй последовательности в строке
# значение(-я) False переменятся на True
forward_order = [0, 0]
# Ищем первую последовательность цветов в строке
forward_order[0] = color_order.find(first_colors)
# Ищем вторую последовательность цветов в строке
forward_order[1] = color_order.find(second_colors, forward_order[0] + len(first_colors))
# forward_order - булевый список. При нахождении первой и(или) второй последовательности в строке
# значение(-я) False переменятся на True.
# В отличие от forward_order backward_order отражает присутствие последовательностей на обратном пути
color_order = "".join(reversed(color_order))
backward_order = [0, 0]
# Ищем первую последовательность цветов в строке
backward_order[0] = color_order.find(first_colors)
# Ищем первую последовательность цветов в строке
backward_order[1] = color_order.find(
    second_colors, backward_order[0] + len(first_colors)
)
# Вывод
if -1 in forward_order and -1 in backward_order:
    print("fantasy")
elif -1 not in forward_order and -1 in backward_order:
    print("forward")
elif -1 not in backward_order and -1 in forward_order:
    print("backward")
else:
    print("both")
# print(forward_order, backward_order)

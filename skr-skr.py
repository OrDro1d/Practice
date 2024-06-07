def are_brackets_correct(brackets):
    stack = []
    brackets_dict = {"(": ")", "[": "]"}

    for bracket in brackets:
        if bracket in brackets_dict:
            stack.append(bracket)
        elif bracket in brackets_dict.values():
            if not stack or brackets_dict[stack.pop()] != bracket:
                return False

    return not stack


n = int(input())

brackets_lines = []
for _ in range(n):
    brackets_lines.append(input())

for brackets in brackets_lines:
    print("Yes" if are_brackets_correct(brackets) else "No")

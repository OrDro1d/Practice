def 


n = input().split()
our_point = tuple(map(int, n[1:]))
n = int(n[0])
points = []
for _ in range(0, n):
    points.append(tuple(map(int, input().split())))
print(our_point, points)

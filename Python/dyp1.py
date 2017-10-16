s = [2 5 1 20 6]

sM = max(s) * 3
p = round (sM ** (1/3))
cubes = []
for i in range(2,p+1):
	cubes.append(i ** 3)

p = range(1,15)
p.append(3)

p1 = 0
p2 = 2
for i in range(len(p)):
	if(p[p1] == p[p2]):
		break
	p2 = p[p2]
	if (p[p1] == p[p2]):
		break
	p2 = p[p2]
	p1 = p[p1]

p3 = 0
for i in range(len(p)):
	if (p[p1] == p[p3]):
		break
	p1 = p[p1]
	p3 = p[p3]

print p3			

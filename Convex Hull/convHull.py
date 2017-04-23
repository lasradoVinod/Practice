
def dist(p1,p2):
	return abs(((p2[1] - p1[1]) * (p2[1] - p1[1])) + ((p2[0] - p1[0]) * (p2[0] - p1[0])))

def sideOfLine(l1,l2,p1):
	temp = ((l2[1] - l1[1]) * (p1[0] - l1[0])) - ((p1[1] - l1[1]) * (l2[0] - l1[0]))

	if (temp == 0):
		return 0
	elif (temp < 0):
		return 1
	else:
		return -1

def distFromLine(l1,l2,p1):
	return abs (((l2[1] - l1[1]) * (p1[0] - l1[0])) - ((p1[1] - l1[1]) * (l2[0] - l1[0])))

points = [[0,0],[1,0],[0,1],[1,1],[0.75,0.75]]

for i in range (0,5):
	for j in range (i+1,5):





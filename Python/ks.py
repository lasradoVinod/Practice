val = [10,40,50,70]
wt = [2,5,4,5]

maxVal = 0

def KS(cV,cW,mW):
	global maxVal
	print "cV" + str(cV) + "cW" + str(cW)
	if (cV > maxVal):
		maxVal = cV
	for i in range (len(val)):
		if (cW + wt[i] <= mW):
			KS(cV + val[i],cW + wt[i], mW)

T =  [[0 for x in range(9)] for y in range(len(val))] 

def KSD(cV,cW,mW):
	global maxVal
	global T
	for i in range (len(val)):
		for j in range (mW+1):
			if (cW + wt[i] <= j):
				sI = j-cW-wt[i]
				T[i][j] = T[i][sI] + val[i]
				if (T[i][j] > maxVal):
					maxVal = T[i][j]
			else:
				if i != 0:	
					T[i][j] = T[i-1][j]

KSD(0,0,8)
print maxVal
print T


sampleTuple = (12, 7, 38, 56, 78 )
sampleList = []
for ele in sampleTuple:
	if ele % 2 == 0:
		sampleList.append(ele)
newTuple = tuple(sampleList)
print(newTuple)
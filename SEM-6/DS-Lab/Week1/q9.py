sampleList = [11, -21, 0, 45, 66, -93]
pos = 0;
neg = 0;
for ele in sampleList:
	if ele < 0:
		neg = neg + 1
	else:
		pos = pos + 1
print(f'Positive: {pos} | Negative: {neg}')
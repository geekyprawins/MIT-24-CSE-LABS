a = int(input('Enter number 1: '))
b = int(input('Enter number 2: '))
c = int(input('Enter number 3: '))
if a > b:
	if a > c:
		print(f'{a} is largest among the three.')
	else:
		print(f'{c} is largest among the three.')
else:
	if b > c:
		print(f'{b} is largest among the three.')
	else:
		print(f'{c} is largest among the three.')
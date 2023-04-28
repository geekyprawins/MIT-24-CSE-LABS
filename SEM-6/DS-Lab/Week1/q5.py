list = ['physics', 'chemistry', 1997, 2000]

# appending an element in the list
list.append('maths')
print(list)

# deleting an element from the list
list.remove(1997)
print(list)

# get length of the list
print(len(list))

# count number of occurences of an element in the list
print(list.count('physics'))

# popping last element from the list
print(list.pop())

# inserting an element at a specific position in the list
list = ['physics', 'chemistry', 1997, 2000];
list.insert (2, 'maths')
print(list)

list = ['physics', 'chemistry', 1997, 2000];
list.reverse()
print(list)
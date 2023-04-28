import sys
fn = input("Enter file name: ")
f = open(fn,'r')
lines = f.read().splitlines()
sum=0
c=0
for l in lines:
    words = l.split()
    if words[0]=='CGPA:':
        c+=1
        sum += float(words[1])
print("Avg CGPA is: " , (sum/c))


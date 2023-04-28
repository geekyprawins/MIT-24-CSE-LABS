import fileinput
for line in fileinput.input():
    data = line.strip().split("\t")
    if len(data) == 6:
        date, time, location, item, cost, payment = data
        print ("{0}\t{1}".format(location, cost))
#can try with different instances.....
#print ("{0}\t{1}".format(payment, cost))
#print ("{0}\t{1}".format(item, cost))
noOfNodes = int(input('Enter number of nodes: '))
initiatorNode = int(input('Enter id of the initiator node: '))
failedCoordinator = int(input('Enter id of the failed coordinator node: '))

activeList = [initiatorNode]

i = (initiatorNode+1)%noOfNodes
while i != initiatorNode:
    if i != failedCoordinator:
        activeList.append(i)
        print(activeList)
    i = (i+1)%noOfNodes

max = activeList[0]

for i in range(1, len(activeList)):
    if activeList[i] > max:
        max = activeList[i]

for i in range(len(activeList)):
    if i != initiatorNode:
        print(f'{initiatorNode} sends COORDINATOR MESSAGE to {i} declaring {max} as the new coordinator.')
def bullyAlgo(initNode, superior):
    for i in range(initNode+1, noOfNodes):
        print(f"{initNode} sends ELECTION message to {i}")
        if i not in superior:
            superior.append(i)
    for i in range(1, len(superior)):
        print(f"{superior[i]} sends OK message to {initNode}")
    superior.remove(superior[0])
    if len(superior) == 1:
        return superior[0]
    return bullyAlgo(superior[0], superior)

noOfNodes = int(input('Enter number of nodes: '))
initiatorNode = int(input('Enter id of the initiator node: '))
newCoordinator = bullyAlgo(initiatorNode, [initiatorNode])
for i in range(0, newCoordinator):
    print(f"{newCoordinator} sends COORDINATOR message to {i}")
import socket
host = socket.gethostname()
port = 12716
s = socket.socket()
s.connect((host,port))
a = [int(item) for item in input(str("Enter a number: ")).split()]
s.send(str(a).encode())
data = s.recv(1024)
s.close()
print('Sum is ' ,data.decode())

// '[1,2,3,4]'
// [1,2,3,4]
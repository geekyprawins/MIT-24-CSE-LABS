import socket
host = socket.gethostname()
port = 12585
s = socket.socket()
s.connect((host,port))
s.sendall(b'Welcome User1')
data = s.recv(1024)
s.close()
print(repr(data))
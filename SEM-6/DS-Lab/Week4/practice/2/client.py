import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = socket.gethostname()
port = 12685
s.connect((host, port))
tm = s.recv(1024)
print('Current time from Sever : ', tm.decode())
s.close()
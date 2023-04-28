import socket
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

host = socket.gethostname()
port = 12786

msg = [1,2,3,4]

s.sendto(str(msg).encode(),(host,port))
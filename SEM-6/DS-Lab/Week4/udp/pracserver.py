import socket

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

host = socket.gethostname()
port = 12786
s.bind((host,port))

while True:
    print('waitingg...')
    data,addr = s.recvfrom(1024)
    print('received msgs: ', data.decode(),' from ',addr)
    data_str = data.decode()
    array_data = list(data_str)
    print(array_data[0])
    print(array_data[1])
    
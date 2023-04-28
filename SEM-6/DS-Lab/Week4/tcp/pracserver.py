import socket
import ast
host = socket.gethostname()
port = 12716
s = socket.socket()
s.bind((host,port))
s.listen(5)
conn,addr = s.accept()
while True:
    data = conn.recv(1024)
    if not data: break
    data_array = data.decode()
    print(data_array)
    elements = ast.literal_eval(data_array)
    sumOfElements = sum(elements)
    conn.sendall(str(sumOfElements).encode())
s.close()
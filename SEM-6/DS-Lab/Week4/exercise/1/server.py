import socket
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udp_host = socket.gethostname()
udp_port = 14585

sock.bind((udp_host, udp_port))

while True:
    print("Waiting for client...")
    data,addr = sock.recvfrom(1024)
    print("Received messages: ", data.decode(),"from ", addr)

    currentTime = time.ctime(time.time()) + "\r\n"
    bytesToSend = str.encode(currentTime)
    sock.sendto(bytesToSend, addr)
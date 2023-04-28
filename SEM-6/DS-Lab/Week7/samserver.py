import socket
import datetime
import time
def initiateClockServer():
	s = socket.socket()
	print("socket successfully created")
	#server port 
	port = 8011
	s.bind(('',port))
	s.listen(5)
	print("Socket is listening...")
	while True:
		connection, address = s.accept()
		print('Server connected to', address)
		connection.send(str(datetime.datetime.now()).encode())
	connection.close()
if __name__=='__main__':
	initiateClockServer()

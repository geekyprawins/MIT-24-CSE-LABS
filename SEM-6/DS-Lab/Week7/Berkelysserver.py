from functools import reduce
from dateutil import parser
import threading
import datetime
import socket
import time

client_data = {}
def startRecieveingClockTime(connector, address):
    while True:
# recieve clock time
        clock_time_string = connector.recv(1024).decode()
        clock_time = parser.parse(clock_time_string)
        clock_time_diff = datetime.datetime.now() - clock_time
        client_data[address] = {
            'clock_time': clock_time,
            'time_difference':clock_time_diff,
            'connector':connector
        }
        print("client Data updated with: "+str(address),end="\n\n")
        time.sleep(5)
def startConnecting(master_server):
    while True:
        master_slave_connector, addr = master_server.accept()
        slave_address = str(addr[0]) + ":" + str(addr[1])
        print(slave_address + " got connected successfully")
        current_thread = threading.Thread(target = startRecieveingClockTime,args = (master_slave_connector,slave_address, ))
        current_thread.start()

def getAverageClockDiff():
    current_client_data = client_data.copy()
    time_difference_list = list(client['time_difference']
        for client_addr, client in client_data.items()):
            sum_of_clock_difference = sum(time_difference_list,datetime.timedelta(0,0))
            average_clock_difference = sum_of_clock_difference/len(client_data)
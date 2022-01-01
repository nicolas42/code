from threading import Thread
from time import sleep

import socket


def threaded_function(conn):
    while True:
        data = conn.recv(1024)
        if not data: break
        # conn.sendall(data)
        print("sent", data)  


if __name__ == "__main__":

    HOST = ''                 # Symbolic name meaning all available interfaces
    PORT = 50000              # Arbitrary non-privileged port
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(1)
    while True:
        conn, addr = s.accept()
        # with conn:
        print('Connected by', addr)
        thread = Thread(target = threaded_function, args = (conn, ))
        thread.start()
        thread.join()
        # print("thread finished...exiting")
    
    s.close()




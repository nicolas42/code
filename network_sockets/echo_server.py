# Echo server program
import socket

def run_echo_server(HOST, PORT):
    # HOST = ''                 # Symbolic name meaning all available interfaces
    # PORT = 50007              # Arbitrary non-privileged port
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(1)
    while True:
        conn, addr = s.accept()
        # with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(1024)
            if not data: break
            conn.sendall(data)
            print("sent", data)  
    
    s.close()

run_echo_server('', 50007) 


# # Echo client program
# import socket

# def send_message(HOST, PORT, message):
#     # HOST = '127.0.0.1'    # The remote host
#     # PORT = 50007              # The same port as used by the server
#     s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#     s.connect((HOST, PORT))
#     s.sendall(bytes(message, "utf8"))
#     data = s.recv(1024)
#     print('Received', repr(data))
#     s.close()

# send_message('127.0.0.1', 50007, "Hello World!")

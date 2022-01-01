
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 50000))
s.sendall(bytes("omg","utf8"))
s.sendall(bytes("omg you","utf8"))

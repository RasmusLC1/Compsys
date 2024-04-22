import socket
import sys
import hashlib

HOST = '127.0.0.1'
PORT = 5000

while 1:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.connect((HOST, PORT))
        hash = hashlib.sha256()
        msg = input("enter message: ")
        hash.update(bytes(msg, encoding='utf-8'))
        if msg == "close":
            server_socket.sendall(bytes(msg, encoding='utf-8'))
            break
        else:
            server_socket.sendall(bytes(msg, encoding='utf-8'))
            data = server_socket.recv(1024)
            print(repr(data.decode()))

    
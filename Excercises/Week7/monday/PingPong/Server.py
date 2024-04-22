import socket
import hashlib

HOST = '127.0.0.1' 
PORT = 5000


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
    client_socket.bind((HOST, PORT))
    client_socket.listen()
    conn, addr = client_socket.accept()
    with conn:
        while 1:
            data = conn.recv(1024)
            if data.decode() == "close":
                    break
            elif data.decode()[0:3] == "PUT" :
                value = data.decode()[5:-1]
                conn.sendall(bytes(value + " stored in server", encoding='utf-8'))
            elif data.decode() == "GET":
                if value == "ping":
                    conn.sendall(b"pong")
                elif value == "Asbjørn er en god TA":
                    conn.sendall(b"Det er rigtigt")
                else:
                    conn.sendall(b"bad input")
                conn, addr = client_socket.accept()
            else:
                conn.sendall(b"What do you want")
                conn, addr = client_socket.accept()
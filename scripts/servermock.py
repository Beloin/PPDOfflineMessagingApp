import socket
import threading


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("127.0.0.1", 22222))
server.listen()
conn, addr = server.accept()
with conn:
    print(f"Connected by {addr}")
    # while True:
    data = conn.recv(1 + 256)
    if data:
        print("Recv:", data.decode())
        st = "Hello from python"
        for i in range(256 - len(st)):
            st += "\0"
        bts = st.encode()
        conn.sendall(bts)

    data1 = conn.recv(256)
    data2 = conn.recv(256)
    print("To: ", data1.decode())
    print("Message: ", data2.decode())


def accept_connection(conn: socket.socket):
    contact = conn.recv(256)
    to = conn.recv(256)
    message = conn.recv(256)

if __name__ == "__main__":
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("127.0.0.1", 22222))
    server.listen()
    while True:
        conn, addr = server.accept()
        thd = threading.Thread(target=accept_connection, args=(conn))
        thd.start()

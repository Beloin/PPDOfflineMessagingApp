import socket


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("127.0.0.1", 22222))
server.listen()
conn, addr = server.accept()
with conn:
    print(f"Connected by {addr}")
    while True:
        data = conn.recv(1 + 256)
        if not data:
            break

        print("Recv:", data.decode())
        st = "Hello from python"
        for i in range(255 - len(st)):
            st += "\0"
        bts = st.encode()
        conn.sendall(bts)

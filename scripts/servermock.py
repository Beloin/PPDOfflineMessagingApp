import socket
import threading

chatMessages = {}


def register_and_check_messages(name, conn):
    msgs = chatMessages.get(name)
    if msgs is None:
        chatMessages[name] = {"name": name, "conn": conn, "pending_messages": []}
        return False

    # TODO: Can add something when client does not exists but will be added later
    msgs["conn"] = conn
    return len(msgs["pending_messages"])


def client_offline(name):
    msgs = chatMessages.get(name)
    if msgs is not None:
        msgs["conn"].close()
        msgs["conn"] = None


def sanitize(msg):
    for _ in range(256 - len(msg)):
        msg += "\0"

    return msg


def send_message(fromm, to, message):
    msgs = chatMessages.get(to)
    if msgs is None:
        return

    msg = sanitize(message)
    fromm = sanitize(fromm)

    if msgs["conn"] is None:
        msgs["pending_messages"].append((fromm, msg))
        return

    try:
        conn = msgs["conn"]
        bts = fromm.encode()
        conn.sendall(bts)

        bts = msg.encode()
        conn.sendall(bts)
    except Exception as e:
        client_offline(to)
        msgs["pending_messages"].append((fromm, msg))
        return



def accept_connection(conn: socket.socket):
    contact = conn.recv(256)
    contact = contact.decode()
    print("Contact: ", contact)
    should_send = register_and_check_messages(contact, conn)
    if should_send:
        messages = chatMessages[contact]["pending_messages"]
        for contact_message in messages:
            # From
            fromm = sanitize(contact_message[0])
            bts = fromm.encode()
            conn.sendall(bts)

            # Message
            msg = sanitize(contact_message[1])
            bts = msg.encode()
            conn.sendall(bts)

    while True:
        try:
            to = conn.recv(256)
            if not to:
                client_offline(contact)
                return
            print("To: ", to.decode())
            contact_message = conn.recv(256)
            if not contact_message:
                client_offline(contact)
                return
            print("Message: ", contact_message.decode())

            send_message(contact, to.decode(), contact_message.decode())
        except Exception as e:
            client_offline(contact)
            return


thds = []
if __name__ == "__main__":
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(("127.0.0.1", 22223))
    server.listen()
    while True:
        conn, addr = server.accept()
        thd = threading.Thread(target=accept_connection, args=(conn,))
        thd.start()
        thds.append(thd)

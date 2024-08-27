# Message App using Sockets and Message Broker
- Will control message for Clients

# Messages

## Both Online

If both client are online, messages sent from one to another will be proxied by the server direct to clients.

## One Client offline
If Client B is offline, the messages sent from the online Client A will be sent to Message Broker. When the client B is online again, all messages in broker will be sent to the now online Client B. 

# Clients

Clients in C++QT using a straightforward implementation

# Server + Message Broker
Server will be implemented in (Python, Elixir or Java) and Message broker will be ActiveMQ/RabbitMQ 

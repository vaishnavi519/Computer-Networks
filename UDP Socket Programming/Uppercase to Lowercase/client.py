import socket

# Server configuration
HOST = "127.0.0.1"
PORT = 5001

# Create UDP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Input message
message = input("Enter a string in uppercase: ")

# Send message to server
client_socket.sendto(message.encode("utf-8"), (HOST, PORT))

print("\nMessage sent to server successfully.")

# Receive converted message
data, server_address = client_socket.recvfrom(1024)

result = data.decode("utf-8")

print(f"Converted String: {result}")

# Close client socket
client_socket.close()

print("Client socket closed.")

# A simple multithreaded UDP client/server example.
# This script can be run as a server or a client.
#
# To run the server: python your_script_name.py server
# To run the client: python your_script_name.py client
#
# The server listens for messages and broadcasts any console input to all connected clients.
# The client sends console input to the server and listens for broadcast messages from the server.

import socket
import threading
import sys
import time
from collections import deque

# --- Configuration ---
HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 50000        # Port to listen on (non-privileged ports are > 1023)
BUFFER_SIZE = 1024  # Size of the buffer for received messages


# --- Server Implementation ---
class Server:
    def __init__(self, host, port):
        # Create a UDP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Bind the socket to the host and port
        self.server_address = (host, port)
        self.sock.bind(self.server_address)

        # Dictionary to store connected clients' addresses
        # Using a dictionary for uniqueness and easy access
        self.clients = {}
        # A lock to protect access to the clients dictionary from multiple threads
        self.clients_lock = threading.Lock()

        # A queue for messages to be sent, to decouple the send thread from the main loop
        self.send_queue = deque()

        print(f"Server started on {host}:{port}")

    def receive_loop(self):
        """
        Receiving thread for the server.
        Continuously listens for incoming packets and adds new clients.
        """
        while True:
            try:
                # `recvfrom` is a blocking call, it waits for a packet to arrive.
                # It returns the data and the address of the sender.
                data, address = self.sock.recvfrom(BUFFER_SIZE)
                message = data.decode('utf-8')
                print(f"Received from {address}: {message}")

                # Lock the dictionary before modifying it to prevent race conditions
                with self.clients_lock:
                    if address not in self.clients:
                        # Add the new client to our list
                        self.clients[address] = True
                        print(f"New client connected: {address}")

            except socket.error as e:
                print(f"Socket error in receive loop: {e}")
                break
            except Exception as e:
                print(f"An unexpected error occurred in receive loop: {e}")
                break

    def send_loop(self):
        """
        Sending thread for the server.
        Continuously checks the send queue and broadcasts messages to all clients.
        """
        while True:
            # Check for messages in the queue
            if self.send_queue:
                message = self.send_queue.popleft()
                with self.clients_lock:
                    # Send the message to all connected clients
                    for client_address in self.clients:
                        try:
                            self.sock.sendto(message.encode('utf-8'), client_address)
                        except socket.error as e:
                            print(f"Failed to send to {client_address}: {e}")
            else:
                # Sleep briefly to avoid busy-waiting
                time.sleep(0.01)

    def console_input_loop(self):
        """
        Main thread loop for the server to handle console input.
        Any input is placed in the send queue to be broadcast.
        """
        while True:
            try:
                message = input("Server > ")
                # Add a message to the send queue
                self.send_queue.append(f"[Server]: {message}")
            except EOFError:
                print("Exiting console input loop.")
                break
            except Exception as e:
                print(f"Error reading from console: {e}")
                break

    def run(self):
        # Create and start the receiving thread
        # `daemon=True` means the thread will exit when the main program exits
        recv_thread = threading.Thread(target=self.receive_loop, daemon=True)
        recv_thread.start()

        # Create and start the sending thread
        send_thread = threading.Thread(target=self.send_loop, daemon=True)
        send_thread.start()

        # Start the main console input loop
        self.console_input_loop()

        # Wait for threads to finish (which won't happen here due to infinite loops,
        # but is good practice). In a real game, this might be the main game loop.
        recv_thread.join()
        send_thread.join()


# --- Client Implementation ---
class Client:
    def __init__(self, host, port):
        # Create a UDP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_address = (host, port)

        print(f"Client started. Connecting to {host}:{port}")

    def receive_loop(self):
        """
        Receiving thread for the client.
        Continuously listens for incoming packets from the server.
        """
        while True:
            try:
                data, address = self.sock.recvfrom(BUFFER_SIZE)
                message = data.decode('utf-8')
                print(f"\n{message}\n> ", end="", flush=True)

            except socket.error as e:
                print(f"Socket error in receive loop: {e}")
                break
            except Exception as e:
                print(f"An unexpected error occurred in receive loop: {e}")
                break

    def send_loop(self):
        """
        Sending thread for the client.
        Reads from console input and sends to the server.
        """
        while True:
            try:
                message = input("> ")
                # `sendto` is used to send data to a specific address.
                self.sock.sendto(message.encode('utf-8'), self.server_address)
            except EOFError:
                print("Exiting console input loop.")
                break
            except Exception as e:
                print(f"Error reading from console: {e}")
                break

    def run(self):
        # Create and start the receiving thread
        recv_thread = threading.Thread(target=self.receive_loop, daemon=True)
        recv_thread.start()

        # Create and start the sending thread
        send_thread = threading.Thread(target=self.send_loop, daemon=True)
        send_thread.start()

        # Wait for threads to finish
        recv_thread.join()
        send_thread.join()


# --- Main script logic ---
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python multiplayer_threads.py [server|client]")
        sys.exit(1)

    role = sys.argv[1].lower()

    if role == 'server':
        server = Server(HOST, PORT)
        server.run()
    elif role == 'client':
        client = Client(HOST, PORT)
        client.run()
    else:
        print("Invalid role. Please specify 'server' or 'client'.")
        sys.exit(1)

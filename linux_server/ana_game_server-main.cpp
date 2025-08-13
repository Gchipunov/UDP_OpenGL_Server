#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Define a port for the server to listen on.
#define PORT 54321
// Define the buffer size for messages.
#define BUFFER_SIZE 1024

// This struct will be used to pass data to the client thread.
struct ClientData {
    sockaddr_in6 server_addr;
    socklen_t addr_len;
};

// Function to run the client in a separate thread.
void* run_client(void* arg) {
    ClientData* client_data = (ClientData*)arg;
    int client_sock_fd;
    const char* message = "Hello from the client!";
    
    // Create a new UDP IPv6 socket for the client.
    if ((client_sock_fd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("Client socket creation failed");
        pthread_exit(NULL);
    }
    
    std::cout << "Client thread started. Sending message to server...\n";

    // Send the message to the server.
    sendto(client_sock_fd, message, strlen(message), 0, 
           (const sockaddr*)&client_data->server_addr, client_data->addr_len);
    
    std::cout << "Client thread sent message: '" << message << "'\n";

    // Clean up.
    close(client_sock_fd);
    delete client_data;
    pthread_exit(NULL);
}

int main() {
    int server_sock_fd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in6 server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t client_thread;

    // 1. Create a UDP IPv6 socket for the server.
    if ((server_sock_fd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("Server socket creation failed");
        return 1;
    }

    // 2. Prepare the server address structure.
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6; // Specify IPv6.
    server_addr.sin6_port = htons(PORT); // Convert port to network byte order.
    server_addr.sin6_addr = in6addr_any; // Listen on all available IPv6 addresses.

    // 3. Bind the socket to the server address and port.
    if (bind(server_sock_fd, (const sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Server socket binding failed");
        close(server_sock_fd);
        return 1;
    }

    std::cout << "Server listening on port " << PORT << "...\n";

    // 4. Create and run the client thread.
    // The client needs to know the server's address to send a message.
    ClientData* client_data = new ClientData();
    memcpy(&client_data->server_addr, &server_addr, sizeof(server_addr));
    client_data->addr_len = sizeof(server_addr);
    
    if (pthread_create(&client_thread, NULL, run_client, (void*)client_data) != 0) {
        perror("Failed to create client thread");
        close(server_sock_fd);
        delete client_data;
        return 1;
    }
    
    // 5. Wait for the client thread to finish and receive the message.
    pthread_join(client_thread, NULL); // This waits for the client to send the message.
    
    std::cout << "Waiting to receive a message...\n";

    // Receive a datagram from the client.
    int n = recvfrom(server_sock_fd, buffer, BUFFER_SIZE, 0, 
                     (sockaddr*)&client_addr, &client_addr_len);
    
    if (n < 0) {
        perror("recvfrom failed");
    } else {
        buffer[n] = '\0'; // Null-terminate the received data.
        
        // Convert the client's IPv6 address to a human-readable string.
        char client_ip_str[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &client_addr.sin6_addr, client_ip_str, INET6_ADDRSTRLEN);
        
        std::cout << "Received " << n << " bytes from client at " 
                  << client_ip_str << ":" << ntohs(client_addr.sin6_port) << "\n";
        std::cout << "Message: '" << buffer << "'\n";
    }

    // 6. Clean up resources.
    close(server_sock_fd);

    return 0;
}
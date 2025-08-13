#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Define the port the server will listen on
#define PORT 54321
// Define the size of the buffer for incoming messages
#define BUFFER_SIZE 1024

//server_thread_listening-main.cpp
//
//
//
// compile:
// g++ server_thread_listening-main.cpp -o server_thread_listening-main
//run:
// ./server_thread_listening-main
//
//  echo "Hello from client" | nc -6 -u ::1 54321
//

// This is the function that will be executed by our server thread.
void* server_thread_function(void* arg) {
    int server_sock_fd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in6 server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 1. Create a UDP IPv6 socket.
    if ((server_sock_fd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("Thread: Socket creation failed");
        pthread_exit(NULL); // Terminate the thread if an error occurs.
    }

    // 2. Prepare the server address structure.
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(PORT);
    server_addr.sin6_addr = in6addr_any;

    // 3. Bind the socket to the specified address and port.
    if (bind(server_sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Thread: Socket binding failed");
        close(server_sock_fd);
        pthread_exit(NULL); // Terminate the thread if an error occurs.
    }

	int iServerNumber = 1;

   std::cout << "Launching Alliance and Allegiance Server Number: " << iServerNumber << "...\n";


    std::cout << "Thread: UDP IPv6 server is listening on port " << PORT << "...\n";

    // 4. Main server loop: listen for incoming messages.
    while (true) {
        memset(&client_addr, 0, client_addr_len);
        memset(buffer, 0, BUFFER_SIZE);

        int n = recvfrom(server_sock_fd, buffer, BUFFER_SIZE, 0, 
                         (struct sockaddr *)&client_addr, &client_addr_len);

        if (n < 0) {
            perror("Thread: recvfrom failed");
            continue;
        }
        
        buffer[n] = '\0';
        
        char client_ip_str[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &client_addr.sin6_addr, client_ip_str, INET6_ADDRSTRLEN);

        std::cout << "Thread: Received message from "
                  << client_ip_str << ":" << ntohs(client_addr.sin6_port) << ": "
                  << buffer << "\n";
        
        const char* response = "Server received your message!";
        
        sendto(server_sock_fd, response, strlen(response), 0, 
               (const struct sockaddr *)&client_addr, client_addr_len);
    }

    close(server_sock_fd);
    pthread_exit(NULL); // Exit the thread gracefully.
}

int main() {
    pthread_t server_thread;

    // Create the server thread.
    // The thread will start executing the server_thread_function.
    if (pthread_create(&server_thread, NULL, server_thread_function, NULL) != 0) {
        perror("Main: Failed to create server thread");
        return 1;
    }
    // Add physics thread with planes and cubes
	
	
	// Add TCP Thread to send to http, curl?
	
	// Add TCP Thread to send to chat server
	
	
	
    std::cout << "Main thread is running. The server thread is operating independently.\n";

    // The main thread can now do other things while the server thread listens.
    // For this simple example, we'll just wait for the server thread to finish.
    // In a real application, the main thread would run the game loop or other tasks.
    pthread_join(server_thread, NULL);

    std::cout << "Main: Server thread has terminated.\n";
    return 0;
}
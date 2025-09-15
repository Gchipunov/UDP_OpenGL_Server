#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdatomic.h> // For atomic operations

// Represents the state of our cube.
typedef struct {
    float x, y, z;
    float rotation_x, rotation_y, rotation_z;
    int update_tick;
} CubeState;

// A lock-free structure using two buffers and an atomic pointer.
// The network thread reads from the buffer pointed to by 'front_buffer',
// while the simulation thread writes to the other buffer.
typedef struct {
    CubeState buffers[2];
    _Atomic(CubeState*) front_buffer; // Atomically managed pointer
} LockFreeBuffer;

// Global flag to signal threads to terminate.
volatile bool is_running = true;

// --- Simulation Thread (The Writer) ---
// This function continuously updates the "back" buffer and then atomically
// swaps it to become the "front" buffer.
void* update_simulation(void* arg) {
    LockFreeBuffer* buffer = (LockFreeBuffer*)arg;
    int tick = 0;

    // Determine the initial back buffer (the one not pointed to by front_buffer).
    CubeState* back_buffer = (atomic_load(&buffer->front_buffer) == &buffer->buffers[0])
                           ? &buffer->buffers[1]
                           : &buffer->buffers[0];

    printf("Simulation thread started.\n");

    while (is_running) {
        // --- Write to the back buffer (no lock needed) ---
        back_buffer->x += 0.01f;
        back_buffer->y += 0.005f;
        back_buffer->rotation_z += 0.5f;
        back_buffer->update_tick = tick++;

        // --- Atomically swap the pointers ---
        // atomic_exchange is a powerful CAS-like operation. It atomically
        // sets 'front_buffer' to the value of 'back_buffer' and returns
        // the old value of 'front_buffer'.
        back_buffer = atomic_exchange(&buffer->front_buffer, back_buffer);

        // Now, 'back_buffer' points to the old front buffer, ready for the next update.

        // Simulate a high-frequency game loop (~200 FPS).
        usleep(5000); // 5ms delay
    }

    printf("Simulation thread finished.\n");
    return NULL;
}

// --- Network Thread (The Reader) ---
// This function simply reads the state from whatever the 'front_buffer'
// pointer is currently pointing to. This read is atomic and lock-free.
void* network_send(void* arg) {
    LockFreeBuffer* buffer = (LockFreeBuffer*)arg;
    
    printf("Network thread started.\n");

    while (is_running) {
        // --- Atomically read the pointer to the latest stable state ---
        CubeState* state_to_send = atomic_load(&buffer->front_buffer);
        
        // "Send" the data by printing it.
        // We read a consistent, complete state without any locks.
        // The tick count will jump, demonstrating that we are only ever
        // sending the absolute latest completed state.
        printf("--> Sending network packet: Tick %d, X=%.2f, Y=%.2f, RotZ=%.1f\n",
               state_to_send->update_tick,
               state_to_send->x,
               state_to_send->y,
               state_to_send->rotation_z);

        // Simulate a fixed network send rate (20 packets per second).
        usleep(50000); // 50ms delay
    }

    printf("Network thread finished.\n");
    return NULL;
}

// --- Main Function ---
int main() {
    pthread_t sim_thread, net_thread;
    LockFreeBuffer shared_buffer;

    // Initialize the buffer structures.
    CubeState initial_state = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0};
    shared_buffer.buffers[0] = initial_state;
    shared_buffer.buffers[1] = initial_state;

    // Atomically set the initial front buffer.
    atomic_init(&shared_buffer.front_buffer, &shared_buffer.buffers[0]);
    
    // Create and start the threads.
    pthread_create(&sim_thread, NULL, update_simulation, &shared_buffer);
    pthread_create(&net_thread, NULL, network_send, &shared_buffer);

    // Let the simulation run for a few seconds.
    printf("Lock-free simulation running for 3 seconds...\n");
    sleep(3);

    // Signal threads to stop and wait for them to exit.
    is_running = false;
    pthread_join(sim_thread, NULL);
    pthread_join(net_thread, NULL);

    printf("Program finished.\n");
    return 0;
}

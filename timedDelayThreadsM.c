/*
 * timedDelayThreadsM.c - Multithreaded TCP Server
 * Author:  Harry Joseph
 * ID:      N00881767
 * Course:  CPAN-226 (Networking & Telecommunications)
 * Lab:     04 - Task 2: Multithreaded Server
 *
 * Changes from timedDelayNothreads.c:
 *   - Added pthread.h
 *   - handle_client() now has signature void* handle_client(void* arg)
 *     to be compatible with pthread_create
 *   - Created client_args_t struct to pass socket + client_id to thread
 *   - In main(), replaced direct handle_client() call with pthread_create()
 *     + pthread_detach() so each client is handled concurrently and thread
 *     resources are reclaimed automatically when done
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#define sleep(x) Sleep(1000 * (x))
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

#define PORT 8080

/* Struct to bundle arguments passed to each thread */
typedef struct {
    SOCKET client_socket;
    int    client_id;
} client_args_t;

/* Thread function — same logic as before, now runs concurrently per client */
void* handle_client(void* arg) {
    client_args_t* args = (client_args_t*)arg;
    SOCKET client_socket = args->client_socket;
    int    client_id     = args->client_id;
    free(args);  /* free heap-allocated struct */

    char *message = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\nConnection: close\r\n\r\nHello Client!";

    printf("[Server] Handling client %d in its own thread...\n", client_id);
    printf("[Server] Processing request for 5 seconds (client %d)...\n", client_id);
    sleep(5);

    send(client_socket, message, (int)strlen(message), 0);
    printf("[Server] Response sent to client %d. Closing connection.\n", client_id);

#ifdef _WIN32
    closesocket(client_socket);
#else
    close(client_socket);
#endif
    return NULL;
}

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
    int client_count = 0;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("[Server] ERROR: Failed to create socket.\n");
        return 1;
    }
    printf("[Server] Socket created successfully.\n");

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("[Server] ERROR: Bind failed.\n");
        return 1;
    }
    printf("[Server] Bind successful.\n");

    if (listen(server_socket, 10) == SOCKET_ERROR) {
        printf("[Server] ERROR: Listen failed.\n");
        return 1;
    }
    printf("[Server] Listen successful.\n\n");

    printf("Server listening on port %d...\n", PORT);
    printf("NOTE: This server is MULTITHREADED. Each client gets its own thread!\n\n");

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket != INVALID_SOCKET) {
            client_count++;

            /* Allocate args on heap so each thread has its own copy */
            client_args_t* args = malloc(sizeof(client_args_t));
            args->client_socket = client_socket;
            args->client_id     = client_count;

            pthread_t thread;
            pthread_create(&thread, NULL, handle_client, args);
            /* Detach so OS reclaims thread resources automatically on exit */
            pthread_detach(thread);
        }
    }

#ifdef _WIN32
    closesocket(server_socket);
    WSACleanup();
#else
    close(server_socket);
#endif
    return 0;
}

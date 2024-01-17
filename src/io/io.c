#include "../header/io.h"

void check(int val, char * errorMsg){
    if(val<0){
        printf("ERROR: %s failed!\n", errorMsg);
        exit(EXIT_FAILURE);
    }
}


void * handleConnection(void* sock_desc){
    ssize_t read_size;
    ssize_t write_size;
    char input[BUFFER_SIZE];
    char output[BUFFER_SIZE];

    int client_socket = *((int *)sock_desc); 
    printf("handle client: %d\n", client_socket);

    while((read_size=read(client_socket, input, BUFFER_SIZE))>0){
        ADAPTER(input, output, read_size, &write_size);
        send(client_socket, output, write_size,0);
    }

    printf("closing client: %d\n",client_socket);
    close(client_socket);

   return 0; 
}

int createSocket(int port, IOFUNC adapter_function){
    int server_socket;
    int client_socket;
    int opt = 1;
    struct sockaddr_in server_address, client_address;
    socklen_t addrlen = sizeof(client_address);


    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "socket");
    check(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)), "setsockopt");
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);
    check(bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)),"bind");
    check(listen(server_socket, BACKLOG), "listen");

    if(adapter_function != 0){
        ADAPTER = adapter_function;
    }

    pthread_t tid;
    while(1){
        check((client_socket = accept(server_socket, (struct sockaddr*)&client_address, &addrlen)), "accept");
        printf("accept successful!\n");

        check(pthread_create(&tid, NULL, handleConnection, (void *)&client_socket),"pthread");
        printf("tid: %ld work!\n", (long int) tid);
    }

    printf("closing server: %d\n", server_socket);
    close(server_socket);
    return server_socket;
}


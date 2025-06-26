#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>


int main(){
    //AF_INET = IPv4
    //SOCK_STREAM = This is a reliable, 
    //              ordered transmission of 
    //              bytes in full duplex mode.
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket <0){
        perror("|  Socket dosen't work  |\n");
        return -1;
        
    }
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8888);

    if(bind(server_socket, (struct sockaddr*)&address, sizeof(address)) <0){
        perror("Bind failed\n");
        close(server_socket);
        return -1;
    }

    if(listen(server_socket, 1)<0){
        perror("Lister failed\n");
        close(server_socket);
        return -1;
    }

    printf("Listening on port 8888\n");

    struct sockaddr_in client_add;
    socklen_t client_add_len = sizeof(client_add);
    int client_socket = accept(server_socket, (struct sockaddr*)&client_add, &client_add_len);
    if(client_socket<0){
        perror("Client failed\n");
        close(server_socket);
        return -1;
    }

    printf("Client connected\n");

    char buff[1024] = {0};
    int bytes_read = recv(client_socket , buff,sizeof(buff),0);
    if(bytes_read<0){
        perror("Read failed\n");
        close(client_socket);
        close(server_socket);
        return -1;
    }

    printf("Massage : |%s|\n",buff);

    const char* responce = "Hi User :)";
    if(send(client_socket , responce,strlen(responce), 0)<0){
        perror("Send failed\n");
        close(client_socket);
        close(server_socket);
        return -1;
    }
    close(client_socket);
    close(server_socket);
    printf("Good bye!");

    return 0;
}
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
        perror("|  Socket dosen't work  |");
        return -1;
        
    }
    return 0;
}
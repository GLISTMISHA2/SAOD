#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockett = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockett, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Ошибка привязки");
        close(sockett);
        return 1;
    }

    
    printf("порт 8080\n");

    if (listen(sockett, 5) < 0) {
        perror("Ошибка");
        close(sockett);
        return 1;
    }
    printf("Сервер слушает порт 8080\n\n");
    
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        char client_ip[16];
        
        int client = accept(sockett, (struct sockaddr*)&client_addr,&client_len);
        if (client < 0) {
            perror("Ошибка");
            continue;
        }
        
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
        printf("клиент: %s\n", client_ip);
        
        char buffer[1024];
        while (1) {
            memset(buffer, 0, sizeof(buffer));
            
            int bytes = recv(client, buffer, sizeof(buffer)-1, 0);
            printf("От %s: %s\n", client_ip, buffer);
            
            if (strcmp(buffer, "exit") == 0) {
                break;
            }
            char response[1100];
            snprintf(response, sizeof(response), "[ECHO]: %s\n", buffer);
    
            if (send(client, response, strlen(response), 0)<0) {
                perror("Ошибка");
                break;
            }
            printf("отправленно клиенту %s: %s", client_ip, response);
        }
        close(client);
    }
    
    close(sockett);
}
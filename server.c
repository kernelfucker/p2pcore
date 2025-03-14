/* p2pcore - classic peer-to-peer program

   server.c

   written by kernelfucker
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 9000

void handle_peer(int socket){
	char buffer[BUFFER_SIZE];
	int bytes_received;

	while (1) {
		bytes_received = recv(socket, buffer, BUFFER_SIZE, 0);
		if (bytes_received <= 0){
	break;
}

		buffer[bytes_received] = '\0';
		printf("Received message: %s\n", buffer);

		char* message = "Thats peer!";
		send(socket, message, strlen(message), 0);
	}
}

int main(){
	int server_socket, client_socket;
	struct sockaddr_in server_address, client_address;
	socklen_t client_address_length = sizeof(client_address);
	
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0){
		perror("Socket creation failed.");
	exit(1);
}

server_address.sin_family = AF_INET;
server_address.sin_port = htons(PORT);
inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
		perror("Bind failed");
	exit(1);
}

if (listen(server_socket, 1) < 0){
		perror("Listen failed");
	exit(1);
}

printf("Server listening on port %d...\n", PORT);

client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
if (client_socket < 0){
		perror("Accept failed");
	exit(1);
}

printf("Connection accepted from client IP address %s and port %d...\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

handle_peer(client_socket);

close(client_socket);
close(server_socket);

return 0;
}

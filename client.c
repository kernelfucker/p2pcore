/* p2pcore - classic peer-to-peer program

   client.c

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

int main(){
	int client_socket;
	struct sockaddr_in server_address;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0){
		perror("Socket creation failed");
	exit(1);
}

server_address.sin_family = AF_INET;
server_address.sin_port = htons(PORT);
inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
		perror("Connection failed");
	exit(1);
}

printf("Connected to server...\n");

char* message = "Hello from client!";
send(client_socket, message, strlen(message), 0);

char buffer[BUFFER_SIZE];
int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
if (bytes_received <= 0){
		perror("recv failed");
	exit(1);
}
buffer[bytes_received] = '\0';
printf("Received response: %s\n", buffer);

close(client_socket);

return 0;
}

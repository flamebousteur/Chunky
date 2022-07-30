// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define TRUE 1
#define FALSE 0
#define CHARS sizeof(char)

char* getfile (char *fileName, long int lenght) {
	FILE *fptr;
	// if the file is found, return the content of the file
	if ((fptr = fopen(fileName, "r")) != NULL) {
		fseek(fptr, 0, SEEK_END);
		long int res = ftell(fptr);
		fseek(fptr, 0, SEEK_SET);
		lenght = (lenght > res || lenght == 0) ? res : lenght;
		char* chs = (char*)calloc(CHARS, lenght + 1);
		fread(chs, CHARS, lenght, fptr);
		// close the file
		fclose(fptr);
		// add the null char
		chs[lenght] = 0;
		return chs;
	} else return NULL;
}

void* startServer (int port) {
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	char message[] = "test";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed\n");
		exit(EXIT_FAILURE);
	} else printf("socket ok\n");

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt\n");
		exit(EXIT_FAILURE);
	} else printf("socket on %d\n", port);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("bind failed\n");
		exit(EXIT_FAILURE);
	} else printf("bind succes\n");
	if (listen(server_fd, 3) < 0) {
		perror("listen\n");
		exit(EXIT_FAILURE);
	}
	do {
		if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
			perror("accept\n");
			exit(EXIT_FAILURE);
		} else printf("stream on\n");
		valread = read(new_socket, buffer, 1024);
		printf("====================from client====================\n%s\n===================================================\n", buffer);
		char* filename = (char*)"./data";
		char* filedata = getfile(filename, 0);
		if (filedata != NULL) send(new_socket, filedata, strlen(filedata), 0);
		else {
			char* str = "file not found";
			send(new_socket, str, strlen(str), 0);
		}
		printf("responce sent\n");
// closing the connected socket
		close(new_socket);
	} while (1);

// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
}

int main(int argc, char const* argv[]) {
	startServer(8080);
	return 0;
}
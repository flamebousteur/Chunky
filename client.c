// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

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

int main(int argc, char const* argv[]) {
	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	char* filename = (char*)"./data";
	char* filedata = getfile(filename, 0);
	if (filedata != NULL) send(sock, filedata, strlen(filedata), 0);
	else {
		char* str = "file not found";
		send(sock, str, strlen(str), 0);
	}
	printf("== Hello message sent ==\n%s\n");

	valread = read(sock, buffer, 1024);
	printf("%s\n", buffer);

	// closing the connected socket
	close(client_fd);
	return 0;
}


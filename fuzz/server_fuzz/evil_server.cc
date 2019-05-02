#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define SERV_PORT 1232

void send_data(int clisocket, char *fileName) {
	FILE * fp;
    uint8_t *Data;
    size_t Size;

    //opens the file, get its size, and reads it into a buffer
    fp = fopen(fileName, "rb");
    if (fp == NULL) {
        return;
    }
    if (fseek(fp, 0L, SEEK_END) != 0) {
        fclose(fp);
        return;
    }
    Size = ftell(fp);
    if (Size == (size_t) -1) {
        fclose(fp);
        return;
    }
    if (fseek(fp, 0L, SEEK_SET) != 0) {
        fclose(fp);
        return;
    }
    Data = (uint8_t*)malloc(Size*sizeof(uint8_t));
    if (Data == NULL) {
        fclose(fp);
        return;
    }
    if (fread(Data, Size, 1, fp) != 1) {
        fclose(fp);
        free(Data);
        return;
    }
    write(clisocket, Data, Size);
}

int main(int argc, char **argv) {
	int serverSocket;

	if ((serverSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("erreur socket");
		exit(1);
	}

	struct sockaddr_in serv_addr;

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_PORT);

	if (bind(serverSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0) {
		perror("erreur bind\n");
		exit(1);
	}

	if (listen(serverSocket, SOMAXCONN) < 0) {
		perror("erreur de listen\n");
	}

	int dialogSocket;
	int clilen;
	struct sockaddr_in cli_addr;

	clilen = sizeof(cli_addr);

	dialogSocket = accept(serverSocket, (struct sockaddr*)&cli_addr, (socklen_t*)&clilen);
	if (dialogSocket < 0) {
		perror("erreur accept.");
		exit(1);
	}

	//We have accepted things. Let's read crash file...
	send_data(dialogSocket, argv[1]);

	char buf[500];
	int size = 0;
	while ((size=read(dialogSocket, buf, 499)) > 0) printf("%d",size); 

	close(dialogSocket);
	close(serverSocket);
}
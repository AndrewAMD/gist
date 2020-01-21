/*

This is a prototype hack job. Do not use this code in production.

This builds in Visual Studio 2017, using Winsock2, LibreSSL, and the DTC protocol.

-AMD

*/


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "tls.lib")
#pragma comment (lib, "ssl.lib")
#pragma comment (lib, "crypto.lib")


//#include<stdio.h>
//#include "tls.h"
//
//void main(void) {
//	printf("hello world");
//
//}




#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>

#include <memory.h>
#include <float.h>
#include "DTCProtocol.h"


struct s_Header
{
	uint16_t Size = 0;
	uint16_t Type = 0;
};



#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>

//#include <poll.h>

#include <WinSock2.h>
#include <ws2def.h>

#include <tls.h>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

int main(int argc, char **argv) {

	//WSADATA wsaData;
	//SOCKET ConnectSocket = INVALID_SOCKET;

	//int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	//if (iResult != 0) {
	//	printf("WSAStartup failed with error: %d\n", iResult);
	//	return 1;
	//}

	struct tls *tls = NULL;
	struct tls_config *config = NULL;
	//const char *msg = "HELLO TLS SERVER!\n";

	DTC::s_LogonRequest rq;
	rq.SetClientName("AndrewAMD");


	ssize_t outlen = 0;
	char bufs[1000], bufc[1000];
	struct sockaddr_in server;
	struct pollfd pfd[2];


	tls_init();

	tls = tls_client();

	config = tls_config_new();

	tls_config_insecure_noverifycert(config);
	tls_config_insecure_noverifyname(config);

	tls_configure(tls, config);

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_port = htons(11099);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;

	if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("erro socket\n");
		exit(1);
	}

	if (tls_connect_socket(tls, sock, "localhost") < 0) {
		printf("tls_connect error\n");
		printf("%s\n", tls_error(tls));
		exit(1);
	}


	tls_write(tls, &rq, sizeof(rq));

	pfd[0].fd = 0;
	pfd[0].events = POLLIN;
	pfd[1].fd = sock;
	pfd[1].events = POLLIN;

	while (bufc[0] != ':' && bufc[1] != 'q') {
		bzero(bufs, 1000);
		bzero(bufc, 1000);

		//poll(pfd, 2, -1);
		WSAPoll(pfd, 2, -1);

		if (pfd[0].revents & POLLIN) {
			//int q = read(0, bufc, 1000);
			int q = recv(0, bufc, 1000, 0);
			tls_write(tls, bufc, q);
		}

		if (pfd[1].revents & POLLIN) {
			bool need_to_quit = false;
			if ((outlen = tls_read(tls, bufs, 1000)) <= 0) break;
			s_Header* pH = (s_Header*)bufs;
			switch (pH->Type) {
			case DTC::LOGON_RESPONSE: {
				DTC::s_LogonResponse m;
				m.CopyFrom(bufs);
				printf("received logon response\n");
				printf("result: %s\n", m.GetResultText());
				printf("server name: %s\n", m.GetServerName());
				break;
			}
			case DTC::HEARTBEAT: {
				DTC::s_Heartbeat m;
				m.CopyFrom(bufs);
				printf("received heartbeat\n");
				DTC::s_Heartbeat m2;
				tls_write(tls, &m2, sizeof(m2));
				printf("sent heartbeat\n");
				break;
			}
			case DTC::LOGOFF: {
				DTC::s_Logoff m;
				m.CopyFrom(bufs);
				printf("received logoff\n");
				printf("reason: %s\n", m.GetReason());
				need_to_quit = true;
				break;
			}
			}
			if (need_to_quit) break;
		}
	}

	tls_close(tls);
	tls_free(tls);
	tls_config_free(config);

	//WSACleanup();

	return 0;
}

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")

#define BUFFER_SIZE 256

//STEP1	同端末通信	OK
//STEP2	LAN通信		OK
//STEP3	WAN通信		調査中

int main()
{
	/* ポート番号、ソケット */
	unsigned short port = 20000;
	int srcSocket;  // 自分
	int dstSocket;  // 相手
	int status;

	/* sockaddr_in 構造体 */
	struct sockaddr_in srcAddr;
	struct sockaddr_in dstAddr;
	int dstAddrSize = sizeof(dstAddr);

	/* 各種パラメータ */
	int numrcv;
	char buffer[BUFFER_SIZE];

	/************************************************************/
	/* Windows 独自の設定 */
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);

	/* sockaddr_in 構造体のセット */
	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_port = htons(port);
	srcAddr.sin_family = AF_INET;
	srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	/* ソケットの生成 */
	srcSocket = socket(AF_INET, SOCK_STREAM, 0);

	/* ソケットのバインド */
	bind(srcSocket, (struct sockaddr *) &srcAddr, sizeof(srcAddr));

	/* 接続の許可 */
	listen(srcSocket, 1);

	/* 接続の受付け */
	printf("Waiting for connection ...\n");
	dstSocket = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
	char addr[80] = { NULL };
	inet_ntop(AF_INET, &dstAddr.sin_addr, addr, dstAddrSize);
	printf("Connected from %s\n", addr);

	/* パケット受信 */
	while (1) {
		numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0);
		if (numrcv == 0 || numrcv == -1) {
			status = closesocket(dstSocket); break;
		}
		printf("received: %s\n", buffer);
	}

	/* Windows 独自の設定 */
	WSACleanup();
}
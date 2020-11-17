#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>

#pragma comment (lib, "Ws2_32.lib")

#define BUFFER_SIZE 256
#define CONNECT_MAX 4

//STEP1	同端末通信	OK
//STEP2	LAN通信		OK
//STEP3	WAN通信		OK

int main()
{
	/* ポート番号、ソケット */
	unsigned short port = 27015;
	int srcSocket;  // 自分
	int dstSocket[CONNECT_MAX];  // 相手

	/* sockaddr_in 構造体 */
	struct sockaddr_in srcAddr;//自分のアドレス
	struct sockaddr_in dstAddr[CONNECT_MAX];//相手のアドレス
	int dstAddrSize = sizeof(dstAddr[0]);

	/* 各種パラメータ */
	int numrcv;
	//char buffer[BUFFER_SIZE]; //送られてくるデータ内容

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

	// ここで、ノンブロッキングに設定しています。
	 // val = 0でブロッキングモードに設定できます。
	 // ソケットの初期設定はブロッキングモードです。
	u_long val = 1;
	ioctlsocket(srcSocket, FIONBIO, &val);



	//----------------------------マッチング信号　ステップ1
	bool ChkMatch = false;
	bool ChkConnect[CONNECT_MAX] = { false };
	int ConnectOK = 0;
	char toSendText[1024];
	while (ChkMatch != true)
	{
		for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
		{
			char ConnectRMsg[BUFFER_SIZE]; //送られてくるデータ内容
			ConnectRMsg[0] = NULL;
			//接続が確立されていない
			if (ChkConnect[ConnectCnt] == false)
			{
				dstSocket[ConnectCnt] = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
				char addr[80] = { NULL };
				inet_ntop(AF_INET, &dstAddr[ConnectCnt].sin_addr, addr, dstAddrSize);
				sprintf_s(addr, "%s%d", addr, ConnectCnt);
				printf("from %s\n", addr);
				/* パケット受信 */
				numrcv = recv(dstSocket[ConnectCnt], ConnectRMsg, BUFFER_SIZE, 0);
				if (numrcv < 1)
				{
					if (WSAGetLastError() == WSAEWOULDBLOCK)
					{
						// まだ来ない。
						//printf("MADA KONAI\n");
					}
					else
					{
						//printf("error : 0x%x\n", WSAGetLastError());
					}
				}
				else
				{
					ChkConnect[ConnectCnt] = true;
					printf("received data\n");
					printf("%s\n", ConnectRMsg);
					//コネクト数をカウントして4になると全員の接続が完了
					ConnectOK++;
					//マッチング待ち(人数待ち)を相手に送る
					sprintf_s(toSendText, "%d", ConnectOK);
					send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
				}
			}
			//接続が確立されてる
			else
			{
				//マッチング待ち(人数待ち)を相手に送る
				sprintf_s(toSendText, "%d", ConnectOK);
				send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
			}
			if (ConnectOK == CONNECT_MAX)
			{
				ChkMatch = true;
				printf("4人マッチング完了\n");
				//人数にが揃ったら5を送ってマッチング確定合図とする
				sprintf_s(toSendText, "%d", 5);
				for (int Cnt = 0; Cnt < CONNECT_MAX; Cnt++)
				{
					send(dstSocket[Cnt], toSendText, strlen(toSendText) + 1, 0);
				}
			}
			// とりあえず待ってみる
			Sleep(100);
		}
	}
	//----------------------------マッチング信号


	//----------------------------個人番号信号　ステップ2
	bool ChkMyNum = false;
	bool ChkMyNumRecv[CONNECT_MAX] = { false };
	int MyNumOK = 0;
	while (ChkMyNum != true)
	{
		for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
		{
			char MyNumChkRMsg[BUFFER_SIZE]; //送られてくるデータ内容
			MyNumChkRMsg[0] = NULL;
			if (ChkMyNumRecv[ConnectCnt] == true) continue;
			//個人番号合図を送る
			sprintf_s(toSendText, "MyNum%d", ConnectCnt);
			send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
			numrcv = recv(dstSocket[ConnectCnt], MyNumChkRMsg, BUFFER_SIZE, 0);
			if (numrcv < 1)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					// まだ来ない。
					//printf("MADA KONAI\n");
				}
				else
				{
					//printf("error : 0x%x\n", WSAGetLastError());
				}
			}
			else
			{
				if (strcmp(MyNumChkRMsg, "OK") == 0)
				{
					//個人番号を受けっとた合図が返ってきたらここでカウント増やす
					ChkMyNumRecv[ConnectCnt] = true;
					MyNumOK++;
					//みんな確認取れたら次のステップへ
					if (MyNumOK >= CONNECT_MAX) ChkMyNum = true;
				}
				char addr[80] = { NULL };
				inet_ntop(AF_INET, &dstAddr[ConnectCnt].sin_addr, addr, dstAddrSize);
				sprintf_s(addr, "%s%d", addr, ConnectCnt);
				printf("from %s\n", addr);
				printf("%s\n", MyNumChkRMsg);
			}
			// とりあえず待ってみる
			Sleep(100);
		}
	}
	//----------------------------個人番号信号



	//----------------------------カウントダウンスタート信号　ステップ3
	//カウントダウン開始の合図を送る
	bool ChkStart = false;
	bool ChkStartRecv[CONNECT_MAX] = { false };
	int StartOK = 0;
	while (ChkStart != true)
	{
		for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
		{
			char CountChkRMsg[BUFFER_SIZE]; //送られてくるデータ内容
			CountChkRMsg[0] = NULL;
			if (ChkStartRecv[ConnectCnt] == true) continue;
			//個人番号合図を送る
			sprintf_s(toSendText, "Start");
			send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
			numrcv = recv(dstSocket[ConnectCnt], CountChkRMsg, BUFFER_SIZE, 0);
			if (numrcv < 1)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					// まだ来ない。
					printf("MADA KONAI\n");
				}
				else
				{
					printf("error : 0x%x\n", WSAGetLastError());
				}
			}
			else
			{
				if (strcmp(CountChkRMsg, "OK") == 0)
				{
					//個人番号を受けっとた合図が返ってきたらここでカウント増やす
					ChkStartRecv[ConnectCnt] = true;
					StartOK++;
					//みんな確認取れたら次のステップへ
					if (StartOK >= CONNECT_MAX) ChkMyNum = true;
				}
				printf("ゲーム開始\n");
				printf("%s\n", CountChkRMsg);
			}
		}
	}
	//----------------------------カウントダウンスタート信号




	//----------------------------ゲーム中信号　ステップ4
	//ゲームが終わるまでループ
	bool ChkGameEnd = false;
	while (ChkGameEnd != true)
	{
		for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
		{
			char GameRMsg[BUFFER_SIZE]; //送られてくるデータ内容
			GameRMsg[0] = NULL;
			//カウントダウン開始の合図を送る
			sprintf_s(toSendText, "Start");
			//send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
			numrcv = recv(dstSocket[ConnectCnt], GameRMsg, BUFFER_SIZE, 0);
			if (numrcv < 1)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					// まだ来ない。
					//printf("MADA KONAI\n");
				}
				else
				{
					//printf("error : 0x%x\n", WSAGetLastError());
					break;
				}
			}
			else
			{
				//printf("received data\n");
				//printf("%s\n", buffer);
				break;
			}
		}
	}
	//----------------------------ゲーム中信号



	/* Windows 独自の設定 */
	WSACleanup();
}
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>

#pragma comment (lib, "Ws2_32.lib")

#define BUFFER_SIZE 256
#define CONNECT_MAX 4

//STEP1	���[���ʐM	OK
//STEP2	LAN�ʐM		OK
//STEP3	WAN�ʐM		OK

int main()
{
	/* �|�[�g�ԍ��A�\�P�b�g */
	unsigned short port = 27015;
	int srcSocket;  // ����
	int dstSocket[CONNECT_MAX];  // ����

	/* sockaddr_in �\���� */
	struct sockaddr_in srcAddr;//�����̃A�h���X
	struct sockaddr_in dstAddr[CONNECT_MAX];//����̃A�h���X
	int dstAddrSize = sizeof(dstAddr[0]);

	/* �e��p�����[�^ */
	int numrcv;
	char buffer[BUFFER_SIZE]; //�����Ă���f�[�^���e

	/************************************************************/
	/* Windows �Ǝ��̐ݒ� */
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);

	/* sockaddr_in �\���̂̃Z�b�g */
	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_port = htons(port);
	srcAddr.sin_family = AF_INET;
	srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	/* �\�P�b�g�̐��� */
	srcSocket = socket(AF_INET, SOCK_STREAM, 0);

	/* �\�P�b�g�̃o�C���h */
	bind(srcSocket, (struct sockaddr *) &srcAddr, sizeof(srcAddr));

	/* �ڑ��̋��� */
	listen(srcSocket, 1);

	/* �ڑ��̎�t�� */
	printf("Waiting for connection ...\n");

	// �����ŁA�m���u���b�L���O�ɐݒ肵�Ă��܂��B
	 // val = 0�Ńu���b�L���O���[�h�ɐݒ�ł��܂��B
	 // �\�P�b�g�̏����ݒ�̓u���b�L���O���[�h�ł��B
	u_long val = 1;
	ioctlsocket(srcSocket, FIONBIO, &val);



	//----------------------------�}�b�`���O
	bool ChkMatch = false;
	bool ChkConnect[CONNECT_MAX] = { false };
	int ConnectOK = 0;
	char toSendText[1024];
	while (ChkMatch != true)
	{
		for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
		{
			//�ڑ����m������Ă��Ȃ�
			if (ChkConnect[ConnectCnt] == false)
			{
				dstSocket[ConnectCnt] = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
				char addr[80] = { NULL };
				inet_ntop(AF_INET, &dstAddr[ConnectCnt].sin_addr, addr, dstAddrSize);
				//printf("Connected from %s\n", addr);
				/* �p�P�b�g��M */
				numrcv = recv(dstSocket[ConnectCnt], buffer, BUFFER_SIZE, 0);
				if (numrcv < 1)
				{
					if (WSAGetLastError() == WSAEWOULDBLOCK)
					{
						// �܂����Ȃ��B
						printf("MADA KONAI\n");
					}
					else
					{
						printf("error : 0x%x\n", WSAGetLastError());
					}
				}
				else
				{
					ChkConnect[ConnectCnt] = true;
					printf("received data\n");
					printf("%s\n", buffer);
					//�R�l�N�g�����J�E���g����4�ɂȂ�ƑS���̐ڑ�������
					ConnectOK++;
					//�}�b�`���O�҂�(�l���҂�)�𑊎�ɑ���
					sprintf_s(toSendText, "%d", ConnectOK);
					send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
					if (ConnectOK == 4)
					{
						ChkMatch = true;
						printf("4�l�}�b�`���O����\n");
						sprintf_s(toSendText, "%d", ConnectOK);
						for (int Cnt = 0; Cnt < CONNECT_MAX; Cnt++)
						{
							send(dstSocket[Cnt], toSendText, strlen(toSendText) + 1, 0);
						}
					}
				}
			}
			//�ڑ����m������Ă�
			else
			{
				//�}�b�`���O�҂�(�l���҂�)�𑊎�ɑ���
				sprintf_s(toSendText, "%d", ConnectOK);
				send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
			}
			// �Ƃ肠������b�҂��Ă݂�
			Sleep(1000);
		}
	}
	//----------------------------�}�b�`���O




	//----------------------------�Q�[���J�n
	bool ChkGame = false;
	while (ChkGame != true)
	{
		for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
		{
			numrcv = recv(dstSocket[ConnectCnt], buffer, BUFFER_SIZE, 0);
			if (numrcv < 1)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					// �܂����Ȃ��B
					printf("MADA KONAI\n");
				}
				else
				{
					printf("error : 0x%x\n", WSAGetLastError());
					break;
				}
			}
			else
			{
				printf("received data\n");
				printf("%s\n", buffer);
				break;
			}
		}
	}
	//----------------------------�Q�[���J�n










	/* Windows �Ǝ��̐ݒ� */
	WSACleanup();
}
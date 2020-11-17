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
	//char buffer[BUFFER_SIZE]; //�����Ă���f�[�^���e

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



	//----------------------------�}�b�`���O�M���@�X�e�b�v1
	bool ChkMatch = false;
	bool ChkConnect[CONNECT_MAX] = { false };
	int ConnectOK = 0;
	char toSendText[1024];
	while (ChkMatch != true)
	{
		for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
		{
			char ConnectRMsg[BUFFER_SIZE]; //�����Ă���f�[�^���e
			ConnectRMsg[0] = NULL;
			//�ڑ����m������Ă��Ȃ�
			if (ChkConnect[ConnectCnt] == false)
			{
				dstSocket[ConnectCnt] = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
				char addr[80] = { NULL };
				inet_ntop(AF_INET, &dstAddr[ConnectCnt].sin_addr, addr, dstAddrSize);
				sprintf_s(addr, "%s%d", addr, ConnectCnt);
				printf("from %s\n", addr);
				/* �p�P�b�g��M */
				numrcv = recv(dstSocket[ConnectCnt], ConnectRMsg, BUFFER_SIZE, 0);
				if (numrcv < 1)
				{
					if (WSAGetLastError() == WSAEWOULDBLOCK)
					{
						// �܂����Ȃ��B
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
					//�R�l�N�g�����J�E���g����4�ɂȂ�ƑS���̐ڑ�������
					ConnectOK++;
					//�}�b�`���O�҂�(�l���҂�)�𑊎�ɑ���
					sprintf_s(toSendText, "%d", ConnectOK);
					send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
				}
			}
			//�ڑ����m������Ă�
			else
			{
				//�}�b�`���O�҂�(�l���҂�)�𑊎�ɑ���
				sprintf_s(toSendText, "%d", ConnectOK);
				send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
			}
			if (ConnectOK == CONNECT_MAX)
			{
				ChkMatch = true;
				printf("4�l�}�b�`���O����\n");
				//�l���ɂ���������5�𑗂��ă}�b�`���O�m�荇�}�Ƃ���
				sprintf_s(toSendText, "%d", 5);
				for (int Cnt = 0; Cnt < CONNECT_MAX; Cnt++)
				{
					send(dstSocket[Cnt], toSendText, strlen(toSendText) + 1, 0);
				}
			}
			// �Ƃ肠�����҂��Ă݂�
			Sleep(100);
		}
	}
	//----------------------------�}�b�`���O�M��


	//----------------------------�l�ԍ��M���@�X�e�b�v2
	bool ChkMyNum = false;
	bool ChkMyNumRecv[CONNECT_MAX] = { false };
	int MyNumOK = 0;
	while (ChkMyNum != true)
	{
		for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
		{
			char MyNumChkRMsg[BUFFER_SIZE]; //�����Ă���f�[�^���e
			MyNumChkRMsg[0] = NULL;
			if (ChkMyNumRecv[ConnectCnt] == true) continue;
			//�l�ԍ����}�𑗂�
			sprintf_s(toSendText, "MyNum%d", ConnectCnt);
			send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
			numrcv = recv(dstSocket[ConnectCnt], MyNumChkRMsg, BUFFER_SIZE, 0);
			if (numrcv < 1)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					// �܂����Ȃ��B
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
					//�l�ԍ����󂯂��Ƃ����}���Ԃ��Ă����炱���ŃJ�E���g���₷
					ChkMyNumRecv[ConnectCnt] = true;
					MyNumOK++;
					//�݂�Ȋm�F��ꂽ�玟�̃X�e�b�v��
					if (MyNumOK >= CONNECT_MAX) ChkMyNum = true;
				}
				char addr[80] = { NULL };
				inet_ntop(AF_INET, &dstAddr[ConnectCnt].sin_addr, addr, dstAddrSize);
				sprintf_s(addr, "%s%d", addr, ConnectCnt);
				printf("from %s\n", addr);
				printf("%s\n", MyNumChkRMsg);
			}
			// �Ƃ肠�����҂��Ă݂�
			Sleep(100);
		}
	}
	//----------------------------�l�ԍ��M��



	//----------------------------�J�E���g�_�E���X�^�[�g�M���@�X�e�b�v3
	//�J�E���g�_�E���J�n�̍��}�𑗂�
	bool ChkStart = false;
	bool ChkStartRecv[CONNECT_MAX] = { false };
	int StartOK = 0;
	while (ChkStart != true)
	{
		for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
		{
			char CountChkRMsg[BUFFER_SIZE]; //�����Ă���f�[�^���e
			CountChkRMsg[0] = NULL;
			if (ChkStartRecv[ConnectCnt] == true) continue;
			//�l�ԍ����}�𑗂�
			sprintf_s(toSendText, "Start");
			send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
			numrcv = recv(dstSocket[ConnectCnt], CountChkRMsg, BUFFER_SIZE, 0);
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
				if (strcmp(CountChkRMsg, "OK") == 0)
				{
					//�l�ԍ����󂯂��Ƃ����}���Ԃ��Ă����炱���ŃJ�E���g���₷
					ChkStartRecv[ConnectCnt] = true;
					StartOK++;
					//�݂�Ȋm�F��ꂽ�玟�̃X�e�b�v��
					if (StartOK >= CONNECT_MAX) ChkMyNum = true;
				}
				printf("�Q�[���J�n\n");
				printf("%s\n", CountChkRMsg);
			}
		}
	}
	//----------------------------�J�E���g�_�E���X�^�[�g�M��




	//----------------------------�Q�[�����M���@�X�e�b�v4
	//�Q�[�����I���܂Ń��[�v
	bool ChkGameEnd = false;
	while (ChkGameEnd != true)
	{
		for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
		{
			char GameRMsg[BUFFER_SIZE]; //�����Ă���f�[�^���e
			GameRMsg[0] = NULL;
			//�J�E���g�_�E���J�n�̍��}�𑗂�
			sprintf_s(toSendText, "Start");
			//send(dstSocket[ConnectCnt], toSendText, strlen(toSendText) + 1, 0);
			numrcv = recv(dstSocket[ConnectCnt], GameRMsg, BUFFER_SIZE, 0);
			if (numrcv < 1)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					// �܂����Ȃ��B
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
	//----------------------------�Q�[�����M��



	/* Windows �Ǝ��̐ݒ� */
	WSACleanup();
}
#include <stdio.h>
#include<time.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <math.h>
#include"../h/vec3.h"
#include "../h/library.h"

#pragma comment (lib, "Ws2_32.lib")

#define BUFFER_SIZE 500					//!< ���M�f�[�^�o�b�t�@�T�C�Y
#define BUFFER_SIZE_STRING 500			//!< ���M�f�[�^�o�b�t�@�T�C�Y
#define CONNECT_MAX 2					//!< �N���C�A���g��


#define DROP_ITEM_MAX 20				//!< �o��������A�C�e���̐�
#define ITEM_RESPOWNTIMEMAX 9600000		//!< �A�C�e���̃��X�|�[���^�C��

#define	ITEM_INIT_POSX						(700.0f)						//!< �������W�A�C�e��
#define	ITEM_INIT_POSY						(500.0f)						//!< �������W�A�C�e��
#define	ITEM_INIT_POSZ						(700.0f)						//!< �������W�A�C�e��
#define	WALL_INIT_POSX						(2600.0f)						//!< �������W��
#define	WALL_INIT_POSY						(0.0f)							//!< �������W��
#define	WALL_INIT_POSZ						(2600.0f)						//!< �������W��
#define	WALL_SIZE_X							(WALL_INIT_POSX*2)				//!< �ǂ̃T�C�YX
#define	WALL_SIZE_Y							(800.0f)						//!< �ǂ̃T�C�YY

#define	NUM_VERTEX_MAX						(1089)						//!< �����b�V�����_�̐�
#define	NUM_VERTEX_INDEX_MAX				(2172)						//!< �����b�V���C���f�b�N�X�̐�
#define	NUM_POLYGON_MAX						(2172)						//!< �����b�V���|���S���̐�
#define	NUM_BLOCK_FIELD_MAX					(32)						//!< �����b�V���̏c���u���b�N��
#define	SIZE_BLOCK_FIELD					(250.0f)					//!< �����b�V���̏c���u���b�N�T�C�Y

#define	SIZE_BLOCK_MAX						(8000)						//!< �����b�V���̃T�C�Y
#define	SIZE_BLOCK_HALF						(4000)						//!< �����b�V���̃T�C�Y
#define	SIZE_BLOCK_QUARTER					(2000)						//!< �����b�V���̃T�C�Y
#define	SIZE_BLOCK_EIGHTH					(1000)						//!< �����b�V���̃T�C�Y

#define	OBJECT_PLAYER_MAX					(4)							//!< �v���C���[�̐�

enum
{
	ITEMTYPE_TIKEI = 0,		// �n�`
	ITEMTYPE_LIFE,			// ���C�t
	ITEMTYPE_SENSYA,		// ���
	ITEMTYPE_BULLET,		// �o���b�g
	ITEMTYPE_SPEEDUP,		// �X�s�[�h�A�b�v
	ITEMTYPE_CAMERA,		// ���ז��A�C�e���@�����o�b�N�J����
	ITEMTYPE_KIRI,			// ���ז��A�C�e���@��
	ITEMTYPE_MAX
};

//WAN�v���g�R���̃|�[�g6432
//�|�[�g�J��
//�ő��300�o�C�g���炢
//sleep�����Ă���
//�đ����䂩�ƍ����䂪����
//upnp��off�ł���

//STEP1	���[���ʐM	OK
//STEP2	LAN�ʐM		OK
//STEP3	WAN�ʐM		OK

void GenerateFiled(VEC3 *PPOS, VEC3 *VTX, int IGetPlayer, DWORD *pIdx, bool *Tikei, int *IdxMsgBuff);


int main()
{
	srand((unsigned)time(NULL));

	//�g�p���̃A�C�e����
	int ItemCntUse = 0;
	bool ItemUse[DROP_ITEM_MAX];
	bool ItemScyncUse[DROP_ITEM_MAX];
	float ItemRespownTime = 0.0f;

	//�v���C���[���W 
	VEC3 PlayerPos[CONNECT_MAX];

	//�n�`�����ɕK�v�ȃf�[�^
	//VEC3 VTXPos[NUM_VERTEX_MAX];	//�n�`���W
	int TikeiItemGetPlayer = -1;	//�n�`�A�C�e�����擾�����v���C���[�ԍ�
	bool TikeiChange = false;		//true�̎��n�`����
	//DWORD FieldIdx[NUM_VERTEX_INDEX_MAX];	//�n�`���_�̃C���f�b�N�X
	int TikeiIdxMsgBuff[NUM_VERTEX_MAX / 2] = { -1 };	//���b�Z�[�W���钸�_�C���f�b�N�X�̃o�b�t�@

	while (1)
	{
		//������
		for (int i = 0; i < DROP_ITEM_MAX; i++) ItemUse[i] = true;
		for (int i = 0; i < DROP_ITEM_MAX; i++) ItemScyncUse[i] = true;
		ItemRespownTime = 0.0f;
		for (int i = 0; i < CONNECT_MAX; i++)
		{
			PlayerPos[i].x = 0.0f;
			PlayerPos[i].y = 0.0f;
			PlayerPos[i].z = 0.0f;
		}
		/*
		for (int ix = 0; ix < NUM_BLOCK_FIELD_MAX+1; ix++)
		{
			for (int iz = 0; iz < NUM_BLOCK_FIELD_MAX + 1; iz++)
			{
				VTXPos[iz * (NUM_BLOCK_FIELD_MAX + 1) + ix].x = -(NUM_BLOCK_FIELD_MAX / 2.0f) * SIZE_BLOCK_FIELD + ix * SIZE_BLOCK_FIELD;
				VTXPos[iz * (NUM_BLOCK_FIELD_MAX + 1) + ix].y = 0.0f;
				VTXPos[iz * (NUM_BLOCK_FIELD_MAX + 1) + ix].z = (NUM_BLOCK_FIELD_MAX / 2.0f) * SIZE_BLOCK_FIELD - iz * SIZE_BLOCK_FIELD;
			}
		}
		*/
		TikeiItemGetPlayer = -1;
		//TikeiChange = false;

		//���_�o�b�t�@�C���f�b�N�X�̐ݒ�
		/*
		int nCntIdx = 0;
		for (int nCntVtxZ = 0; nCntVtxZ < NUM_BLOCK_FIELD_MAX; nCntVtxZ++)
		{
			if (nCntVtxZ > 0)
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				FieldIdx[nCntIdx] = (nCntVtxZ + 1) * (NUM_BLOCK_FIELD_MAX + 1);
				nCntIdx++;
			}

			for (int nCntVtxX = 0; nCntVtxX < (NUM_BLOCK_FIELD_MAX + 1); nCntVtxX++)
			{
				FieldIdx[nCntIdx] = (nCntVtxZ + 1) * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX;
				nCntIdx++;
				FieldIdx[nCntIdx] = nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX;
				nCntIdx++;
			}

			if (nCntVtxZ < (NUM_BLOCK_FIELD_MAX - 1))
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				FieldIdx[nCntIdx] = nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + NUM_BLOCK_FIELD_MAX;
				nCntIdx++;
			}
		}
		*/

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
		//srcSocket = socket(AF_INET, SOCK_DGRAM, 0);

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


		char ItemSMsg[BUFFER_SIZE] = { NULL }; //�A�C�e����񑗂�f�[�^���e

		for (int nCntItem = 0; nCntItem < DROP_ITEM_MAX; nCntItem++)
		{
			//1�u���b�N21�����@21*20=420�T�C�Y
			VEC3 pos;
			pos.x = float(rand() % int(WALL_SIZE_X / 4)) + 100.0f;
			pos.z = float(rand() % int(WALL_SIZE_X / 4)) + 100.0f;
			int x = rand() % 2;
			int z = rand() % 2;
			if (x == 1) pos.x *= -1;
			if (z == 1) pos.z *= -1;

			int ItemTypeNum = rand() % ITEMTYPE_MAX;
			//���C�t�A�J�����A���A�C�e���̎��͂�����x���I
			if (ItemTypeNum == ITEMTYPE_LIFE && ItemTypeNum == ITEMTYPE_CAMERA && ItemTypeNum == ITEMTYPE_KIRI) ItemTypeNum = rand() % ITEMTYPE_MAX;
			char NewSMsg[BUFFER_SIZE] = { NULL }; //����f�[�^���e�@"@Item,%d,%d,X%d,Z%d&"
			sprintf_s(NewSMsg, "@I,N%d.T%d,X%d,Z%d&"
				, nCntItem, ItemTypeNum, int(pos.x), int(pos.z));
			sprintf_s(ItemSMsg, "%s%s", ItemSMsg, NewSMsg);
		}
		//�A�C�e���J�E���g������
		ItemCntUse = 20;

		//----------------------------�}�b�`���O�M���@�X�e�b�v1
		bool ChkMatch = false;
		bool ChkConnect[CONNECT_MAX] = { false };
		int ConnectOK = 0;
		char toSendText[BUFFER_SIZE];
		bool acceptFlag[CONNECT_MAX] = { false };
		while (ChkMatch != true)
		{
			for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
			{
				char ConnectRMsg[BUFFER_SIZE]; //�����Ă���f�[�^���e
				char addr[80] = { NULL };
				ConnectRMsg[0] = NULL;
				//�ڑ����m������Ă��Ȃ�
				if (ChkConnect[ConnectCnt] == false)
				{
					printf("STEP1 �R�l�N�g\n");
					if (acceptFlag[ConnectCnt] == false)
					{
						dstSocket[ConnectCnt] = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);

						if (dstSocket[ConnectCnt] != -1)
						{
							acceptFlag[ConnectCnt] = true;
						}
					}

					//�Ώۂ̃\�P�b�g����A�h���X�𔲂��o���\��
					//dstSocket[ConnectCnt] = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
					inet_ntop(AF_INET, &dstAddr[ConnectCnt].sin_addr, addr, dstAddrSize);
					sprintf_s(addr, "%s[%d]", addr, ConnectCnt);
					printf("from %s\n", addr);
					/* �p�P�b�g��M */
					numrcv = recv(dstSocket[ConnectCnt], ConnectRMsg, BUFFER_SIZE_STRING, 0);

					//�f�[�^���󂯎���Ă��Ȃ�
					if (numrcv < 1)
					{
						// ��u���b�L���O�œ��삵�Ă���̂Őڑ��m�F��receive���󂯎���Ă��Ȃ��Ƃ��ɂ����֗���
						if (WSAGetLastError() == WSAEWOULDBLOCK)
						{
							printf("error : 0x%x\n", WSAGetLastError());
						}
						//�ЂƂ܂��̏�Ԃ�\��
						else
						{
							printf("�����Ȃ� : 0x%x\n", WSAGetLastError());
						}
					}
					//�����receive�����Ƃ�
					else
					{
						ChkConnect[ConnectCnt] = true;
						printf("received data\n");
						printf("%s\n", ConnectRMsg);
						//�R�l�N�g�����J�E���g����4�ɂȂ�ƑS���̐ڑ�������
						ConnectOK++;
						//�}�b�`���O�҂�(�l���҂�)�𑊎�ɑ���
						sprintf_s(toSendText, "%d", ConnectOK);
						send(dstSocket[ConnectCnt], toSendText, BUFFER_SIZE_STRING, 0);
					}
				}
				//�ڑ����m������Ă�
				else
				{
					inet_ntop(AF_INET, &dstAddr[ConnectCnt].sin_addr, addr, dstAddrSize);
					sprintf_s(addr, "%s[%d]", addr, ConnectCnt);
					printf("�ڑ��m���@%s\n", addr);
					//�}�b�`���O�҂�(�l���҂�)�𑊎�ɑ���
					sprintf_s(toSendText, "%d", ConnectOK);
					send(dstSocket[ConnectCnt], toSendText, BUFFER_SIZE_STRING, 0);
				}

				//�l���ɂ���������m�����ꂽ�N���C�A���g��5�𑗂��ă}�b�`���O�m�荇�}�Ƃ���
				if (ConnectOK == CONNECT_MAX)
				{
					ChkMatch = true;
					printf("�}�b�`���O����\n");
					sprintf_s(toSendText, "%d", 5);
					//�����Ŋm�F�p�M�������񂩂�����Ȃ��Ǝ��s���鎞������
					for (int Cnt = 0; Cnt < CONNECT_MAX; Cnt++)
					{
						send(dstSocket[Cnt], toSendText, BUFFER_SIZE_STRING, 0);
					}
					for (int Cnt = 0; Cnt < CONNECT_MAX; Cnt++)
					{
						send(dstSocket[Cnt], toSendText, BUFFER_SIZE_STRING, 0);
					}
					for (int Cnt = 0; Cnt < CONNECT_MAX; Cnt++)
					{
						send(dstSocket[Cnt], toSendText, BUFFER_SIZE_STRING, 0);
					}

				}
				// �Ƃ肠�����҂��Ă݂�
				Sleep(10);
			}
		}
		//----------------------------�}�b�`���O�M��


		//----------------------------�l�ԍ��M���@�X�e�b�v2
		bool ChkMyNum = false;
		bool ChkMyNumRecv[CONNECT_MAX] = { false };
		int MyNumOK = 0;
		while (ChkMyNum != true)
		{
			printf("STEP2 �l�ԍ�\n");
			for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
			{
				char MyNumChkRMsg[BUFFER_SIZE]; //�����Ă���f�[�^���e
				MyNumChkRMsg[0] = NULL;
				if (ChkMyNumRecv[ConnectCnt] == true) continue;
				//�l�ԍ����}�𑗂�
				sprintf_s(toSendText, "MyNum%d", ConnectCnt);
				send(dstSocket[ConnectCnt], toSendText, BUFFER_SIZE_STRING, 0);
				numrcv = recv(dstSocket[ConnectCnt], MyNumChkRMsg, BUFFER_SIZE_STRING, 0);
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
					if (strcmp(MyNumChkRMsg, "MyNumOK") == 0)
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
				Sleep(10);
			}
		}
		//----------------------------�l�ԍ��M��


		//----------------------------�A�C�e�������@�X�e�b�v3
		bool ChkItem = false;
		bool ChkItemRecv[CONNECT_MAX] = { false };
		int ItemOK = 0;
		while (ChkItem != true)
		{
			printf("STEP3 �A�C�e������\n");
			//socket���[�v
			for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
			{
				char ItemChkRMsg[BUFFER_SIZE]; //�����Ă���f�[�^���e
				ItemChkRMsg[0] = NULL;
				if (ChkItemRecv[ConnectCnt] == true) continue;

				//�A�C�e����񃁃b�Z�[�W�𑗂�
				send(dstSocket[ConnectCnt], ItemSMsg, BUFFER_SIZE_STRING, 0);
				numrcv = recv(dstSocket[ConnectCnt], ItemChkRMsg, BUFFER_SIZE_STRING, 0);
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
					if (strcmp(ItemChkRMsg, "ItemOK") == 0)
					{
						//�l�ԍ����󂯂��Ƃ����}���Ԃ��Ă����炱���ŃJ�E���g���₷
						ChkItemRecv[ConnectCnt] = true;
						ItemOK++;
						//�݂�Ȋm�F��ꂽ�玟�̃X�e�b�v��
						if (ItemOK >= CONNECT_MAX) ChkItem = true;
					}
					char addr[80] = { NULL };
					inet_ntop(AF_INET, &dstAddr[ConnectCnt].sin_addr, addr, dstAddrSize);
					sprintf_s(addr, "%s%d", addr, ConnectCnt);
					printf("from %s\n", addr);
					printf("%s\n", ItemChkRMsg);
				}
				// �Ƃ肠�����҂��Ă݂�
				Sleep(10);
			}
		}
		//----------------------------�A�C�e������


		//----------------------------�J�E���g�_�E���X�^�[�g�M���@�X�e�b�v4
		//�J�E���g�_�E���J�n�̍��}�𑗂�
		bool ChkStart = false;
		bool ChkStartRecv[CONNECT_MAX] = { false };
		int StartOK = 0;
		while (ChkStart != true)
		{
			printf("STEP4 �J�E���g�_�E���J�n\n");
			for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
			{
				char CountChkRMsg[BUFFER_SIZE]; //�����Ă���f�[�^���e
				CountChkRMsg[0] = NULL;
				if (ChkStartRecv[ConnectCnt] == true) continue;
				//�l�ԍ����}�𑗂�
				sprintf_s(toSendText, "Start");
				send(dstSocket[ConnectCnt], toSendText, BUFFER_SIZE_STRING, 0);
				numrcv = recv(dstSocket[ConnectCnt], CountChkRMsg, BUFFER_SIZE_STRING, 0);
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
					if (strcmp(CountChkRMsg, "StartOK") == 0)
					{
						//�l�ԍ����󂯂��Ƃ����}���Ԃ��Ă����炱���ŃJ�E���g���₷
						ChkStartRecv[ConnectCnt] = true;
						StartOK++;
						//�݂�Ȋm�F��ꂽ�玟�̃X�e�b�v��
						if (StartOK >= CONNECT_MAX) ChkStart = true;
					}
					printf("�Q�[���J�n\n");
					printf("%s\n", CountChkRMsg);
				}
			}
		}
		//----------------------------�J�E���g�_�E���X�^�[�g�M��


		//----------------------------�Q�[�����M���@�X�e�b�v5
		//�Q�[�����I���܂Ń��[�v
		bool ChkGameEnd = false;
		while (ChkGameEnd != true)
		{
			//printf("STEP5 �ΐ풆\n");
			char GameRMsg[BUFFER_SIZE] = { NULL }; //�����Ă���f�[�^���e
			for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
			{
				GameRMsg[0] = NULL;//�����Ă���f�[�^���e
				//���b�Z�[�W���󂯎��
				numrcv = recv(dstSocket[ConnectCnt], GameRMsg, BUFFER_SIZE_STRING, 0);
				//numrcv = -1;
				/*
				if (numrcv < 1)
				{
					printf("[ %d ][ P%d ]\n", WSAGetLastError(), ConnectCnt);
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
				*/
				if(numrcv >0)
				{
					/* �X�y�[�X.����؂�ɕ�����𒊏o */
					if (GameRMsg[0] != NULL)
					{
						char GameRMsgBuff[BUFFER_SIZE] = { NULL };
						strcpy_s(GameRMsgBuff, GameRMsg);
						char *RMsgBlock;
						char *next = NULL;

						RMsgBlock = strtok_s(GameRMsgBuff, ",", &next);

						//�A�C�e���擾�̃f�[�^�������Ă�����A�C�e���Ǘ�������
						if (strcmp(RMsgBlock, "@I") == 0)
						{
							char *ItemMsgBlock = next;
							char *nextItemMsg = NULL;
							char *Index = strtok_s(ItemMsgBlock, "N,", &nextItemMsg);
							char *Type = strtok_s(NULL, "T,", &nextItemMsg);
							//"@I,N%d,T%d,X%4.3f,Y%4.3f,Z%4.3f&"
							RMsgBlock = strtok_s(NULL, "&", &nextItemMsg);
							//�f�[�^���i�[
							int iIndex = atoi(Index);
							int iType = atoi(Type);		//�^�C�v�͕K�v�Ȃ�
							//�Q�b�g���ꂽ�A�C�e����false�ɂ��ă��X�|�[���J�E���g�A�b�v�J�n
							if (ItemUse[iIndex] != false)
							{
								ItemUse[iIndex] = false;
								ItemCntUse--;
							}
						}
						//�I������
						else if (strcmp(GameRMsgBuff, "@EndGame") == 0)
						{
							//�ŏI���b�Z�[�W�𑗂��ăQ�[�����[�v���I��������
							for (int SendCnt = 0; SendCnt < CONNECT_MAX; SendCnt++)
							{
								send(dstSocket[SendCnt], GameRMsg, BUFFER_SIZE_STRING, 0);
							}
							ChkGameEnd = true;
						}

						//����ȊO�@player�f�[�^�ƒn�`�A�C�e���擾�̃f�[�^�������Ă����瑼�N���C�A���g�ɂ��̂܂܃f�[�^�𑗐M
						else
						{
							for (int SendCnt = 0; SendCnt < CONNECT_MAX; SendCnt++)
							{
								if (SendCnt == ConnectCnt) continue; //�����ɂ͑���Ȃ��Ă���
								send(dstSocket[SendCnt], GameRMsg, BUFFER_SIZE_STRING, 0);
							}
						}
					}

				}
			}
			//�A�C�e���̍X�V
			//�A�C�e������20��肷���Ȃ���Ύ��Ԍo�߂ŕ���������
			if (ItemCntUse < DROP_ITEM_MAX)
			{
				ItemRespownTime += 1.0f;
				//��莞�Ԍo�߂Ń��X�|�[������
				if (ItemRespownTime >= ITEM_RESPOWNTIMEMAX)
				{
					ItemRespownTime = 0.0f;

					VEC3 pos;
					pos.x = float(rand() % int(WALL_SIZE_X / 4)) + 100.0f;
					pos.z = float(rand() % int(WALL_SIZE_X / 4)) + 100.0f;
					int x = rand() % 2;
					int z = rand() % 2;
					if (x == 1) pos.x *= -1;
					if (z == 1) pos.z *= -1;

					int ItemTypeNum = rand() % ITEMTYPE_MAX;
					//���C�t�A�J�����A���A�C�e���̎��͂�����x���I
					if (ItemTypeNum == ITEMTYPE_LIFE && ItemTypeNum == ITEMTYPE_CAMERA && ItemTypeNum == ITEMTYPE_KIRI) ItemTypeNum = rand() % ITEMTYPE_MAX;
					char NewSMsg[BUFFER_SIZE] = { NULL }; //����f�[�^���e�@"@Item,%d,%d,X%d,Z%d&"

					for (int CntItem = 0; CntItem <= DROP_ITEM_MAX; CntItem++)
					{
						//���g�p�������true�ɂ��ă��X�|�[��������
						if (ItemUse[CntItem] == false)
						{
							ItemSMsg[0] = NULL;
							ItemUse[CntItem] = true;
							ItemCntUse++;
							sprintf_s(NewSMsg, "@I,N%d.T%d,X%d,Z%d&"
								, CntItem, ItemTypeNum, int(pos.x), int(pos.z));
							sprintf_s(ItemSMsg, "%s%s", ItemSMsg, NewSMsg);

							//���X�|�[�������A�C�e�������N���C�A���g�ɑ��M
							for (int SendCnt = 0; SendCnt < CONNECT_MAX; SendCnt++)
							{
								send(dstSocket[SendCnt], ItemSMsg, BUFFER_SIZE_STRING, 0);
							}
							break;
						}
					}
				}
			}
		}
		//----------------------------�Q�[�����M��


		/* Windows �Ǝ��̐ݒ� */
		WSACleanup();
	}
}






void GenerateFiled(VEC3 *PPOS,VEC3 *VTX,int IGetPlayer,DWORD *pIdx,bool *Tikei,int *IdxMsgBuff)
{
	//����@������ݒ�	
	//���b�Z�[�W��Z�����邽�ߍ�������񐔂�/2���āA�v�Z�Ȃǂ͍s�킸�ɕύX�̂��������_Indx��Y���l�����b�Z�[�W�ɓ����
	for (int nCntVtx = 0; nCntVtx < int(NUM_VERTEX_MAX)/2; nCntVtx++)
	{
		//���������߂钸�_������
		int YTXrandNum(rand() % NUM_VERTEX_MAX);
		//���������ߑ��
		int VTXrandY(rand() % 200);
		VTXrandY += 20;//�I�t�Z�b�g
		if (VTX[YTXrandNum] == VTX[YTXrandNum + 1])
		{
			VTX[YTXrandNum].y = VTX[YTXrandNum + 1].y = float(VTXrandY);
			IdxMsgBuff[nCntVtx] = YTXrandNum;
			continue;
		}
		else if (VTX[YTXrandNum + 1] == VTX[YTXrandNum + 2])
		{
			VTX[YTXrandNum + 1].y = VTX[YTXrandNum + 2].y = float(VTXrandY);
			IdxMsgBuff[nCntVtx] = YTXrandNum;
			continue;
		}
		VTX[YTXrandNum].y = float(VTXrandY);
		IdxMsgBuff[nCntVtx] = YTXrandNum;
	}

	/*
	//�t���N�^���A���S���Y��������
	for (int nCntVtxZ = 0; nCntVtxZ < (NUM_BLOCK_FIELD_MAX + 1); nCntVtxZ++)
	{
		for (int nCntVtxX = 0; nCntVtxX < (NUM_BLOCK_FIELD_MAX + 1); nCntVtxX++)
		{
			//�k�ރ|���S���悯�Ȃ���
			if (nCntVtxZ*nCntVtxX == NUM_VERTEX_INDEX_MAX - 2) break;
			else if (VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX] == VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX + 1])	continue;
			else if (VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX + 1] == VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX + 2]) continue;
			// ���_���W�̐ݒ�
			//���_�Œ[�̍����͌Œ�B�Ǎۂ̒��_�̂��ƁB
			//�㑤
			if (nCntVtxZ == 0 || nCntVtxX == 0 || nCntVtxZ == NUM_BLOCK_FIELD_MAX || nCntVtxX == NUM_BLOCK_FIELD_MAX)
				VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX].y = 200.0f;
			//�����@�㉺���E�̕��ϒl���Z�o
			//�אڒ��_�̍����̕��ϒl�����߁A���S�̒��_�̍����Ƃ���B
			else
			{
				float y = (VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX - 1].y + VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX + 1].y +
					VTX[(nCntVtxZ - 1) * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX].y + VTX[(nCntVtxZ + 1) * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX].y) / 4.0f;
				VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX].y = fabsf(y);
			}
		}
	}



	for (int CntPlayer = 0; CntPlayer < CONNECT_MAX; CntPlayer++)
	{
		if (CntPlayer != IGetPlayer)
		{
			float HitPosUp;
			float HitPosDown;
			float HitPosLeft;
			float HitPosRight;
			HitPosUp = HitPosDown = HitPosLeft = HitPosRight = 0.0f;

			//�v���C���[�̏���Ă���G���A�����B4���؂Ŕ͈͂��i��B
			//-------------------�I�u�W�F�N�g�l�ǂݍ���
			VEC3 pos = PPOS[CntPlayer];
			SpeedUpFieldHitPoly(pos, &HitPosUp, &HitPosDown, &HitPosLeft, &HitPosRight,
				SIZE_BLOCK_EIGHTH, SIZE_BLOCK_EIGHTH, SIZE_BLOCK_EIGHTH / 2, SIZE_BLOCK_EIGHTH / 2);

			for (int nCntVtx = 0; nCntVtx < int(NUM_VERTEX_INDEX_MAX); nCntVtx++)
			{
				//�k�ރ|���S���̂Ƃ��̓R���e�B�j���[�B�ŏI�|���S���̎���break;
				if (nCntVtx == NUM_VERTEX_INDEX_MAX - 2)
				{
					break;
				}
				else if (pIdx[nCntVtx] == pIdx[nCntVtx + 1])
				{
					continue;
				}
				else if (pIdx[nCntVtx + 1] == pIdx[nCntVtx + 2])
				{
					continue;
				}
				//���������蔻��p�|���S���̍��W���Ȃ瓖���蔻����s�@X�`�F�b�N����Z�`�F�b�N�B�Ƃ���true���Ɣ���
				if (VTX[pIdx[nCntVtx]].x >= HitPosLeft && VTX[pIdx[nCntVtx]].x <= HitPosRight)
				{
					if (VTX[pIdx[nCntVtx]].z <= HitPosUp && VTX[pIdx[nCntVtx]].z >= HitPosDown)
					{
						// ���_���W�̐ݒ�
						VTX[pIdx[nCntVtx]].y = 20.0f;
					}
				}
			}
		}
	}
	*/


	*Tikei = false;
}


#include <stdio.h>
#include<time.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <math.h>
#include"../h/vec3.h"
#include "../h/library.h"

#pragma comment (lib, "Ws2_32.lib")

#define BUFFER_SIZE 500					//!< 送信データバッファサイズ
#define BUFFER_SIZE_STRING 500			//!< 送信データバッファサイズ
#define CONNECT_MAX 2					//!< クライアント数


#define DROP_ITEM_MAX 20				//!< 出現させるアイテムの数
#define ITEM_RESPOWNTIMEMAX 9600000		//!< アイテムのリスポーンタイム

#define	ITEM_INIT_POSX						(700.0f)						//!< 初期座標アイテム
#define	ITEM_INIT_POSY						(500.0f)						//!< 初期座標アイテム
#define	ITEM_INIT_POSZ						(700.0f)						//!< 初期座標アイテム
#define	WALL_INIT_POSX						(2600.0f)						//!< 初期座標壁
#define	WALL_INIT_POSY						(0.0f)							//!< 初期座標壁
#define	WALL_INIT_POSZ						(2600.0f)						//!< 初期座標壁
#define	WALL_SIZE_X							(WALL_INIT_POSX*2)				//!< 壁のサイズX
#define	WALL_SIZE_Y							(800.0f)						//!< 壁のサイズY

#define	NUM_VERTEX_MAX						(1089)						//!< 床メッシュ頂点の数
#define	NUM_VERTEX_INDEX_MAX				(2172)						//!< 床メッシュインデックスの数
#define	NUM_POLYGON_MAX						(2172)						//!< 床メッシュポリゴンの数
#define	NUM_BLOCK_FIELD_MAX					(32)						//!< 床メッシュの縦横ブロック数
#define	SIZE_BLOCK_FIELD					(250.0f)					//!< 床メッシュの縦横ブロックサイズ

#define	SIZE_BLOCK_MAX						(8000)						//!< 床メッシュのサイズ
#define	SIZE_BLOCK_HALF						(4000)						//!< 床メッシュのサイズ
#define	SIZE_BLOCK_QUARTER					(2000)						//!< 床メッシュのサイズ
#define	SIZE_BLOCK_EIGHTH					(1000)						//!< 床メッシュのサイズ

#define	OBJECT_PLAYER_MAX					(4)							//!< プレイヤーの数

enum
{
	ITEMTYPE_TIKEI = 0,		// 地形
	ITEMTYPE_LIFE,			// ライフ
	ITEMTYPE_SENSYA,		// 戦車
	ITEMTYPE_BULLET,		// バレット
	ITEMTYPE_SPEEDUP,		// スピードアップ
	ITEMTYPE_CAMERA,		// お邪魔アイテム　強制バックカメラ
	ITEMTYPE_KIRI,			// お邪魔アイテム　霧
	ITEMTYPE_MAX
};

//WANプロトコルのポート6432
//ポート開放
//最大で300バイトくらい
//sleep無くていい
//再送制御か照合制御がいる
//upnpはoffでいい

//STEP1	同端末通信	OK
//STEP2	LAN通信		OK
//STEP3	WAN通信		OK

void GenerateFiled(VEC3 *PPOS, VEC3 *VTX, int IGetPlayer, DWORD *pIdx, bool *Tikei, int *IdxMsgBuff);


int main()
{
	srand((unsigned)time(NULL));

	//使用中のアイテム数
	int ItemCntUse = 0;
	bool ItemUse[DROP_ITEM_MAX];
	bool ItemScyncUse[DROP_ITEM_MAX];
	float ItemRespownTime = 0.0f;

	//プレイヤー座標 
	VEC3 PlayerPos[CONNECT_MAX];

	//地形生成に必要なデータ
	//VEC3 VTXPos[NUM_VERTEX_MAX];	//地形座標
	int TikeiItemGetPlayer = -1;	//地形アイテムを取得したプレイヤー番号
	bool TikeiChange = false;		//trueの時地形生成
	//DWORD FieldIdx[NUM_VERTEX_INDEX_MAX];	//地形頂点のインデックス
	int TikeiIdxMsgBuff[NUM_VERTEX_MAX / 2] = { -1 };	//メッセージする頂点インデックスのバッファ

	while (1)
	{
		//初期化
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

		//頂点バッファインデックスの設定
		/*
		int nCntIdx = 0;
		for (int nCntVtxZ = 0; nCntVtxZ < NUM_BLOCK_FIELD_MAX; nCntVtxZ++)
		{
			if (nCntVtxZ > 0)
			{// 縮退ポリゴンのためのダブりの設定
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
			{// 縮退ポリゴンのためのダブりの設定
				FieldIdx[nCntIdx] = nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + NUM_BLOCK_FIELD_MAX;
				nCntIdx++;
			}
		}
		*/

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
		//srcSocket = socket(AF_INET, SOCK_DGRAM, 0);

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


		char ItemSMsg[BUFFER_SIZE] = { NULL }; //アイテム情報送るデータ内容

		for (int nCntItem = 0; nCntItem < DROP_ITEM_MAX; nCntItem++)
		{
			//1ブロック21文字　21*20=420サイズ
			VEC3 pos;
			pos.x = float(rand() % int(WALL_SIZE_X / 4)) + 100.0f;
			pos.z = float(rand() % int(WALL_SIZE_X / 4)) + 100.0f;
			int x = rand() % 2;
			int z = rand() % 2;
			if (x == 1) pos.x *= -1;
			if (z == 1) pos.z *= -1;

			int ItemTypeNum = rand() % ITEMTYPE_MAX;
			//ライフ、カメラ、霧アイテムの時はもう一度抽選
			if (ItemTypeNum == ITEMTYPE_LIFE && ItemTypeNum == ITEMTYPE_CAMERA && ItemTypeNum == ITEMTYPE_KIRI) ItemTypeNum = rand() % ITEMTYPE_MAX;
			char NewSMsg[BUFFER_SIZE] = { NULL }; //送るデータ内容　"@Item,%d,%d,X%d,Z%d&"
			sprintf_s(NewSMsg, "@I,N%d.T%d,X%d,Z%d&"
				, nCntItem, ItemTypeNum, int(pos.x), int(pos.z));
			sprintf_s(ItemSMsg, "%s%s", ItemSMsg, NewSMsg);
		}
		//アイテムカウント初期化
		ItemCntUse = 20;

		//----------------------------マッチング信号　ステップ1
		bool ChkMatch = false;
		bool ChkConnect[CONNECT_MAX] = { false };
		int ConnectOK = 0;
		char toSendText[BUFFER_SIZE];
		bool acceptFlag[CONNECT_MAX] = { false };
		while (ChkMatch != true)
		{
			for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
			{
				char ConnectRMsg[BUFFER_SIZE]; //送られてくるデータ内容
				char addr[80] = { NULL };
				ConnectRMsg[0] = NULL;
				//接続が確立されていない
				if (ChkConnect[ConnectCnt] == false)
				{
					printf("STEP1 コネクト\n");
					if (acceptFlag[ConnectCnt] == false)
					{
						dstSocket[ConnectCnt] = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);

						if (dstSocket[ConnectCnt] != -1)
						{
							acceptFlag[ConnectCnt] = true;
						}
					}

					//対象のソケットからアドレスを抜き出し表示
					//dstSocket[ConnectCnt] = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
					inet_ntop(AF_INET, &dstAddr[ConnectCnt].sin_addr, addr, dstAddrSize);
					sprintf_s(addr, "%s[%d]", addr, ConnectCnt);
					printf("from %s\n", addr);
					/* パケット受信 */
					numrcv = recv(dstSocket[ConnectCnt], ConnectRMsg, BUFFER_SIZE_STRING, 0);

					//データを受け取っていない
					if (numrcv < 1)
					{
						// 非ブロッキングで動作しているので接続確認後receiveを受け取っていないときにここへ来る
						if (WSAGetLastError() == WSAEWOULDBLOCK)
						{
							printf("error : 0x%x\n", WSAGetLastError());
						}
						//ひとまずの状態を表示
						else
						{
							printf("応答なし : 0x%x\n", WSAGetLastError());
						}
					}
					//正常にreceiveしたとき
					else
					{
						ChkConnect[ConnectCnt] = true;
						printf("received data\n");
						printf("%s\n", ConnectRMsg);
						//コネクト数をカウントして4になると全員の接続が完了
						ConnectOK++;
						//マッチング待ち(人数待ち)を相手に送る
						sprintf_s(toSendText, "%d", ConnectOK);
						send(dstSocket[ConnectCnt], toSendText, BUFFER_SIZE_STRING, 0);
					}
				}
				//接続が確立されてる
				else
				{
					inet_ntop(AF_INET, &dstAddr[ConnectCnt].sin_addr, addr, dstAddrSize);
					sprintf_s(addr, "%s[%d]", addr, ConnectCnt);
					printf("接続確立　%s\n", addr);
					//マッチング待ち(人数待ち)を相手に送る
					sprintf_s(toSendText, "%d", ConnectOK);
					send(dstSocket[ConnectCnt], toSendText, BUFFER_SIZE_STRING, 0);
				}

				//人数にが揃ったら確立されたクライアントに5を送ってマッチング確定合図とする
				if (ConnectOK == CONNECT_MAX)
				{
					ChkMatch = true;
					printf("マッチング完了\n");
					sprintf_s(toSendText, "%d", 5);
					//ここで確認用信号を何回かおくらないと失敗する時がある
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
				// とりあえず待ってみる
				Sleep(10);
			}
		}
		//----------------------------マッチング信号


		//----------------------------個人番号信号　ステップ2
		bool ChkMyNum = false;
		bool ChkMyNumRecv[CONNECT_MAX] = { false };
		int MyNumOK = 0;
		while (ChkMyNum != true)
		{
			printf("STEP2 個人番号\n");
			for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
			{
				char MyNumChkRMsg[BUFFER_SIZE]; //送られてくるデータ内容
				MyNumChkRMsg[0] = NULL;
				if (ChkMyNumRecv[ConnectCnt] == true) continue;
				//個人番号合図を送る
				sprintf_s(toSendText, "MyNum%d", ConnectCnt);
				send(dstSocket[ConnectCnt], toSendText, BUFFER_SIZE_STRING, 0);
				numrcv = recv(dstSocket[ConnectCnt], MyNumChkRMsg, BUFFER_SIZE_STRING, 0);
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
					if (strcmp(MyNumChkRMsg, "MyNumOK") == 0)
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
				Sleep(10);
			}
		}
		//----------------------------個人番号信号


		//----------------------------アイテム同期　ステップ3
		bool ChkItem = false;
		bool ChkItemRecv[CONNECT_MAX] = { false };
		int ItemOK = 0;
		while (ChkItem != true)
		{
			printf("STEP3 アイテム同期\n");
			//socketループ
			for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
			{
				char ItemChkRMsg[BUFFER_SIZE]; //送られてくるデータ内容
				ItemChkRMsg[0] = NULL;
				if (ChkItemRecv[ConnectCnt] == true) continue;

				//アイテム情報メッセージを送る
				send(dstSocket[ConnectCnt], ItemSMsg, BUFFER_SIZE_STRING, 0);
				numrcv = recv(dstSocket[ConnectCnt], ItemChkRMsg, BUFFER_SIZE_STRING, 0);
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
					if (strcmp(ItemChkRMsg, "ItemOK") == 0)
					{
						//個人番号を受けっとた合図が返ってきたらここでカウント増やす
						ChkItemRecv[ConnectCnt] = true;
						ItemOK++;
						//みんな確認取れたら次のステップへ
						if (ItemOK >= CONNECT_MAX) ChkItem = true;
					}
					char addr[80] = { NULL };
					inet_ntop(AF_INET, &dstAddr[ConnectCnt].sin_addr, addr, dstAddrSize);
					sprintf_s(addr, "%s%d", addr, ConnectCnt);
					printf("from %s\n", addr);
					printf("%s\n", ItemChkRMsg);
				}
				// とりあえず待ってみる
				Sleep(10);
			}
		}
		//----------------------------アイテム生成


		//----------------------------カウントダウンスタート信号　ステップ4
		//カウントダウン開始の合図を送る
		bool ChkStart = false;
		bool ChkStartRecv[CONNECT_MAX] = { false };
		int StartOK = 0;
		while (ChkStart != true)
		{
			printf("STEP4 カウントダウン開始\n");
			for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
			{
				char CountChkRMsg[BUFFER_SIZE]; //送られてくるデータ内容
				CountChkRMsg[0] = NULL;
				if (ChkStartRecv[ConnectCnt] == true) continue;
				//個人番号合図を送る
				sprintf_s(toSendText, "Start");
				send(dstSocket[ConnectCnt], toSendText, BUFFER_SIZE_STRING, 0);
				numrcv = recv(dstSocket[ConnectCnt], CountChkRMsg, BUFFER_SIZE_STRING, 0);
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
					if (strcmp(CountChkRMsg, "StartOK") == 0)
					{
						//個人番号を受けっとた合図が返ってきたらここでカウント増やす
						ChkStartRecv[ConnectCnt] = true;
						StartOK++;
						//みんな確認取れたら次のステップへ
						if (StartOK >= CONNECT_MAX) ChkStart = true;
					}
					printf("ゲーム開始\n");
					printf("%s\n", CountChkRMsg);
				}
			}
		}
		//----------------------------カウントダウンスタート信号


		//----------------------------ゲーム中信号　ステップ5
		//ゲームが終わるまでループ
		bool ChkGameEnd = false;
		while (ChkGameEnd != true)
		{
			//printf("STEP5 対戦中\n");
			char GameRMsg[BUFFER_SIZE] = { NULL }; //送られてくるデータ内容
			for (int ConnectCnt = 0; ConnectCnt < CONNECT_MAX; ConnectCnt++)
			{
				GameRMsg[0] = NULL;//送られてくるデータ内容
				//メッセージを受け取る
				numrcv = recv(dstSocket[ConnectCnt], GameRMsg, BUFFER_SIZE_STRING, 0);
				//numrcv = -1;
				/*
				if (numrcv < 1)
				{
					printf("[ %d ][ P%d ]\n", WSAGetLastError(), ConnectCnt);
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
				*/
				if(numrcv >0)
				{
					/* スペース.を区切りに文字列を抽出 */
					if (GameRMsg[0] != NULL)
					{
						char GameRMsgBuff[BUFFER_SIZE] = { NULL };
						strcpy_s(GameRMsgBuff, GameRMsg);
						char *RMsgBlock;
						char *next = NULL;

						RMsgBlock = strtok_s(GameRMsgBuff, ",", &next);

						//アイテム取得のデータが送られてきたらアイテム管理をする
						if (strcmp(RMsgBlock, "@I") == 0)
						{
							char *ItemMsgBlock = next;
							char *nextItemMsg = NULL;
							char *Index = strtok_s(ItemMsgBlock, "N,", &nextItemMsg);
							char *Type = strtok_s(NULL, "T,", &nextItemMsg);
							//"@I,N%d,T%d,X%4.3f,Y%4.3f,Z%4.3f&"
							RMsgBlock = strtok_s(NULL, "&", &nextItemMsg);
							//データを格納
							int iIndex = atoi(Index);
							int iType = atoi(Type);		//タイプは必要なし
							//ゲットされたアイテムをfalseにしてリスポーンカウントアップ開始
							if (ItemUse[iIndex] != false)
							{
								ItemUse[iIndex] = false;
								ItemCntUse--;
							}
						}
						//終了判定
						else if (strcmp(GameRMsgBuff, "@EndGame") == 0)
						{
							//最終メッセージを送ってゲームループを終了させる
							for (int SendCnt = 0; SendCnt < CONNECT_MAX; SendCnt++)
							{
								send(dstSocket[SendCnt], GameRMsg, BUFFER_SIZE_STRING, 0);
							}
							ChkGameEnd = true;
						}

						//それ以外　playerデータと地形アイテム取得のデータが送られてきたら他クライアントにそのままデータを送信
						else
						{
							for (int SendCnt = 0; SendCnt < CONNECT_MAX; SendCnt++)
							{
								if (SendCnt == ConnectCnt) continue; //自分には送らなくていい
								send(dstSocket[SendCnt], GameRMsg, BUFFER_SIZE_STRING, 0);
							}
						}
					}

				}
			}
			//アイテムの更新
			//アイテム数が20よりすくなければ時間経過で復活させる
			if (ItemCntUse < DROP_ITEM_MAX)
			{
				ItemRespownTime += 1.0f;
				//一定時間経過でリスポーンする
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
					//ライフ、カメラ、霧アイテムの時はもう一度抽選
					if (ItemTypeNum == ITEMTYPE_LIFE && ItemTypeNum == ITEMTYPE_CAMERA && ItemTypeNum == ITEMTYPE_KIRI) ItemTypeNum = rand() % ITEMTYPE_MAX;
					char NewSMsg[BUFFER_SIZE] = { NULL }; //送るデータ内容　"@Item,%d,%d,X%d,Z%d&"

					for (int CntItem = 0; CntItem <= DROP_ITEM_MAX; CntItem++)
					{
						//未使用があればtrueにしてリスポーンさせる
						if (ItemUse[CntItem] == false)
						{
							ItemSMsg[0] = NULL;
							ItemUse[CntItem] = true;
							ItemCntUse++;
							sprintf_s(NewSMsg, "@I,N%d.T%d,X%d,Z%d&"
								, CntItem, ItemTypeNum, int(pos.x), int(pos.z));
							sprintf_s(ItemSMsg, "%s%s", ItemSMsg, NewSMsg);

							//リスポーンしたアイテム情報をクライアントに送信
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
		//----------------------------ゲーム中信号


		/* Windows 独自の設定 */
		WSACleanup();
	}
}






void GenerateFiled(VEC3 *PPOS,VEC3 *VTX,int IGetPlayer,DWORD *pIdx,bool *Tikei,int *IdxMsgBuff)
{
	//上限　高さを設定	
	//メッセージを短くするため高さ決定回数を/2して、計算などは行わずに変更のあった頂点IndxとY数値をメッセージに入れる
	for (int nCntVtx = 0; nCntVtx < int(NUM_VERTEX_MAX)/2; nCntVtx++)
	{
		//高さを決める頂点を決定
		int YTXrandNum(rand() % NUM_VERTEX_MAX);
		//高さを決め代入
		int VTXrandY(rand() % 200);
		VTXrandY += 20;//オフセット
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
	//フラクタルアルゴリズム改造版
	for (int nCntVtxZ = 0; nCntVtxZ < (NUM_BLOCK_FIELD_MAX + 1); nCntVtxZ++)
	{
		for (int nCntVtxX = 0; nCntVtxX < (NUM_BLOCK_FIELD_MAX + 1); nCntVtxX++)
		{
			//縮退ポリゴンよけなさい
			if (nCntVtxZ*nCntVtxX == NUM_VERTEX_INDEX_MAX - 2) break;
			else if (VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX] == VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX + 1])	continue;
			else if (VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX + 1] == VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX + 2]) continue;
			// 頂点座標の設定
			//頂点最端の高さは固定。壁際の頂点のこと。
			//上側
			if (nCntVtxZ == 0 || nCntVtxX == 0 || nCntVtxZ == NUM_BLOCK_FIELD_MAX || nCntVtxX == NUM_BLOCK_FIELD_MAX)
				VTX[nCntVtxZ * (NUM_BLOCK_FIELD_MAX + 1) + nCntVtxX].y = 200.0f;
			//中側　上下左右の平均値を算出
			//隣接頂点の高さの平均値を求め、中心の頂点の高さとする。
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

			//プレイヤーの乗っているエリアを特定。4分木で範囲を絞る。
			//-------------------オブジェクト値読み込み
			VEC3 pos = PPOS[CntPlayer];
			SpeedUpFieldHitPoly(pos, &HitPosUp, &HitPosDown, &HitPosLeft, &HitPosRight,
				SIZE_BLOCK_EIGHTH, SIZE_BLOCK_EIGHTH, SIZE_BLOCK_EIGHTH / 2, SIZE_BLOCK_EIGHTH / 2);

			for (int nCntVtx = 0; nCntVtx < int(NUM_VERTEX_INDEX_MAX); nCntVtx++)
			{
				//縮退ポリゴンのときはコンティニュー。最終ポリゴンの時はbreak;
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
				//高速当たり判定用ポリゴンの座標内なら当たり判定実行　XチェックからZチェック。ともにtrueだと判定
				if (VTX[pIdx[nCntVtx]].x >= HitPosLeft && VTX[pIdx[nCntVtx]].x <= HitPosRight)
				{
					if (VTX[pIdx[nCntVtx]].z <= HitPosUp && VTX[pIdx[nCntVtx]].z >= HitPosDown)
					{
						// 頂点座標の設定
						VTX[pIdx[nCntVtx]].y = 20.0f;
					}
				}
			}
		}
	}
	*/


	*Tikei = false;
}



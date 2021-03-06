#pragma once

/**
* @struct VEC3
* @details 3Dベクトル構造体
*/
struct VEC3
{
	float x;
	float y;
	float z;

	//比較演算子オーバーロード
	inline bool operator==(const VEC3& pMy)
	{
		if (x == pMy.x && y == pMy.y && z == pMy.z)
		{
			return true;
		}
		return false;
	}
};

/**
* @brief VEC3Create
* @param[in] float x,float y,float z,
* @return VEC3
* @details x,y,zからVEC3を作成しコピーを返す
*/
VEC3 VEC3Create(float x, float y, float z);

/**
* @brief VEC3Copy
* @param[in] VEC3 VecIn
* @param[in] VEC3 VecOut
* @return void
* @details VecInをVecOutへコピー
*/
void VEC3Copy(VEC3 *VecIn, VEC3 *VecOut);

/**
* @brief VEC3Add
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1とv2を加算してvOutへ格納する
*/
void VEC3Add(VEC3* v1, VEC3* v2, VEC3* vOut);

/**
* @brief VEC3Sub
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1からv2を減算してvOutへ格納する
*/
void VEC3Sub(VEC3* v1, VEC3* v2, VEC3* vOut);

/**
* @brief VEC3Scale
* @param[in] VEC3* v1,float t
* @param[out] VEC3* vOut
* @return void
* @details v1にtを積算してvOutへ格納する
*/
void VEC3Scale(VEC3* v1, float t, VEC3* vOut);

/**
* @brief VEC3Len
* @param[in] VEC3* v1
* @return float
* @details v1のベクトル長を返す
*/
float VEC3Len(VEC3* v1);

/**
* @brief VEC3LenSq
* @param[in] VEC3* v1
* @return float
* @details v1のベクトル長を返す(ルート計算無し)
*/
float VEC3LenSq(VEC3* v1);

/**
* @brief VEC3Norm
* @param[in] VEC3* v1
* @param[out] VEC3* vOut
* @return void
* @details v1を正規化してvOutへ格納する
*/
void VEC3Norm(VEC3* v1, VEC3* vOut);

/**
* @brief VEC3Dot
* @param[in] VEC3* v1,VEC3* v2
* @return float
* @details v1とv2の内積を返す
*/
float VEC3Dot(VEC3* v1, VEC3* v2);

/**
* @brief VEC3Cross
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1とv2の外積を求めvOutへ格納する
*/
void VEC3Cross(VEC3* v1, VEC3* v2, VEC3* vOut);

/**
* @brief VEC3RotX
* @param[in] VEC3* v1,float fRadX
* @param[out] VEC3* vOut
* @return void
* @details v1のfRadX回転を求めvOutへ格納する
*/
void VEC3RotX(VEC3* v1, float fRadX, VEC3* vOut);

/**
* @brief VEC3RotY
* @param[in] VEC3* v1,float fRadY
* @param[out] VEC3* vOut
* @return void
* @details v1のfRadY回転を求めvOutへ格納する
*/
void VEC3RotY(VEC3* v1, float fRadY, VEC3* vOut);

/**
* @brief VEC3RotZ
* @param[in] VEC3* v1,float fRadZ
* @param[out] VEC3* vOut
* @return void
* @details v1のfRadZ回転を求めvOutへ格納する
*/
void VEC3RotZ(VEC3* v1, float fRadZ, VEC3* vOut);

/**
* @brief VEC3RotXY
* @param[in] VEC3* v1,float fRadX,float fRadY
* @param[out] VEC3* vOut
* @return void
* @details v1のfRadX回転fRadY回転を求めvOutへ格納する
*/
void VEC3RotXY(VEC3* v1, float fRadX, float fRadY, VEC3* vOut);

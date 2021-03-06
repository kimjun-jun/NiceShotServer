#include "../h/vec3.h"
#include <math.h>

/**
* @brief VEC3Create
* @param[in] float x,float y,float z,
* @return VEC3
* @details x,y,zからVEC3を作成しコピーを返す
*/
VEC3 VEC3Create(float x, float y, float z)
{
	VEC3 vec;
	vec = { x,y,z };
	return vec;
}
/**
* @brief VEC3Copy
* @param[in] VEC3 VecIn 
* @param[in] VEC3 VecOut
* @return void
* @details VecInをVecOutへコピー
*/
void VEC3Copy(VEC3 *VecIn,VEC3 *VecOut)
{
	*VecOut = *VecIn;
}

/**
* @brief VEC3Add
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1とv2を加算してvOutへ格納する
*/
void VEC3Add(VEC3* v1, VEC3* v2, VEC3* vOut)
{
	vOut->x = v1->x + v2->x;
	vOut->y = v1->y + v2->y;
	vOut->z = v1->z + v2->z;
}

/**
* @brief VEC3Sub
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1からv2を減算してvOutへ格納する
*/
void VEC3Sub(VEC3* v1, VEC3* v2, VEC3* vOut)
{
	vOut->x = v1->x - v2->x;
	vOut->y = v1->y - v2->y;
	vOut->z = v1->z - v2->z;
}

/**
* @brief VEC3Scale
* @param[in] VEC3* v1,float t
* @param[out] VEC3* vOut
* @return void
* @details v1にtを積算してvOutへ格納する
*/
void VEC3Scale(VEC3* v1,  float t,VEC3* vOut)
{
	vOut->x = v1->x *t;
	vOut->y = v1->y *t;
	vOut->z = v1->z *t;
}

/**
* @brief VEC3Len
* @param[in] VEC3* v1
* @return float
* @details v1のベクトル長を返す
*/
float VEC3Len(VEC3* v1)
{
	//! Len 長さを格納 returnで返す
	float len =
		sqrtf((v1->x*v1->x) + (v1->y*v1->y) + (v1->z*v1->z));
	return len;
}

/**
* @brief VEC3LenSq
* @param[in] VEC3* v1
* @return float
* @details v1のベクトル長を返す(ルート計算無し)
*/
float VEC3LenSq(VEC3* v1)
{
	//! Len 長さを格納
	float len =
		(v1->x*v1->x) + (v1->y*v1->y) + (v1->z*v1->z);
	return len;
}

/**
* @brief VEC3Norm
* @param[in] VEC3* v1
* @param[out] VEC3* vOut
* @return void
* @details v1を正規化してvOutへ格納する
*/
void VEC3Norm(VEC3* v1, VEC3* vOut)
{
	//! Len 長さを格納
	float len = VEC3Len(v1);
	if (len == 0.0f)
	{
		vOut->x = 0.0f;
		vOut->y = 0.0f;
		vOut->z = 0.0f;
		return;
	}
	vOut->x = v1->x / len;
	vOut->y = v1->y / len;
	vOut->z = v1->z / len;
}

/**
* @brief VEC3Dot
* @param[in] VEC3* v1,VEC3* v2
* @return float
* @details v1とv2の内積を返す
*/
float VEC3Dot(VEC3* v1, VEC3* v2)
{
	//! Dot 内積値を格納
	float Dot = 
		(v1->x *v2->x) + (v1->y *v2->y) + (v1->z *v2->z);
		return Dot;
}

/**
* @brief VEC3Cross
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1とv2の外積を求めvOutへ格納する
*/
void VEC3Cross(VEC3* v1, VEC3* v2, VEC3* vOut)
{
	vOut->x = v1->y*v2->z - v1->z*v2->y;
	vOut->y = v1->z*v2->x - v1->x*v2->z;
	vOut->z = v1->x*v2->y - v1->y*v2->x;
}

/**
* @brief VEC3RotX
* @param[in] VEC3* v1,float fRadX
* @param[out] VEC3* vOut
* @return void
* @details v1のfRadX回転を求めvOutへ格納する
*/
void VEC3RotX(VEC3* v1, float fRadX, VEC3* vOut)
{
	vOut->x = v1->x;
	vOut->y = (v1->y*cosf(fRadX)) - (v1->z*sinf(fRadX));
	vOut->z = (v1->y*sinf(fRadX)) + (v1->z*cosf(fRadX));
}

/**
* @brief VEC3RotY
* @param[in] VEC3* v1,float fRadY
* @param[out] VEC3* vOut
* @return void
* @details v1のfRadY回転を求めvOutへ格納する
*/
void VEC3RotY(VEC3* v1, float fRadY, VEC3* vOut)
{
	vOut->x = (v1->x*cosf(fRadY)) + (v1->z*sinf(fRadY));
	vOut->y = v1->y;
	vOut->z = (-v1->x*sinf(fRadY)) + (v1->z*cosf(fRadY));
}

/**
* @brief VEC3RotZ
* @param[in] VEC3* v1,float fRadZ
* @param[out] VEC3* vOut
* @return void
* @details v1のfRadZ回転を求めvOutへ格納する
*/
void VEC3RotZ(VEC3* v1, float fRadZ, VEC3* vOut)
{
	vOut->x = (v1->x*cosf(fRadZ)) - (v1->y*sinf(fRadZ));
	vOut->y = (v1->x*sinf(fRadZ)) + (v1->y*cosf(fRadZ));
	vOut->z = v1->z;
}

/**
* @brief VEC3RotXY
* @param[in] VEC3* v1,float fRadX,float fRadY
* @param[out] VEC3* vOut
* @return void
* @details v1のfRadX回転fRadY回転を求めvOutへ格納する
*/
void VEC3RotXY(VEC3* v1, float fRadX, float fRadY, VEC3* vOut)
{
	vOut->x = v1->x*cosf(fRadY) + v1->z*sinf(fRadY);
	vOut->y = v1->x*( -sinf(fRadX))* (-sinf(fRadY)) + v1->y*cosf(fRadX) + v1->z* (-sinf(fRadX)) * cosf(fRadY);
	vOut->z = v1->x*cosf(fRadX) * (-sinf(fRadY)) + v1->y*sinf(fRadX) + v1->z*cosf(fRadX) *cosf(fRadY);

}

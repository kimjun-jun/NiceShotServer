#pragma once

/**
* @struct VEC3
* @details 3DƒxƒNƒgƒ‹\‘¢‘Ì
*/
struct VEC3
{
	float x;
	float y;
	float z;

	//”äŠr‰‰ZqƒI[ƒo[ƒ[ƒh
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
* @details x,y,z‚©‚çVEC3‚ğì¬‚µƒRƒs[‚ğ•Ô‚·
*/
VEC3 VEC3Create(float x, float y, float z);

/**
* @brief VEC3Copy
* @param[in] VEC3 VecIn
* @param[in] VEC3 VecOut
* @return void
* @details VecIn‚ğVecOut‚ÖƒRƒs[
*/
void VEC3Copy(VEC3 *VecIn, VEC3 *VecOut);

/**
* @brief VEC3Add
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1‚Æv2‚ğ‰ÁZ‚µ‚ÄvOut‚ÖŠi”[‚·‚é
*/
void VEC3Add(VEC3* v1, VEC3* v2, VEC3* vOut);

/**
* @brief VEC3Sub
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1‚©‚çv2‚ğŒ¸Z‚µ‚ÄvOut‚ÖŠi”[‚·‚é
*/
void VEC3Sub(VEC3* v1, VEC3* v2, VEC3* vOut);

/**
* @brief VEC3Scale
* @param[in] VEC3* v1,float t
* @param[out] VEC3* vOut
* @return void
* @details v1‚Ét‚ğÏZ‚µ‚ÄvOut‚ÖŠi”[‚·‚é
*/
void VEC3Scale(VEC3* v1, float t, VEC3* vOut);

/**
* @brief VEC3Len
* @param[in] VEC3* v1
* @return float
* @details v1‚ÌƒxƒNƒgƒ‹’·‚ğ•Ô‚·
*/
float VEC3Len(VEC3* v1);

/**
* @brief VEC3LenSq
* @param[in] VEC3* v1
* @return float
* @details v1‚ÌƒxƒNƒgƒ‹’·‚ğ•Ô‚·(ƒ‹[ƒgŒvZ–³‚µ)
*/
float VEC3LenSq(VEC3* v1);

/**
* @brief VEC3Norm
* @param[in] VEC3* v1
* @param[out] VEC3* vOut
* @return void
* @details v1‚ğ³‹K‰»‚µ‚ÄvOut‚ÖŠi”[‚·‚é
*/
void VEC3Norm(VEC3* v1, VEC3* vOut);

/**
* @brief VEC3Dot
* @param[in] VEC3* v1,VEC3* v2
* @return float
* @details v1‚Æv2‚Ì“àÏ‚ğ•Ô‚·
*/
float VEC3Dot(VEC3* v1, VEC3* v2);

/**
* @brief VEC3Cross
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1‚Æv2‚ÌŠOÏ‚ğ‹‚ßvOut‚ÖŠi”[‚·‚é
*/
void VEC3Cross(VEC3* v1, VEC3* v2, VEC3* vOut);

/**
* @brief VEC3RotX
* @param[in] VEC3* v1,float fRadX
* @param[out] VEC3* vOut
* @return void
* @details v1‚ÌfRadX‰ñ“]‚ğ‹‚ßvOut‚ÖŠi”[‚·‚é
*/
void VEC3RotX(VEC3* v1, float fRadX, VEC3* vOut);

/**
* @brief VEC3RotY
* @param[in] VEC3* v1,float fRadY
* @param[out] VEC3* vOut
* @return void
* @details v1‚ÌfRadY‰ñ“]‚ğ‹‚ßvOut‚ÖŠi”[‚·‚é
*/
void VEC3RotY(VEC3* v1, float fRadY, VEC3* vOut);

/**
* @brief VEC3RotZ
* @param[in] VEC3* v1,float fRadZ
* @param[out] VEC3* vOut
* @return void
* @details v1‚ÌfRadZ‰ñ“]‚ğ‹‚ßvOut‚ÖŠi”[‚·‚é
*/
void VEC3RotZ(VEC3* v1, float fRadZ, VEC3* vOut);

/**
* @brief VEC3RotXY
* @param[in] VEC3* v1,float fRadX,float fRadY
* @param[out] VEC3* vOut
* @return void
* @details v1‚ÌfRadX‰ñ“]fRadY‰ñ“]‚ğ‹‚ßvOut‚ÖŠi”[‚·‚é
*/
void VEC3RotXY(VEC3* v1, float fRadX, float fRadY, VEC3* vOut);

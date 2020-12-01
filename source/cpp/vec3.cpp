#include "../h/vec3.h"
#include <math.h>

/**
* @brief VEC3Create
* @param[in] float x,float y,float z,
* @return VEC3
* @details x,y,z����VEC3���쐬���R�s�[��Ԃ�
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
* @details VecIn��VecOut�փR�s�[
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
* @details v1��v2�����Z����vOut�֊i�[����
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
* @details v1����v2�����Z����vOut�֊i�[����
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
* @details v1��t��ώZ����vOut�֊i�[����
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
* @details v1�̃x�N�g������Ԃ�
*/
float VEC3Len(VEC3* v1)
{
	//! Len �������i�[ return�ŕԂ�
	float len =
		sqrtf((v1->x*v1->x) + (v1->y*v1->y) + (v1->z*v1->z));
	return len;
}

/**
* @brief VEC3LenSq
* @param[in] VEC3* v1
* @return float
* @details v1�̃x�N�g������Ԃ�(���[�g�v�Z����)
*/
float VEC3LenSq(VEC3* v1)
{
	//! Len �������i�[
	float len =
		(v1->x*v1->x) + (v1->y*v1->y) + (v1->z*v1->z);
	return len;
}

/**
* @brief VEC3Norm
* @param[in] VEC3* v1
* @param[out] VEC3* vOut
* @return void
* @details v1�𐳋K������vOut�֊i�[����
*/
void VEC3Norm(VEC3* v1, VEC3* vOut)
{
	//! Len �������i�[
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
* @details v1��v2�̓��ς�Ԃ�
*/
float VEC3Dot(VEC3* v1, VEC3* v2)
{
	//! Dot ���ϒl���i�[
	float Dot = 
		(v1->x *v2->x) + (v1->y *v2->y) + (v1->z *v2->z);
		return Dot;
}

/**
* @brief VEC3Cross
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1��v2�̊O�ς�����vOut�֊i�[����
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
* @details v1��fRadX��]������vOut�֊i�[����
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
* @details v1��fRadY��]������vOut�֊i�[����
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
* @details v1��fRadZ��]������vOut�֊i�[����
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
* @details v1��fRadX��]fRadY��]������vOut�֊i�[����
*/
void VEC3RotXY(VEC3* v1, float fRadX, float fRadY, VEC3* vOut)
{
	vOut->x = v1->x*cosf(fRadY) + v1->z*sinf(fRadY);
	vOut->y = v1->x*( -sinf(fRadX))* (-sinf(fRadY)) + v1->y*cosf(fRadX) + v1->z* (-sinf(fRadX)) * cosf(fRadY);
	vOut->z = v1->x*cosf(fRadX) * (-sinf(fRadY)) + v1->y*sinf(fRadX) + v1->z*cosf(fRadX) *cosf(fRadY);

}

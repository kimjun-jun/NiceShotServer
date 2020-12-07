#pragma once

/**
* @struct VEC3
* @details 3D�x�N�g���\����
*/
struct VEC3
{
	float x;
	float y;
	float z;

	//��r���Z�q�I�[�o�[���[�h
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
* @details x,y,z����VEC3���쐬���R�s�[��Ԃ�
*/
VEC3 VEC3Create(float x, float y, float z);

/**
* @brief VEC3Copy
* @param[in] VEC3 VecIn
* @param[in] VEC3 VecOut
* @return void
* @details VecIn��VecOut�փR�s�[
*/
void VEC3Copy(VEC3 *VecIn, VEC3 *VecOut);

/**
* @brief VEC3Add
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1��v2�����Z����vOut�֊i�[����
*/
void VEC3Add(VEC3* v1, VEC3* v2, VEC3* vOut);

/**
* @brief VEC3Sub
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1����v2�����Z����vOut�֊i�[����
*/
void VEC3Sub(VEC3* v1, VEC3* v2, VEC3* vOut);

/**
* @brief VEC3Scale
* @param[in] VEC3* v1,float t
* @param[out] VEC3* vOut
* @return void
* @details v1��t��ώZ����vOut�֊i�[����
*/
void VEC3Scale(VEC3* v1, float t, VEC3* vOut);

/**
* @brief VEC3Len
* @param[in] VEC3* v1
* @return float
* @details v1�̃x�N�g������Ԃ�
*/
float VEC3Len(VEC3* v1);

/**
* @brief VEC3LenSq
* @param[in] VEC3* v1
* @return float
* @details v1�̃x�N�g������Ԃ�(���[�g�v�Z����)
*/
float VEC3LenSq(VEC3* v1);

/**
* @brief VEC3Norm
* @param[in] VEC3* v1
* @param[out] VEC3* vOut
* @return void
* @details v1�𐳋K������vOut�֊i�[����
*/
void VEC3Norm(VEC3* v1, VEC3* vOut);

/**
* @brief VEC3Dot
* @param[in] VEC3* v1,VEC3* v2
* @return float
* @details v1��v2�̓��ς�Ԃ�
*/
float VEC3Dot(VEC3* v1, VEC3* v2);

/**
* @brief VEC3Cross
* @param[in] VEC3* v1,VEC3* v2
* @param[out] VEC3* vOut
* @return void
* @details v1��v2�̊O�ς�����vOut�֊i�[����
*/
void VEC3Cross(VEC3* v1, VEC3* v2, VEC3* vOut);

/**
* @brief VEC3RotX
* @param[in] VEC3* v1,float fRadX
* @param[out] VEC3* vOut
* @return void
* @details v1��fRadX��]������vOut�֊i�[����
*/
void VEC3RotX(VEC3* v1, float fRadX, VEC3* vOut);

/**
* @brief VEC3RotY
* @param[in] VEC3* v1,float fRadY
* @param[out] VEC3* vOut
* @return void
* @details v1��fRadY��]������vOut�֊i�[����
*/
void VEC3RotY(VEC3* v1, float fRadY, VEC3* vOut);

/**
* @brief VEC3RotZ
* @param[in] VEC3* v1,float fRadZ
* @param[out] VEC3* vOut
* @return void
* @details v1��fRadZ��]������vOut�֊i�[����
*/
void VEC3RotZ(VEC3* v1, float fRadZ, VEC3* vOut);

/**
* @brief VEC3RotXY
* @param[in] VEC3* v1,float fRadX,float fRadY
* @param[out] VEC3* vOut
* @return void
* @details v1��fRadX��]fRadY��]������vOut�֊i�[����
*/
void VEC3RotXY(VEC3* v1, float fRadX, float fRadY, VEC3* vOut);

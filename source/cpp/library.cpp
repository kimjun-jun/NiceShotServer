/**
* @file library.cpp
* @brief ���C�u�����֐��Q
* @author �L�����W����
*/
#include"../h/vec3.h"
#include "../h/library.h"

//=============================================================================
// �����蔻�荂��������֐�
//=============================================================================
void SpeedUpFieldHitPoly(VEC3 InrayS, float *HitPosUp, float *HitPosDown, float *HitPosLeft, float *HitPosRight
	, float fSideSizeXQuarter, float fSideSizeZQuarter, float fSideSizeXEighth, float fSideSizeZEighth)
{

	//����@X,Z���v���X���}�C�i�X���@���g_posField�̒��S(x0,z0)�@if()����3�����ǒ���
	if (InrayS.x >= 0.0f && InrayS.z >= 0.0f)			//�e++���ی�
	{
		//�q����@�e�̎��Ɠ������A���ی��̂Ȃ��ł���Ƀv���X���}�C�i�X������
		if (InrayS.x >= fSideSizeXQuarter && InrayS.z >= fSideSizeZQuarter)			//�q++���ی�
		{
			//������@����
			if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//��++���ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//��-+���ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//��--��O�ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//��+-��l�ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < fSideSizeXQuarter && InrayS.z >= fSideSizeZQuarter)			//�q-+���ی�
		{
			//������@����
			if (InrayS.x >= fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//��++���ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//��-+���ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//��--��O�ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//��+-��l�ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < fSideSizeXQuarter && InrayS.z < fSideSizeZQuarter)			//�q--��O�ی�
		{
			//������@����
			if (InrayS.x >= fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//��++���ی�
			{
				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//��-+���ی�
			{
				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//��--��O�ی�
			{
				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//��+-��l�ی�
			{
				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}

		}
		else if (InrayS.x >= fSideSizeXQuarter && InrayS.z < fSideSizeZQuarter)			//�q+-��l�ی�
		{
			//������@����
			if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//��++���ی�
			{
				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//��-+���ی�
			{
				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//��--��O�ی�
			{
				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//��+-��l�ی�
			{
				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
		}
	}
	else if (InrayS.x < 0.0f && InrayS.z >= 0.0f)			//�e-+���ی�
	{
		//�q����@�e�̎��Ɠ������A���ی��̂Ȃ��ł���Ƀv���X���}�C�i�X������
		if (InrayS.x >= -fSideSizeXQuarter && InrayS.z >= fSideSizeZQuarter)			//�q++���ی�
		{

			//������@����
			if (InrayS.x >= -fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//��++���ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//��-+���ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//��--��O�ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//��+-��l�ی�
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
		}
		else if (InrayS.x < -fSideSizeXQuarter && InrayS.z >= fSideSizeZQuarter)			//�q-+���ی�
		{
			//������@����
			if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//��++���ی�
			{

				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//��-+���ی�
			{

				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//��--��O�ی�
			{

				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//��+-��l�ی�
			{

				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < -fSideSizeXQuarter && InrayS.z < fSideSizeZQuarter)			//�q--��O�ی�
		{
			//������@����
			if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//��++���ی�
			{

				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//��-+���ی�
			{

				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//��--��O�ی�
			{

				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//��+-��l�ی�
			{

				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}

		}
		else if (InrayS.x >= -fSideSizeXQuarter && InrayS.z < fSideSizeZQuarter)			//�q+-��l�ی�
		{
			//������@����
			if (InrayS.x >= -fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//��++���ی�
			{

				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//��-+���ی�
			{

				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//��--��O�ی�
			{

				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//��+-��l�ی�
			{

				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
		}
	}
	else if (InrayS.x < 0.0f && InrayS.z < 0.0f)			//�e--��O�ی�
	{
		if (InrayS.x >= -fSideSizeXQuarter && InrayS.z >= -fSideSizeZQuarter)			//�q++���ی�
		{
			//������@����
			if (InrayS.x >= -fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//��++���ی�
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//��-+���ی�
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//��--��O�ی�
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//��+-��l�ی�
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
		}
		else if (InrayS.x < -fSideSizeXQuarter && InrayS.z >= -fSideSizeZQuarter)			//�q-+���ی�
		{
			//������@����
			if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//��++���ی�
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//��-+���ی�
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//��--��O�ی�
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//��+-��l�ی�
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < -fSideSizeXQuarter && InrayS.z < -fSideSizeZQuarter)			//�q--��O�ی�
		{
			//������@����
			if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//��++���ی�
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//��-+���ی�
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//��--��O�ی�
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//��+-��l�ی�
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}

		}
		else if (InrayS.x >= -fSideSizeXQuarter && InrayS.z < -fSideSizeZQuarter)			//�q+-��l�ی�
		{
			//������@����
			if (InrayS.x >= -fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//��++���ی�
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//��-+���ی�
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//��--��O�ی�
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//��+-��l�ی�
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
		}
	}
	else if (InrayS.x >= 0.0f && InrayS.z < 0.0f)			//�e+-��l�ی�
	{
		if (InrayS.x >= fSideSizeXQuarter && InrayS.z >= -fSideSizeZQuarter)			//�q++���ی�
		{
			//������@����
			if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//��++���ی�
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//��-+���ی�
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//��--��O�ی�
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//��+-��l�ی�
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < fSideSizeXQuarter && InrayS.z >= -fSideSizeZQuarter)			//�q-+���ی�
		{
			//������@����
			if (InrayS.x >= fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//��++���ی�
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//��-+���ی�
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//��--��O�ی�
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//��+-��l�ی�
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < fSideSizeXQuarter && InrayS.z < -fSideSizeZQuarter)			//�q--��O�ی�
		{
			//������@����
			if (InrayS.x >= fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//��++���ی�
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//��-+���ی�
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//��--��O�ی�
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//��+-��l�ی�
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}

		}
		else if (InrayS.x >= fSideSizeXQuarter && InrayS.z < -fSideSizeZQuarter)			//�q+-��l�ی�
		{
			//������@����
			if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//��++���ی�
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//��-+���ی�
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//��--��O�ی�
			{
				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//��+-��l�ی�
			{
				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
		}
	}

}


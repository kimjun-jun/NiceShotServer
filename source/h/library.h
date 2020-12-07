/**
* @file library.h
* @brief ���C�u�����֐��Q
* @author �L�����W����
*/
#pragma once


/**
* @brief �����蔻�荂��������֐�	SpeedUpFieldHitPoly
* @param[in] D3DXVECTOR3	InPos					���肷����͍��W
* @param[in] float			*HitPosUp				�����Ă���G���A�̍ő�Z���W
* @param[in] float			*HitPosDown				�����Ă���G���A�̍ŏ�Z���W
* @param[in] float			*HitPosLeft				�����Ă���G���A�̍ő�X���W
* @param[in] float			*HitPosRight			�����Ă���G���A�̍ŏ�X���W
* @param[in] float			fSideSizeXQuarter		�t�B�[���h��X1/4�T�C�Y
* @param[in] float			fSideSizeZQuarter		�t�B�[���h��Z1/4�T�C�Y
* @param[in] float			fSideSizeXEighth		�t�B�[���h��X1/8�T�C�Y
* @param[in] float			fSideSizeZEighth		�t�B�[���h��Z1/8�T�C�Y
* @details �����Ă���HitPos��XZ�ő�ŏ����|�C���^�[�Ƃ��ĕԂ��B���̃G���A����InPos������Ƃ���
* @author : �ؑ���(�L�����W����)
*/
void SpeedUpFieldHitPoly(VEC3 InPos, float *HitPosUp, float *HitPosDown, float *HitPosLeft, float *HitPosRight
	,float fSideSizeXQuarter, float fSideSizeZQuarter, float fSideSizeXEighth, float fSideSizeZEighth);


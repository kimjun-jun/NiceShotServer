/**
* @file library.h
* @brief ライブラリ関数群
* @author キムラジュン
*/
#pragma once


/**
* @brief 当たり判定高速化判定関数	SpeedUpFieldHitPoly
* @param[in] D3DXVECTOR3	InPos					判定する入力座標
* @param[in] float			*HitPosUp				属しているエリアの最大Z座標
* @param[in] float			*HitPosDown				属しているエリアの最小Z座標
* @param[in] float			*HitPosLeft				属しているエリアの最大X座標
* @param[in] float			*HitPosRight			属しているエリアの最小X座標
* @param[in] float			fSideSizeXQuarter		フィールドのX1/4サイズ
* @param[in] float			fSideSizeZQuarter		フィールドのZ1/4サイズ
* @param[in] float			fSideSizeXEighth		フィールドのX1/8サイズ
* @param[in] float			fSideSizeZEighth		フィールドのZ1/8サイズ
* @details 属しているHitPosのXZ最大最小をポインターとして返す。このエリア内にInPosがあるという
* @author : 木村純(キムラジュン)
*/
void SpeedUpFieldHitPoly(VEC3 InPos, float *HitPosUp, float *HitPosDown, float *HitPosLeft, float *HitPosRight
	,float fSideSizeXQuarter, float fSideSizeZQuarter, float fSideSizeXEighth, float fSideSizeZEighth);


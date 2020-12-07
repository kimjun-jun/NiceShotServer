/**
* @file library.cpp
* @brief ライブラリ関数群
* @author キムラジュン
*/
#include"../h/vec3.h"
#include "../h/library.h"

//=============================================================================
// 当たり判定高速化判定関数
//=============================================================================
void SpeedUpFieldHitPoly(VEC3 InrayS, float *HitPosUp, float *HitPosDown, float *HitPosLeft, float *HitPosRight
	, float fSideSizeXQuarter, float fSideSizeZQuarter, float fSideSizeXEighth, float fSideSizeZEighth)
{

	//判定　X,Zがプラスかマイナスか　基準はg_posFieldの中心(x0,z0)　if()分岐3つだけど長い
	if (InrayS.x >= 0.0f && InrayS.z >= 0.0f)			//親++第一象限
	{
		//子判定　親の時と同じく、第一象限のなかでさらにプラスかマイナスか判定
		if (InrayS.x >= fSideSizeXQuarter && InrayS.z >= fSideSizeZQuarter)			//子++第一象限
		{
			//孫判定　同上
			if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//孫++第一象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//孫-+第二象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//孫--第三象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//孫+-第四象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < fSideSizeXQuarter && InrayS.z >= fSideSizeZQuarter)			//子-+第二象限
		{
			//孫判定　同上
			if (InrayS.x >= fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//孫++第一象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//孫-+第二象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//孫--第三象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//孫+-第四象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < fSideSizeXQuarter && InrayS.z < fSideSizeZQuarter)			//子--第三象限
		{
			//孫判定　同上
			if (InrayS.x >= fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//孫++第一象限
			{
				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//孫-+第二象限
			{
				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//孫--第三象限
			{
				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//孫+-第四象限
			{
				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}

		}
		else if (InrayS.x >= fSideSizeXQuarter && InrayS.z < fSideSizeZQuarter)			//子+-第四象限
		{
			//孫判定　同上
			if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//孫++第一象限
			{
				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//孫-+第二象限
			{
				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//孫--第三象限
			{
				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//孫+-第四象限
			{
				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
		}
	}
	else if (InrayS.x < 0.0f && InrayS.z >= 0.0f)			//親-+第二象限
	{
		//子判定　親の時と同じく、第一象限のなかでさらにプラスかマイナスか判定
		if (InrayS.x >= -fSideSizeXQuarter && InrayS.z >= fSideSizeZQuarter)			//子++第一象限
		{

			//孫判定　同上
			if (InrayS.x >= -fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//孫++第一象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//孫-+第二象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//孫--第三象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//孫+-第四象限
			{
				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
		}
		else if (InrayS.x < -fSideSizeXQuarter && InrayS.z >= fSideSizeZQuarter)			//子-+第二象限
		{
			//孫判定　同上
			if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//孫++第一象限
			{

				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= fSideSizeZQuarter + fSideSizeZEighth)			//孫-+第二象限
			{

				*HitPosUp = fSideSizeZQuarter + fSideSizeZQuarter;
				*HitPosDown = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//孫--第三象限
			{

				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < fSideSizeZQuarter + fSideSizeZEighth)			//孫+-第四象限
			{

				*HitPosUp = fSideSizeZQuarter + fSideSizeZEighth;
				*HitPosDown = fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < -fSideSizeXQuarter && InrayS.z < fSideSizeZQuarter)			//子--第三象限
		{
			//孫判定　同上
			if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//孫++第一象限
			{

				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//孫-+第二象限
			{

				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//孫--第三象限
			{

				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//孫+-第四象限
			{

				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}

		}
		else if (InrayS.x >= -fSideSizeXQuarter && InrayS.z < fSideSizeZQuarter)			//子+-第四象限
		{
			//孫判定　同上
			if (InrayS.x >= -fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//孫++第一象限
			{

				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z >= fSideSizeZEighth)			//孫-+第二象限
			{

				*HitPosUp = fSideSizeZQuarter;
				*HitPosDown = fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//孫--第三象限
			{

				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXEighth && InrayS.z < fSideSizeZEighth)			//孫+-第四象限
			{

				*HitPosUp = fSideSizeZEighth;
				*HitPosDown = 0.0f;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
		}
	}
	else if (InrayS.x < 0.0f && InrayS.z < 0.0f)			//親--第三象限
	{
		if (InrayS.x >= -fSideSizeXQuarter && InrayS.z >= -fSideSizeZQuarter)			//子++第一象限
		{
			//孫判定　同上
			if (InrayS.x >= -fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//孫++第一象限
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//孫-+第二象限
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//孫--第三象限
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//孫+-第四象限
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
		}
		else if (InrayS.x < -fSideSizeXQuarter && InrayS.z >= -fSideSizeZQuarter)			//子-+第二象限
		{
			//孫判定　同上
			if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//孫++第一象限
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//孫-+第二象限
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//孫--第三象限
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//孫+-第四象限
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < -fSideSizeXQuarter && InrayS.z < -fSideSizeZQuarter)			//子--第三象限
		{
			//孫判定　同上
			if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//孫++第一象限
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//孫-+第二象限
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//孫--第三象限
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXQuarter - fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXQuarter - fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//孫+-第四象限
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter - fSideSizeXEighth;
				*HitPosRight = -fSideSizeXQuarter;
			}

		}
		else if (InrayS.x >= -fSideSizeXQuarter && InrayS.z < -fSideSizeZQuarter)			//子+-第四象限
		{
			//孫判定　同上
			if (InrayS.x >= -fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//孫++第一象限
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//孫-+第二象限
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x < -fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//孫--第三象限
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXQuarter;
				*HitPosRight = -fSideSizeXEighth;
			}
			else if (InrayS.x >= -fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//孫+-第四象限
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = -fSideSizeXEighth;
				*HitPosRight = 0.0f;
			}
		}
	}
	else if (InrayS.x >= 0.0f && InrayS.z < 0.0f)			//親+-第四象限
	{
		if (InrayS.x >= fSideSizeXQuarter && InrayS.z >= -fSideSizeZQuarter)			//子++第一象限
		{
			//孫判定　同上
			if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//孫++第一象限
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//孫-+第二象限
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//孫--第三象限
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//孫+-第四象限
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < fSideSizeXQuarter && InrayS.z >= -fSideSizeZQuarter)			//子-+第二象限
		{
			//孫判定　同上
			if (InrayS.x >= fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//孫++第一象限
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z >= -fSideSizeZEighth)			//孫-+第二象限
			{

				*HitPosUp = 0.0f;
				*HitPosDown = -fSideSizeZEighth;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//孫--第三象限
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXEighth && InrayS.z < -fSideSizeZEighth)			//孫+-第四象限
			{

				*HitPosUp = -fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
		}
		else if (InrayS.x < fSideSizeXQuarter && InrayS.z < -fSideSizeZQuarter)			//子--第三象限
		{
			//孫判定　同上
			if (InrayS.x >= fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//孫++第一象限
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//孫-+第二象限
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//孫--第三象限
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = 0.0f;
				*HitPosRight = fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//孫+-第四象限
			{

				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter;
			}

		}
		else if (InrayS.x >= fSideSizeXQuarter && InrayS.z < -fSideSizeZQuarter)			//子+-第四象限
		{
			//孫判定　同上
			if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//孫++第一象限
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z >= -fSideSizeZQuarter - fSideSizeZEighth)			//孫-+第二象限
			{

				*HitPosUp = -fSideSizeZQuarter;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x < fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//孫--第三象限
			{
				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXEighth;
			}
			else if (InrayS.x >= fSideSizeXQuarter + fSideSizeXEighth && InrayS.z < -fSideSizeZQuarter - fSideSizeZEighth)			//孫+-第四象限
			{
				*HitPosUp = -fSideSizeZQuarter - fSideSizeZEighth;
				*HitPosDown = -fSideSizeZQuarter - fSideSizeZQuarter;
				*HitPosLeft = fSideSizeXQuarter + fSideSizeXEighth;
				*HitPosRight = fSideSizeXQuarter + fSideSizeXQuarter;
			}
		}
	}

}


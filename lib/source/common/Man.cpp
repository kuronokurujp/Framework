/**
 *	@file 	D:/work/dungeon/framework/common/Man.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-02
 *	@note 	便利な計算方法を関数で提供
 *
 */
#include "Common/Man.h"

/*
	@brief	円運動座標計算
	@param	i_center_pos	:	円運動の中心座標
	@param	i_radius		:	円の半径
	@return	ip_pos			:	円運動結果の座標取得
*/
Vec3	CalcRotaryPos( const Vec3& i_center_pos, float i_radius )
{
	Vec3	result_pos( -i_radius, 0.f, 0.f );
	
	// 回転行列を作成
	D3DXMATRIXA16	mat_rot_y;
	D3DXMatrixRotationY( &mat_rot_y, timeGetTime() / 1000.0f );
	// 回転行列を回転結果座標に変換
	D3DXVec3TransformCoord( &result_pos, &result_pos, &mat_rot_y );
	// 回転結果座標を中心座標に足す
	D3DXVec3Add( &result_pos, &result_pos, &i_center_pos );

	return result_pos;
}



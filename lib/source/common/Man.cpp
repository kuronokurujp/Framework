/**
 *	@file 	D:/work/dungeon/framework/common/Man.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-02
 *	@note 	•Ö—˜‚ÈŒvZ•û–@‚ğŠÖ”‚Å’ñ‹Ÿ
 *
 */
#include "Common/Man.h"

/*
	@brief	‰~‰^“®À•WŒvZ
	@param	i_center_pos	:	‰~‰^“®‚Ì’†SÀ•W
	@param	i_radius		:	‰~‚Ì”¼Œa
	@return	ip_pos			:	‰~‰^“®Œ‹‰Ê‚ÌÀ•Wæ“¾
*/
Vec3	CalcRotaryPos( const Vec3& i_center_pos, float i_radius )
{
	Vec3	result_pos( -i_radius, 0.f, 0.f );
	
	// ‰ñ“]s—ñ‚ğì¬
	D3DXMATRIXA16	mat_rot_y;
	D3DXMatrixRotationY( &mat_rot_y, timeGetTime() / 1000.0f );
	// ‰ñ“]s—ñ‚ğ‰ñ“]Œ‹‰ÊÀ•W‚É•ÏŠ·
	D3DXVec3TransformCoord( &result_pos, &result_pos, &mat_rot_y );
	// ‰ñ“]Œ‹‰ÊÀ•W‚ğ’†SÀ•W‚É‘«‚·
	D3DXVec3Add( &result_pos, &result_pos, &i_center_pos );

	return result_pos;
}



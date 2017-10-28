/**
 *	@file 	D:/work/dungeon/framework/common/Man.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-02
 *	@note 	�֗��Ȍv�Z���@���֐��Œ�
 *
 */
#include "Common/Man.h"

/*
	@brief	�~�^�����W�v�Z
	@param	i_center_pos	:	�~�^���̒��S���W
	@param	i_radius		:	�~�̔��a
	@return	ip_pos			:	�~�^�����ʂ̍��W�擾
*/
Vec3	CalcRotaryPos( const Vec3& i_center_pos, float i_radius )
{
	Vec3	result_pos( -i_radius, 0.f, 0.f );
	
	// ��]�s����쐬
	D3DXMATRIXA16	mat_rot_y;
	D3DXMatrixRotationY( &mat_rot_y, timeGetTime() / 1000.0f );
	// ��]�s�����]���ʍ��W�ɕϊ�
	D3DXVec3TransformCoord( &result_pos, &result_pos, &mat_rot_y );
	// ��]���ʍ��W�𒆐S���W�ɑ���
	D3DXVec3Add( &result_pos, &result_pos, &i_center_pos );

	return result_pos;
}



/**
 *	@file 	Ray.h
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-12-15
 *	@note 
 *
 */
#ifndef __GEMOETRY_RAY_H__
#define __GEMOETRY_RAY_H__

#include "directx/Manager.h"
#include "common/Man.h"

namespace GameLib
{
	/*
		@note	�����`��
	*/
	class Ray
	{
	public:
		Ray();
		~Ray();

		/*
			@brief	�n�_�ƏI�_�̎w��
			@param	i_spos	:	�n�_���W
			@param	i_epos	:	�I�_���W
		*/
		void	SetLinePos( Vec3&	i_spos,	Vec3&	i_epos );

		/*
			@brief	�`����W�ݒ�
			@param	i_pos	:	���W
		*/
		void	SetPos( Vec3&	i_pos	);

		/*
			@brief	�F
		*/
		void	SetColor( const unsigned i_rgb ) { m_color = i_rgb; }

		//	�`��
		void	Draw();
	private:
		//	�ϐ�
		Vec3		m_spos, m_epos,	m_pos;
		unsigned	m_color;		// �J���[
	};
}

#endif // __GEMOETRY_RAY_H__

/**
 *	@file 	/game/graphics/Camera.h
 *	@brief	�J��������
 *	@author	yuto uchida
 *	@data   2010-12-02
 *	@note	�J�����̒��S���𓮂����ꍇ�͒����_��
 *			�ʒu�𓮂������͍��W��ύX����B
 *
 */
#ifndef __GAME_SYSTEM_CAMERA_H__
#define __GAME_SYSTEM_CAMERA_H__

#include "common/Man.h"

namespace GameLib
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		/*
			@brief	�X�V
		*/
		void Update();

		/*
			@brief	�ʒu�ݒ�
		*/
		void	SetPos( const Vec3& i_pos );
		/*
			@brief	�����ʒu�ݒ�
		*/
		void	SetTarget( const Vec3& i_target );
		/*
			@brief	�Y�[���W���ݒ�
		*/
		void	SetZoom( const float& i_zoom );

		//	�r���[�s��擾
		const Marixt4x4&	GetViewMat()	{ return m_ViewMat; }
		//	�ˉe�s��擾
		const Marixt4x4&	GetProjMat()	{ return m_ProjMat; }

		/*
			�擾�֘A
		*/
		const Vec3&	GetPos() const { return m_pos; }
		const Vec3& GetTarget() const { return m_target; }
		const float GetYaw();
		const float GetPitch();
		const float GetRoll();
		//	���_�ƈʒu�̕����x�N�g��
		const Vec3&	GetDist()	{ return m_Dist; }

		/*
			@brief	�J�����̃f�o�b�O������ʂɏo��
			@param	in_BaseXPos	: �\���o�͊�_X���W
			@param	in_BaseYPos	: �\���o�͊�_Y���W
		*/
		void	DebugPrint( const int in_BaseXPos, const int in_BaseYPos );

	private:
		Vec3	m_pos;			// �J�����ʒu
		Vec3	m_target;		// ���Ă���ӏ��̍��W
		Vec3	m_up;			// �J���������(�p������Ɏg��)
		float	m_zoom;			// �Y�[���W��
		Vec3	m_Dist;

		Marixt4x4	m_ProjMat;
		Marixt4x4	m_ViewMat;
	};
}

#endif // __GAME_SYSTEM_CAMERA_H__

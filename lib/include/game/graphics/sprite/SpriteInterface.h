/********************************************************************
	created:	2012/06/17
	created:	17:6:2012   9:08
	file base:	SpriteInterface
	
	purpose:	
*********************************************************************/
#ifndef __SPRITEINTERFACE_H__
#define __SPRITEINTERFACE_H__

#include "common/Common.h"
#include "common/Man.h"
#include "game/graphics/Camera.h"

namespace	GameLib
{
	class	Texture;

	/*
		@brief	�X�v���C�g�A�N�Z�T�̃C���^�[�t�F�C�X
	*/
	class SpriteInterface
	{
	public:
		SpriteInterface() {};
		virtual ~SpriteInterface()	{}

		//	�쐬
		virtual	const bool	Create( class Texture* in_pTex )	= 0;

		//	�J��
		virtual	void	Destroy()	= 0;

		// �`��
		virtual	void Draw()	= 0;
		virtual void Draw( Camera& in_Cam ) = 0;

		// ���W�ݒ�
		virtual	void SetPos( const Vec3 &vec )	= 0;

		// ���W�擾
		virtual	const Vec3&	GetPos() const	= 0;
		virtual	Vec3 &GetPos()	= 0;

		// �摜�͈͐ݒ�
		virtual	void SetImgRect( RECT_DATA_ST *pRect )	= 0;
		virtual	void SetImgRect( unsigned x, unsigned y, unsigned x2, unsigned y2 )	= 0;
		// �摜�͈͎擾
		virtual	RECT_DATA_ST& GetImgRect()	= 0;

		// �X�v���C�g��]
		virtual	void SetRota(float sita)	= 0;
		// �X�v���C�g�g��k��
		virtual	void SetScale(float scale)	= 0;

		// �F �ݒ�/�擾
		virtual	const unsigned GetAddRGB() const	= 0;
		virtual	void SetAddRGB( unsigned rgb )	= 0;

		// �`��ON/OFF
		virtual	void SetVisible( bool bFlg )	= 0;
		// �A���t�@ON/OFF
		virtual	void EnableAlpha( bool flg )	= 0;
	};
}

#endif // __SPRITEINTERFACE_H__
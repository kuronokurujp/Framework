/********************************************************************
	created:	2012/05/27
	created:	27:5:2012   23:17
	file base:	Sprite3D
	
	purpose:	3D�X�v���C�g�`��
*********************************************************************/
#ifndef __SPRITE3D_H__
#define __SPRITE3D_H__

#include "game/graphics/sprite/SpriteInterface.h"

namespace	DirectX
{
	class	Sprite3DImpl;
}

namespace	GameLib
{
	class	Texture;
	class	Sprite3D : public SpriteInterface
	{
	public:
		//	�R���X�g���N�g
		explicit Sprite3D()	{ _Clear(); }
		~Sprite3D()	{}

		//	�֐�
		const bool	Create( Texture* in_pTex );

		//	�J��
		void	Destroy();

		// �`��
		void Draw();
		void Draw( Camera& in_Cam );

		// ���W�ݒ�
		void SetPos( const Vec3 &vec );

		// ���W�擾
		const Vec3&	GetPos() const;
		Vec3 &GetPos();

		// �摜�͈͐ݒ�
		void SetImgRect( RECT_DATA_ST *pRect )	{}
		void SetImgRect( unsigned x, unsigned y, unsigned x2, unsigned y2 )	{}
		// �摜�͈͎擾
		RECT_DATA_ST& GetImgRect();

		// �X�v���C�g��]
		void SetRota(float sita)	{}
		// �X�v���C�g�g��k��
		void SetScale(float scale)	{}

		// �F �ݒ�/�擾
		const unsigned GetAddRGB() const	{ return	0; }
		void SetAddRGB( unsigned rgb )	{}

		// �`��ON/OFF
		void SetVisible( bool bFlg )	{}
		// �A���t�@ON/OFF
		void EnableAlpha( bool flg )	{}

	private:
		//	�֐�
		void	_Clear();

		//	�ϐ�
		DirectX::Sprite3DImpl*	mp_Impl;
	};
}

#endif // __SPRITE3D_H__

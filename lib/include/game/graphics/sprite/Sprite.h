/**
 *	@file 	Sprite.h
 *	@brief
 *	@author	yuto uchida
 *	@data   2010-02-22
 *	@note
 *
 */
#ifndef __GAME_SPRITE_H__
#define __GAME_SPRITE_H__

#include "game/graphics/sprite/SpriteInterface.h"

namespace DirectX
{
	class SpriteImpl;
}

namespace GameLib
{
	// �X�v���C�g�P�̃N���X
	class Texture;
	class Sprite : public SpriteInterface
	{
	public:
		// �X�v���C�g�쐬
		Sprite() { _Clear(); }
		virtual ~Sprite();

		//	�쐬
		const bool	Create( class Texture* in_pTex );

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
		void SetImgRect( RECT_DATA_ST *pRect );
		void SetImgRect( unsigned x,	unsigned y,
						 unsigned x2,	unsigned y2 );
		// �摜�͈͎擾
		RECT_DATA_ST& GetImgRect();

		// �X�v���C�g��]
		void SetRota(float sita);
		// �X�v���C�g�g��k��
		void SetScale(float scale);
		
		// �F �ݒ�/�擾
		const unsigned GetAddRGB() const;
		void SetAddRGB( unsigned rgb );
				
		// �`��ON/OFF
		void SetVisible( bool bFlg );
		// �A���t�@ON/OFF
		void EnableAlpha( bool flg );

	protected:
		DirectX::SpriteImpl *mp_Impl;

		Texture *mp_Tex;

	private:
		//	�֐�
		void	_Clear()	{ mp_Impl	= NULL; mp_Tex	= NULL; }

		bool mb_Alpha;
	};

} // namespace GameLib


#endif // __GAME_SPRITE_H__

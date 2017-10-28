/**
 *	@file 	Sprite.cpp
 *	@brief
 *	@author	yuto uchida
 *	@data   2009-08-01
 *	@note
 *
 */
#include "game/graphics/sprite/Sprite.h"
#include "game/graphics/texture/Texture.h"

#include "common/Man.h"
#include "directx/graphics/SpriteImpl.h"

namespace GameLib {

	// �X�v���C�g�P�̃N���X
	Sprite::~Sprite()
	{
		Destroy();
	}

	//	�쐬
	const bool	Sprite::Create( class Texture* in_pTex )
	{
		// ���̏����͊�{�܂���
		// �O������̃e�N�X�`�������폜����邩�킩��Ȃ�����
		// �ŏI�I�ɂ̓X�}�[�g�|�C���g�ɂ���K�v�������B
		mp_Tex = in_pTex;
		ASSERT(mp_Tex);
		mp_Impl = new DirectX::SpriteImpl( mp_Tex->GetTex(),
			mp_Tex->GetWidth(), mp_Tex->GetHeight() );

		ASSERT( mp_Impl );
		mp_Tex->DenableTransColor();

		return	true;
	}

	//	�J��
	void	Sprite::Destroy()
	{
		SAFE_DELETE( mp_Impl );
	}

	// �摜�͈͐ݒ�
	void Sprite::SetImgRect( RECT_DATA_ST*pRect )
	{
		mp_Impl->SetImgRect( pRect );
	}

	void Sprite::SetImgRect( unsigned x, unsigned y, unsigned x2, unsigned y2 )
	{
		mp_Impl->SetImgRect(x, y, x2, y2);
	}

	RECT_DATA_ST&	Sprite::GetImgRect() { return mp_Impl->GetImgRect(); }

	// ���W�ݒ�
	void Sprite::SetPos( const Vec3 &vec ) { mp_Impl->SetPos(vec); }

	// �A���t�@�ݒ�
	void Sprite::EnableAlpha( bool flg ) { mb_Alpha = flg; }

	// �F �ݒ�/�擾
	const unsigned Sprite::GetAddRGB() const { return mp_Impl->GetAddRGB(); }
	void Sprite::SetAddRGB( unsigned rgb ) { mp_Impl->SetAddRGB(rgb); }
	// �X�v���C�g��]
	void Sprite::SetRota( float sita ) { mp_Impl->Rota(sita); }
	// �X�v���C�g�g��k��
	void Sprite::SetScale( float scale ) { mp_Impl->Scale(scale); }
	
	// �`��
	void Sprite::Draw()
	{
		if( mb_Alpha == true )
		{
			mp_Tex->EnableTransColor();

			mp_Impl->Draw();

			mp_Tex->DenableTransColor();
		}
		else
		{
			mp_Impl->Draw();
		}
	}

	void Sprite::Draw( Camera& in_Cam )
	{
		Draw();
	}

	
	// ���W�擾
	const Vec3&	Sprite::GetPos() const	{ return	mp_Impl->GetPos(); }
	Vec3&	Sprite::GetPos() { return mp_Impl->GetPos(); }

	// �`��ON/OFF
	void Sprite::SetVisible( bool bFlg ) {  mp_Impl->SetVisible(bFlg); };
	
} // namespace GameLib {

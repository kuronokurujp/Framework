/**
 *	@file 	Texture.cpp
 *	@brief
 *	@author	yuto uchida
 *	@data   2009-08-25
 *	@note
 *
 */
#include "game/graphics/texture/Texture.h"

#include "common/Common.h"
#include "directx/graphics/TextureImpl.h"

namespace GameLib {

    Texture::Texture()
		:	m_SetFlg( false )
	{
		mp_Impl = new DirectX::TextureImpl();
		ASSERT(mp_Impl);
    }

    Texture::~Texture() { SAFE_DELETE(mp_Impl); }

	/*
		@brief	�摜�t�@�C�����e�N�X�`���[�ɓ\��t����	
	*/
	const bool Texture::CreateImage( char *const pImgFileName, unsigned colorKey )
	{
		m_SetFlg	= true;
		return	mp_Impl->CreateImage( pImgFileName, colorKey );
	}

	/*
		@brief	��̃e�N�X�`���[�쐬
		@return	true : ���� / false : ���s
	*/
	const bool Texture::CreateEmpty( unsigned int w, unsigned int h )
	{
		m_SetFlg	= true;
		return	mp_Impl->CreateEmpty( w, h );
	}

	/*
		@brief	�j��
	*/
	void	Texture::Destroy()
	{
		m_SetFlg	= false;
		mp_Impl->Destroy();
	}


    // �e�N�X�`���T�C�Y
    unsigned Texture::GetWidth() const { return mp_Impl->GetWidth(); }
    unsigned Texture::GetHeight() const { return mp_Impl->GetHeight(); }
    // �e�N�X�`����������
    void Texture::Write(unsigned int *pSrc, unsigned int w, unsigned int h)
	{
		mp_Impl->Write(pSrc, w, h);
    }

    // �e�N�X�`����������(�P�Fonly)
    void Texture::Write(unsigned int color) { mp_Impl->Write(color); }

    // �e�N�X�`�������FON/OFF
    void Texture::EnableTransColor() { mp_Impl->EnableTransColor(); }
    void Texture::DenableTransColor() { mp_Impl->DenableTransColor(); }

    // ���S��DirecX��p
    IDirect3DTexture9** Texture::GetTex() const { return (mp_Impl->GetTex()); }
}
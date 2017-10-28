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
		@brief	画像ファイルをテクスチャーに貼り付ける	
	*/
	const bool Texture::CreateImage( char *const pImgFileName, unsigned colorKey )
	{
		m_SetFlg	= true;
		return	mp_Impl->CreateImage( pImgFileName, colorKey );
	}

	/*
		@brief	空のテクスチャー作成
		@return	true : 成功 / false : 失敗
	*/
	const bool Texture::CreateEmpty( unsigned int w, unsigned int h )
	{
		m_SetFlg	= true;
		return	mp_Impl->CreateEmpty( w, h );
	}

	/*
		@brief	破棄
	*/
	void	Texture::Destroy()
	{
		m_SetFlg	= false;
		mp_Impl->Destroy();
	}


    // テクスチャサイズ
    unsigned Texture::GetWidth() const { return mp_Impl->GetWidth(); }
    unsigned Texture::GetHeight() const { return mp_Impl->GetHeight(); }
    // テクスチャ書き込み
    void Texture::Write(unsigned int *pSrc, unsigned int w, unsigned int h)
	{
		mp_Impl->Write(pSrc, w, h);
    }

    // テクスチャ書き込み(単色only)
    void Texture::Write(unsigned int color) { mp_Impl->Write(color); }

    // テクスチャ抜き色ON/OFF
    void Texture::EnableTransColor() { mp_Impl->EnableTransColor(); }
    void Texture::DenableTransColor() { mp_Impl->DenableTransColor(); }

    // 完全にDirecX専用
    IDirect3DTexture9** Texture::GetTex() const { return (mp_Impl->GetTex()); }
}
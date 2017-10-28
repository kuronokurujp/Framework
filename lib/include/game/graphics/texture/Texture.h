/**
 *	@file 	Texture.h
 *	@brief
 *	@author	yuto uchida
 *	@data   2009-08-25
 *	@note
 *
 */
#ifndef __GAME_TEXTURE_H__
#define __GAME_TEXTURE_H__

#include "directx/Manager.h"

namespace DirectX
{
	class TextureImpl;
}

namespace GameLib
{
    class Texture
	{
	public:
		/*
			コンストラクタ
		*/
		explicit Texture();
		~Texture();

		/*
			@brief	画像ファイルをテクスチャーに貼り付ける	
			@return	true : 成功 / false : 失敗
		*/
		const bool CreateImage( char *const pImgFileName, unsigned colorKey = 0 );

		/*
			@brief	空のテクスチャー作成
			@return	true : 成功 / false : 失敗
		*/
		const bool CreateEmpty( unsigned int w, unsigned int h );

		/*
			@brief	破棄
		*/
		void	Destroy();

		const bool IsEmpty() const { return m_SetFlg == false; }

		// テクスチャサイズ
		unsigned GetWidth() const;
		unsigned GetHeight() const;

		// テクスチャ書き込み
		void Write(unsigned int *pSrc, unsigned int w, unsigned int h);
		// テクスチャ書き込み(単色only)
		void Write(unsigned int color);

		// テクスチャ抜き色設定
		void EnableTransColor();
		void DenableTransColor();

		// DirectX専用
		IDirect3DTexture9** GetTex() const;

		//	大本のテクスチャ制御クラス
		DirectX::TextureImpl*	GetTexImpl()	{ return mp_Impl; }

	private:
		bool	m_SetFlg;
		DirectX::TextureImpl *mp_Impl;
    };

} // namespace GameLib {

#endif // __GAME_TEXTURE_H__

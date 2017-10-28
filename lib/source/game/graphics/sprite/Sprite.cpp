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

	// スプライト単体クラス
	Sprite::~Sprite()
	{
		Destroy();
	}

	//	作成
	const bool	Sprite::Create( class Texture* in_pTex )
	{
		// この処理は基本まずい
		// 外部からのテクスチャがいつ削除されるかわからないから
		// 最終的にはスマートポイントにする必要があるん。
		mp_Tex = in_pTex;
		ASSERT(mp_Tex);
		mp_Impl = new DirectX::SpriteImpl( mp_Tex->GetTex(),
			mp_Tex->GetWidth(), mp_Tex->GetHeight() );

		ASSERT( mp_Impl );
		mp_Tex->DenableTransColor();

		return	true;
	}

	//	開放
	void	Sprite::Destroy()
	{
		SAFE_DELETE( mp_Impl );
	}

	// 画像範囲設定
	void Sprite::SetImgRect( RECT_DATA_ST*pRect )
	{
		mp_Impl->SetImgRect( pRect );
	}

	void Sprite::SetImgRect( unsigned x, unsigned y, unsigned x2, unsigned y2 )
	{
		mp_Impl->SetImgRect(x, y, x2, y2);
	}

	RECT_DATA_ST&	Sprite::GetImgRect() { return mp_Impl->GetImgRect(); }

	// 座標設定
	void Sprite::SetPos( const Vec3 &vec ) { mp_Impl->SetPos(vec); }

	// アルファ設定
	void Sprite::EnableAlpha( bool flg ) { mb_Alpha = flg; }

	// 色 設定/取得
	const unsigned Sprite::GetAddRGB() const { return mp_Impl->GetAddRGB(); }
	void Sprite::SetAddRGB( unsigned rgb ) { mp_Impl->SetAddRGB(rgb); }
	// スプライト回転
	void Sprite::SetRota( float sita ) { mp_Impl->Rota(sita); }
	// スプライト拡大縮小
	void Sprite::SetScale( float scale ) { mp_Impl->Scale(scale); }
	
	// 描画
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

	
	// 座標取得
	const Vec3&	Sprite::GetPos() const	{ return	mp_Impl->GetPos(); }
	Vec3&	Sprite::GetPos() { return mp_Impl->GetPos(); }

	// 描画ON/OFF
	void Sprite::SetVisible( bool bFlg ) {  mp_Impl->SetVisible(bFlg); };
	
} // namespace GameLib {

/********************************************************************
	created:	2012/01/09
	created:	9:1:2012   21:17
	file base:	SpriteAnim
	
	purpose:	スプライトアニメ
*********************************************************************/
#include "game/graphics/sprite/SpriteAnim.h"

#include "common/Common.h"
#include "game/graphics/sprite/Sprite.h"
#include "game/graphics/sprite/Sprite3D.h"
#include "game/graphics/texture/Texture.h"
#include "game/utl/File.h"

namespace GameLib
{
	/*
		@brief	
	*/
	SpriteAnim::SpriteAnim( GameLib::File* file, const DRAW_TYPE in_Type ) 
	: m_Alpha( 0xff )
	{
		if( file == NULL )
		{
			return;
		}

		mp_Data = new Data(file);
		ASSERT(mp_Data);

		mp_Anim = new Anim(mp_Data);
		ASSERT(mp_Anim);

		unsigned int w = mp_Data->w();
		unsigned int h = mp_Data->h();
		mp_Tex = new Texture();
		ASSERT(mp_Tex);

		if( mp_Tex->CreateEmpty( w, h ) == false )
		{
			ASSERT( 0 );
		}

		// スプライト作成
		if( in_Type == TYPE_2D )		{ mp_Sp = new Sprite(); }
		else if( in_Type == TYPE_3D )	{ mp_Sp	= new Sprite3D(); }

		ASSERT( mp_Sp );
		mp_Sp->Create( mp_Tex );
		mp_Sp->SetImgRect( 0, 0, w, h );
	}

	/*
		@brief	
	*/
	SpriteAnim::~SpriteAnim()
	{
		mp_Tex->Destroy();
		SAFE_DELETE( mp_Tex );
		SAFE_DELETE( mp_Anim );
		SAFE_DELETE( mp_Data );

		mp_Sp->Destroy();
		SAFE_DELETE( mp_Sp );
	}

	// アニメIdx取得
	unsigned SpriteAnim::GetIdxAnim() const
	{
		return	mp_Anim->m_DatIdx;
	}

	// アニメ変更
	void SpriteAnim::ChgIdxAnim( unsigned idx )
	{
		ASSERT( idx < mp_Data->GetDatMax() );
		// アニメフレームを初期化
		mp_Anim->ChgAnim( idx );
	}

	// アニメ変更(名前指定用)
	// まだ作ってない
	void SpriteAnim::ChgNameAnim( const char *const name )
	{
		ASSERT( name );
	}

	void SpriteAnim::PlayLoop( bool bInitFrame )
	{
		mp_Anim->Play(bInitFrame);
		mp_Anim->mb_Loop = true;
	}

	// スプライト回転
	void SpriteAnim::SetRota( float sita ) { mp_Sp->SetRota(sita); }
	// スプライト拡大縮小
	void SpriteAnim::SetScale( float scale ) { mp_Sp->SetScale(scale); }

	// 矩形情報取得
	RECT_DATA_ST& SpriteAnim::GetRect() { return mp_Sp->GetImgRect(); }
	// 座標取得
	Vec3& SpriteAnim::GetPos() { return mp_Sp->GetPos(); }
	// 色 設定/取得
	unsigned SpriteAnim::GetAddRGB() const { return mp_Sp->GetAddRGB(); }
	unsigned char SpriteAnim::GetAlpha() const { return m_Alpha; }

	// 描画ON/OFF
	void SpriteAnim::SetVisible( bool bFlg ) { mp_Sp->SetVisible(bFlg); }
	// 座標設定
	void SpriteAnim::SetPos( const Vec3 &vec )					{ mp_Sp->SetPos(vec); }

	void SpriteAnim::SetAddRGB( unsigned rgb )
	{
		// 透明度をあわせる
		unsigned argb = static_cast<unsigned> (m_Alpha );
		argb = argb << 24;
		argb |= ( rgb & 0x00ffffff );
		mp_Sp->SetAddRGB(argb);
	}

	// 透明度指定
	void SpriteAnim::SetAlpha( const unsigned char a )
	{
		m_Alpha = a - 0xff;
		unsigned rgb = mp_Sp->GetAddRGB();
		SetAddRGB(rgb);
	}

	// 描画
	void SpriteAnim::Draw()
	{
		mp_Tex->EnableTransColor();
		{
			// ピクセル書き込み
			unsigned int w, h;
			w = mp_Data->w();
			h = mp_Data->h();

			unsigned int layerMax = mp_Data->GetLayerMax(mp_Anim->m_DatIdx, mp_Anim->m_NowFrame);
			unsigned int **p = mp_Data->GetAddrPixel(mp_Anim->m_DatIdx, mp_Anim->m_NowFrame);
			for( unsigned int i = 0; i < layerMax; ++i )
			{
				// テクセル更新
				mp_Tex->Write(p[i], w, h);
				// 描画
				mp_Sp->Draw();
			}
		}

		mp_Tex->DenableTransColor();
	}

	void SpriteAnim::Draw( Camera& in_Cam )
	{
		mp_Tex->EnableTransColor();
		{
			// ピクセル書き込み
			unsigned int w, h;
			w = mp_Data->w();
			h = mp_Data->h();

			unsigned int layerMax = mp_Data->GetLayerMax(mp_Anim->m_DatIdx, mp_Anim->m_NowFrame);
			unsigned int **p = mp_Data->GetAddrPixel(mp_Anim->m_DatIdx, mp_Anim->m_NowFrame);
			for( unsigned int i = 0; i < layerMax; ++i )
			{
				// テクセル更新
				mp_Tex->Write(p[i], w, h);
				// 描画
				mp_Sp->Draw( in_Cam );
			}
		}

		mp_Tex->DenableTransColor();
	}

	/*
		画像ファイルからスプライトデータ作成
	*/
	SpriteAnim::Data::Data( GameLib::File* file )
	{
		unsigned file_pos = 0;
		{
			// ヘッダーをパース
			m_Head.max = file->GetUnsigned( file_pos );
			file_pos += sizeof( m_Head.max );

			m_Head.transColor = file->GetUnsigned( file_pos );
			file_pos += sizeof( m_Head.transColor );

			m_Head.w = file->GetUnsigned( file_pos );
			file_pos += sizeof(m_Head.w);

			m_Head.h = file->GetUnsigned( file_pos );
			file_pos += sizeof( m_Head.h );

			m_Head.pixelSize = file->GetUnsigned( file_pos );
			file_pos += sizeof( m_Head.pixelSize );
		}

		struct _tag_galeDat *pPak = NULL;
		mp_Dat = new struct _tag_galeDat[m_Head.max];
		ASSERT(mp_Dat);
		// フレームのパース
		{
			unsigned int frameSize, nameSize, frameMax, layerMax;
			for( unsigned int i = 0; i < m_Head.max; ++i )
			{
				pPak = &mp_Dat[i];
				frameSize = file->GetUnsigned( file_pos );
				file_pos += sizeof( frameSize );

				nameSize = file->GetUnsigned( file_pos );
				file_pos += sizeof( nameSize );

				{
					pPak->pName = new char[nameSize];
					ASSERT( pPak->pName );
					const char* dat = file->Data();
					for( unsigned i = 0; i < nameSize; ++i )
					{
						pPak->pName[0] = dat[file_pos];
						file_pos += 1;
					}

					cprintf( "AnimName => %s\n", pPak->pName );
				}

				frameMax = file->GetUnsigned( file_pos );
				file_pos += sizeof( frameMax );

				cprintf( "frameMax => [%d]\n", frameMax );
				pPak->frameMax = frameMax;
				pPak->pFrame = new struct _tag_galeDat::_tag_frame[frameMax];
				ASSERT(pPak->pFrame);
				for( unsigned fIdx = 0; fIdx < frameMax; ++fIdx )
				{
					pPak->pFrame[fIdx].time = file->GetUnsigned(file_pos);
					file_pos += sizeof( pPak->pFrame[fIdx].time );

					layerMax = file->GetUnsigned( file_pos );
					file_pos += sizeof( layerMax );

					cprintf( "time[%d] => [%d]\n", fIdx, pPak->pFrame[fIdx].time );
					cprintf( "layerMax[%d] => [%d]\n", fIdx, layerMax );

					pPak->pFrame[fIdx].layerMax = layerMax;
					pPak->pFrame[fIdx].p = new unsigned *[layerMax];
					ASSERT(pPak->pFrame[fIdx].p);
					for( unsigned lIdx = 0; lIdx < layerMax; ++lIdx )
					{
						pPak->pFrame[fIdx].p[lIdx] = new unsigned [m_Head.pixelSize];
						ASSERT( pPak->pFrame[fIdx].p[lIdx] );
					}
				}
			}
		}

		// ピクセルのパース
		{
			for( unsigned i = 0; i < m_Head.max; ++i )
			{
				pPak = &mp_Dat[i];
				for( unsigned fIdx = 0; fIdx < pPak->frameMax; ++fIdx )
				{
					for( unsigned int lIdx = 0; lIdx < pPak->pFrame[fIdx].layerMax; ++lIdx )
					{
						for( unsigned p = 0; p < (m_Head.w * m_Head.h); ++p )
						{
							pPak->pFrame[fIdx].p[lIdx][p] = file->GetUnsigned(file_pos);
							file_pos += sizeof( pPak->pFrame[fIdx].p[lIdx][p] );
						}
					}
				}
			}
		}
	}

	SpriteAnim::Data::~Data()
	{
		// メモリ開放
		struct _tag_galeDat *pPak = NULL;
		for( unsigned int i = 0; i < m_Head.max; ++i )
		{
			pPak = &mp_Dat[i];
			for( unsigned int fIdx = 0; fIdx < pPak->frameMax; ++fIdx )
			{
				for( unsigned int lIdx = 0; lIdx < pPak->pFrame[fIdx].layerMax; ++lIdx )
				{
					SAFE_DELETE_ARRAY( pPak->pFrame[fIdx].p[lIdx] );
				}

				SAFE_DELETE_ARRAY( pPak->pFrame[fIdx].p );
			}

			SAFE_DELETE_ARRAY( pPak->pName );
			SAFE_DELETE_ARRAY( pPak->pFrame );
		}

		SAFE_DELETE_ARRAY( mp_Dat );
	}

	SpriteAnim::Anim::Anim( Data *pData ) :
	m_DatIdx( 0 ),
	m_AnimTime( 0 ),
	m_NowFrame( 0 ),
	mf_NowFrame( 0.0f ),
	mf_AnimSpeed( 1.0f ),
	mb_Play( false ),
	mb_Loop( false ),
	mp_Data( NULL ) { mp_Data = pData; }

	void SpriteAnim::Anim::ChgAnim( unsigned idx )
	{
		m_DatIdx = idx;
		m_NowFrame = 0;
		mf_NowFrame = 0.0f;
	}

	// 更新
	void SpriteAnim::Anim::Update()
	{
		if( mb_Play == false ) { return; }

		if( m_AnmTime <= 0.0f )
		{
			mb_Play = false;
			return;
		}

		unsigned int nowTime = timeGetTime();
		unsigned int subTime = nowTime - m_AnmTime;

		subTime = static_cast<unsigned int>(static_cast<float>(subTime) * mf_AnimSpeed);
		const unsigned int putAnimTime = mp_Data->GetAnimTime(m_DatIdx, m_NowFrame);
		if( subTime >= putAnimTime )
		{
			m_AnmTime = nowTime;

			mf_NowFrame += 1.0f;
			unsigned int nNowFrame = static_cast<unsigned int>(mf_NowFrame);
			unsigned int frameMax = mp_Data->GetFrameMax(m_DatIdx);
			if( nNowFrame >= frameMax )
			{
				if( mb_Loop == true )
				{
					mf_NowFrame = 0.0f;
					nNowFrame = 0;
				}
				else
				{
					nNowFrame = frameMax-1;
					mf_NowFrame = static_cast<float>(nNowFrame);
					mb_Play = false;
				}
			}

			m_NowFrame = nNowFrame;
		}
	}

	void SpriteAnim::Anim::Play( bool bInitFrame )
	{
		// 初期化設定
		{
			mf_NowFrame = 0.0f;
			if(bInitFrame == false)
			{
				mf_NowFrame = static_cast<float>(m_NowFrame);
			}
		}

		mb_Loop = false;

		m_AnmTime = timeGetTime();
		mb_Play = true;
	}

}	//	GameLib

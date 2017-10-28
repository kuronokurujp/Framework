/**
 *	@file 	TextureImpl.h
 *	@brief
 *	@author	yuto uchida
 *	@data   2009-08-25
 *	@note
 *
 */
#ifndef __DIRECTX_TEXTURE_IMPL_H__
#define __DIRECTX_TEXTURE_IMPL_H__

#include "directx/Manager.h"
#include "common/Common.h"

namespace DirectX
{
    class TextureImpl
	{
	public:
        // 読み込んだ画像ファイルを貼り付けて作成
        explicit TextureImpl::TextureImpl() :
        mp_Tex(NULL),
		mp_Surface( NULL ),
        m_Width(0),
        m_Height(0),
        mpp_Tex(&mp_Tex) {}

        TextureImpl::~TextureImpl()
		{
			Destroy();
        }

		/*
			@brief	画像ファイルをテクスチャーに貼り付ける	
			@return	true : 成功 / false : 失敗
		*/
		const bool CreateImage( char *const pImgFileName, unsigned int colorKey )
		{
			//	すでに読み込んでいるなら一旦削除する
			Destroy();

			ASSERT( pImgFileName );

			// 画像サイズを２のべき乗にする
			HRESULT hr = D3DXCreateTextureFromFileEx( Manager::Inst().GetDevice(),
				pImgFileName, D3DX_DEFAULT, D3DX_DEFAULT,
				1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
				D3DX_FILTER_NONE, D3DX_DEFAULT, colorKey, 0, 0,
				&mp_Tex
				);
			ASSERT(!FAILED(hr));

			_SetTexDat(mp_Tex);

			return	true;
		}

		/*
			@brief	空のテクスチャー作成
			@return	true : 成功 / false : 失敗
		*/
		const bool CreateEmpty( unsigned int w, unsigned int h )
		{
			//	すでに読み込んでいるなら一旦削除する
			Destroy();

			LPDIRECT3DDEVICE9 p = Manager::Inst().GetDevice();
			ASSERT(p);
			// ピクセルサイズ8bit(ARGB) 各4byte
			HRESULT hr = p->CreateTexture(	w, h, 1, 0, D3DFMT_A8R8G8B8,
											D3DPOOL_MANAGED, &mp_Tex, NULL );
			ASSERT( FAILED( hr ) == false );

			_SetTexDat(mp_Tex);

			Write( 0 );

			return	true;
		}

		/*
			@brief	破棄
		*/
		void	Destroy()
		{
			SAFE_RELEASE( mp_Surface );
			SAFE_RELEASE( mp_Tex );
		}

        // テクスチャ抜き色設定
        void EnableTransColor()
		{
            LPDIRECT3DDEVICE9 p = Manager::Inst().GetDevice();
            ASSERT(p);
			// アルファブレンディングを有効にする。
			// 透過色のピクセルは完全透明ピクセルになっているから
			// これを有効にしないと透過したピクセルが描画される。
            p->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

			// 下記の設定でテクセルのAlpha値を反映させる
			// 合成したい画像
			// D3DBLEND_SRCALPHA -> 画像ARGB
	        p->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			// バッファ画像(元の画像)
			// D3DBLEND_INVSRCALPHA -> 合成画像のARGB反転
            p->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        }

        void DenableTransColor()
		{
            LPDIRECT3DDEVICE9 p = Manager::Inst().GetDevice();
            ASSERT(p);
            p->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
        }

        // テクスチャ書き込み
        void Write(unsigned int *pSrc, unsigned int w, unsigned int h)
		{
            {
				ASSERT( mp_Tex );
				ASSERT( mp_Surface );

                ASSERT(pSrc);
                ASSERT(m_Width <= w);
                ASSERT(m_Height <= h);
            }

            {
                unsigned int *pDst = NULL;
                int pitch;
                _Lock(&pDst, &pitch);

                for( unsigned int y=0; y<h; ++y )
				{
                    memcpy(pDst, pSrc, sizeof(pSrc[0]) * w);

                    pSrc += w;
                    pDst += pitch >> 2;
                }

                _Unlock(&pDst);
            }
        }

        // テクスチャ書き込み(単色only)
        void Write(unsigned int color)
		{
			ASSERT( mp_Tex );
			ASSERT( mp_Surface );

            unsigned int w = m_Width;
            unsigned int h = m_Height;
            {
                unsigned int *pDst = NULL;
                int pitch;
                _Lock(&pDst, &pitch);

                for( unsigned int y=0; y<h; ++y )
				{
                    for( unsigned int x=0; x<w; ++x )
					{
                        pDst[x] = color;
                    }

                    pDst += pitch >> 2;
                }

                _Unlock(&pDst);
            }
        }

        // テクスチャサイズ
        const unsigned GetWidth() const { return m_Width; }
        const unsigned GetHeight() const { return m_Height; }

        IDirect3DTexture9 **GetTex() const { return mpp_Tex; }

	private:
		//	変数
		IDirect3DTexture9	*mp_Tex;
		IDirect3DTexture9	**mpp_Tex;

		IDirect3DSurface9	*mp_Surface;
		D3DSURFACE_DESC		m_SurfaceInfo;

		unsigned int m_Width, m_Height;

		void _SetTexDat(IDirect3DTexture9 *const pTex)
		{
			ASSERT(pTex);
			// サーフェイスを取得
			pTex->GetSurfaceLevel( 0, &mp_Surface );
			{
				// テクスチャー情報取得
				mp_Surface->GetDesc( &m_SurfaceInfo );

				m_Width = m_SurfaceInfo.Width;
				m_Height = m_SurfaceInfo.Height;
			}
		}

		void _Lock( unsigned int **ppAddr, int *pPitch, int iMipLevel = 0)
		{
			ASSERT(ppAddr);
			ASSERT(pPitch);

			D3DLOCKED_RECT rect;
			HRESULT hr = mp_Tex->LockRect(iMipLevel, &rect, NULL, 0);
			ASSERT( hr != D3DERR_INVALIDCALL );
			ASSERT( hr != D3DERR_WASSTILLDRAWING );

			*ppAddr = static_cast<unsigned int*>(rect.pBits);
			*pPitch = rect.Pitch;
		}

		void _Unlock(unsigned int **ppAddr, int iMipLevel = 0)
		{
			ASSERT(ppAddr);
			ASSERT(*ppAddr);

			mp_Tex->UnlockRect(iMipLevel);
			*ppAddr = NULL;
		}
    };

} // namespace DirectX

#endif // __DIRECTX_TEXTURE_IMPL_H__

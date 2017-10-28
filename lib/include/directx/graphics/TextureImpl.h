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
        // �ǂݍ��񂾉摜�t�@�C����\��t���č쐬
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
			@brief	�摜�t�@�C�����e�N�X�`���[�ɓ\��t����	
			@return	true : ���� / false : ���s
		*/
		const bool CreateImage( char *const pImgFileName, unsigned int colorKey )
		{
			//	���łɓǂݍ���ł���Ȃ��U�폜����
			Destroy();

			ASSERT( pImgFileName );

			// �摜�T�C�Y���Q�ׂ̂���ɂ���
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
			@brief	��̃e�N�X�`���[�쐬
			@return	true : ���� / false : ���s
		*/
		const bool CreateEmpty( unsigned int w, unsigned int h )
		{
			//	���łɓǂݍ���ł���Ȃ��U�폜����
			Destroy();

			LPDIRECT3DDEVICE9 p = Manager::Inst().GetDevice();
			ASSERT(p);
			// �s�N�Z���T�C�Y8bit(ARGB) �e4byte
			HRESULT hr = p->CreateTexture(	w, h, 1, 0, D3DFMT_A8R8G8B8,
											D3DPOOL_MANAGED, &mp_Tex, NULL );
			ASSERT( FAILED( hr ) == false );

			_SetTexDat(mp_Tex);

			Write( 0 );

			return	true;
		}

		/*
			@brief	�j��
		*/
		void	Destroy()
		{
			SAFE_RELEASE( mp_Surface );
			SAFE_RELEASE( mp_Tex );
		}

        // �e�N�X�`�������F�ݒ�
        void EnableTransColor()
		{
            LPDIRECT3DDEVICE9 p = Manager::Inst().GetDevice();
            ASSERT(p);
			// �A���t�@�u�����f�B���O��L���ɂ���B
			// ���ߐF�̃s�N�Z���͊��S�����s�N�Z���ɂȂ��Ă��邩��
			// �����L���ɂ��Ȃ��Ɠ��߂����s�N�Z�����`�悳���B
            p->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

			// ���L�̐ݒ�Ńe�N�Z����Alpha�l�𔽉f������
			// �����������摜
			// D3DBLEND_SRCALPHA -> �摜ARGB
	        p->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			// �o�b�t�@�摜(���̉摜)
			// D3DBLEND_INVSRCALPHA -> �����摜��ARGB���]
            p->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        }

        void DenableTransColor()
		{
            LPDIRECT3DDEVICE9 p = Manager::Inst().GetDevice();
            ASSERT(p);
            p->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
        }

        // �e�N�X�`����������
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

        // �e�N�X�`����������(�P�Fonly)
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

        // �e�N�X�`���T�C�Y
        const unsigned GetWidth() const { return m_Width; }
        const unsigned GetHeight() const { return m_Height; }

        IDirect3DTexture9 **GetTex() const { return mpp_Tex; }

	private:
		//	�ϐ�
		IDirect3DTexture9	*mp_Tex;
		IDirect3DTexture9	**mpp_Tex;

		IDirect3DSurface9	*mp_Surface;
		D3DSURFACE_DESC		m_SurfaceInfo;

		unsigned int m_Width, m_Height;

		void _SetTexDat(IDirect3DTexture9 *const pTex)
		{
			ASSERT(pTex);
			// �T�[�t�F�C�X���擾
			pTex->GetSurfaceLevel( 0, &mp_Surface );
			{
				// �e�N�X�`���[���擾
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

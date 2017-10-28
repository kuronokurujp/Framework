/********************************************************************
	created:	2012/05/27
	created:	27:5:2012   23:16
	file base:	Sprite3DImpl
	
	purpose:	3D�X�v���C�g�`��(�{��)
*********************************************************************/
#ifndef __DIRECTX_SPRITE3DIMPL_H__
#define __DIRECTX_SPRITE3DIMPL_H__

#include "common/Common.h"
#include "directx/Manager.h"
#include "directx/graphics/TextureImpl.h"

namespace DirectX
{
	class TextureImpl;

	class Sprite3DImpl
	{
	public:
		Sprite3DImpl() { _Clear(); }
		~Sprite3DImpl()	{}

		/*
			@brief	�쐬
			@param	�e�N�X�`���[�ݒ�
			@return	�쐬���� : true / ���s : false
		*/
		const bool	Create( TextureImpl* in_pTex )
		{
			mp_Tex	= in_pTex;
			return	true;
		}

		/*
			@brief	�쐬
			@return	�쐬���� : true / ���s : false
		*/
		const bool	Create() { return true; }

		void	Destroy() {}

		/*
			@brief	���W�擾	
		*/
		Vec3*	GetPos()			{ return &m_Pos; }

		/*
			@brief	���W�ݒ�	
		*/
		void	SetPos( const Vec3& in_Pos )
		{
			m_Pos	= in_Pos;
		}

		/*
			@brief	�`��
		*/
		void	Draw(	const bool in_CamFlg,
						const float in_Yaw, const float in_Pitch, const Vec3& in_DistVec,
						const Marixt4x4& in_ViewMat, const Marixt4x4& in_ProjMat )
		{
			DirectX::Manager&	inst	= DirectX::Manager::Inst();
			IDirect3DDevice9*	pDevice	= inst.GetDevice();
			ASSERT( pDevice );

			D3DVIEWPORT9	viewPort;
			pDevice->GetViewport( &viewPort );

			//	�e�N�X�`���[�\��t��
			if( mp_Tex && mp_Tex->GetTex() )
			{
				pDevice->SetTexture( 0, *( mp_Tex->GetTex() ) );
			}
			else
			{
				pDevice->SetTexture( 0, NULL );
			}

			D3DMATERIAL9	material	= DirectX::CreateMaterialData( 1.f, 1.f, 1.f );
			pDevice->SetMaterial( &material );

			if( in_CamFlg == false )
			{
				//	���_
				static	DirectX::VERTEX	aV[]	=
				{
					VERTEX( 0.5f, 2.0f, 0.0f, 0, 0, -1, 1, 0 ),	//	�E��
					VERTEX( 0.5f, 0.0f, 0.0f, 0, 0, -1, 1, 1 ),	//	�E��
					VERTEX(-0.5f, 0.0f, 0.0f, 0, 0, -1, 0, 1 ),	//	����
					VERTEX(-0.5f, 2.0f, 0.0f, 0, 0, -1, 0, 0 ),	//	����
				};

				//	�r���{�[�g����
				Marixt4x4	matView;
				pDevice->GetTransform( D3DTS_VIEW, &matView );

				//	�t�s��쐬
				Marixt4x4	matBillboard	= matView.GetTranspose();
				matBillboard._14	= 0.f;
				matBillboard._24	= 0.f;
				matBillboard._34	= 0.f;

				//	���W�ݒ�
				matBillboard._41	= m_Pos.x;
				matBillboard._42	= m_Pos.y;
				matBillboard._43	= m_Pos.z;

				//	�`��
				pDevice->SetTransform( D3DTS_WORLD, &matBillboard );

				pDevice->SetFVF( DirectX::VERTEX::FVF );
				pDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, aV, sizeof( DirectX::VERTEX ) );
			}
			else
			{
				D3DXMATRIX	m, rot;
				D3DXMatrixRotationYawPitchRoll( &rot, in_Yaw, 0.f, 0.f );
				D3DXMatrixScaling( &m, 1.f, 1.f / (float)cos( in_Pitch ), 1.f );
				D3DXMatrixMultiply( &rot, &m, &rot );

				float	vx	= 0.25f * in_DistVec.x / in_DistVec.y;
				float	vz	= 0.25f * in_DistVec.z / in_DistVec.y;
				float	vy	= 0.f;

				//	���W�ݒ�
				D3DXMatrixTranslation( &m, vx + m_Pos.x, vy + m_Pos.y, vz + m_Pos.z );
				D3DXMatrixMultiply( &m, &rot, &m );

				Vec3	v1( 0.5f, 0.f, 0.f );
				Vec3	v2( -0.5f, 0.f, 0.f );
				Vec3	v3( 0.f, 2.f, 0.f );

				D3DXVec3Project( &v1, &v1, &viewPort, &in_ProjMat, &in_ViewMat, &m );
				D3DXVec3Project( &v2, &v2, &viewPort, &in_ProjMat, &in_ViewMat, &m );
				D3DXVec3Project( &v3, &v3, &viewPort, &in_ProjMat, &in_ViewMat, &m );

				v3.y	= v1.y + ( v1.y - v3.y );

				DirectX::TLVERTEX	aV[]	=
				{
					{ v1.x, v3.y, v1.z, 1, 0xffffffff, 1, 0 },	// �E��
					{ v1.x, v1.y, v2.z, 1, 0xffffffff, 1, 1 },	// �E��
					{ v2.x, v3.y, v1.z, 1, 0xffffffff, 0, 0 },	// ����
					{ v2.x, v2.y, v2.z, 1, 0xffffffff, 0, 1 },	// ����
				};

				pDevice->SetFVF( DirectX::TLVERTEX::FVF );
				pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, aV, sizeof( DirectX::TLVERTEX ) );
			}
		}

	private:
		//	�֐�
		void	_Clear()
		{
			m_Pos.Set( 0.f, 0.f, 0.f );
			mp_Tex	= NULL;
		}

		//	�ϐ�
		Vec3	m_Pos;

		TextureImpl*	mp_Tex;
	};
}

#endif // __DIRECTX_SPRITE3DIMPL_H__

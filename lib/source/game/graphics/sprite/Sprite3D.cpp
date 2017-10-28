/********************************************************************
	created:	2012/05/27
	created:	27:5:2012   23:19
	file base:	Sprite3D
	
	purpose:	3D�X�v���C�g�`��
*********************************************************************/
#include "game/graphics/sprite/Sprite3D.h"

#include "directx/graphics/Sprite3DImpl.h"

#include "game/graphics/texture/Texture.h"

namespace	GameLib
{
	/*
		@brief	�쐬
		@param	in_pTex	: �e�N�X�`���w��
		@return	
	*/
	const bool	Sprite3D::Create( Texture* in_pTex )
	{
		if( mp_Impl != NULL )
		{
			Destroy();
		}

		mp_Impl	= new DirectX::Sprite3DImpl();
		ASSERT( mp_Impl );

		return	mp_Impl->Create( in_pTex->GetTexImpl() );
	}

	/*
		@brief	�j��
	*/
	void	Sprite3D::Destroy()
	{
		if( mp_Impl != NULL )
		{
			mp_Impl->Destroy();
		}

		SAFE_DELETE( mp_Impl );
	}

	/*
		@brief	���W�ݒ�
		@param	in_Pos : ���W
	*/
	void	Sprite3D::SetPos( const Vec3& in_Pos )
	{
		mp_Impl->SetPos( in_Pos );
	}

	/*
		@brief	���W�ݒ�	
	*/
	const Vec3&	Sprite3D::GetPos() const { return	*(mp_Impl->GetPos()); }
	Vec3 &Sprite3D::GetPos()	{ return	*(mp_Impl->GetPos()); }

	// �摜�͈͎擾
	RECT_DATA_ST& Sprite3D::GetImgRect()
	{
		RECT_DATA_ST	rect;
		return	rect;	//	�b��Ώ�
	}

	void Sprite3D::Draw()
	{
		float	yaw		= 0.f;
		float	pitch	= 0.f;
		Vec3	dist;
		Marixt4x4	matProj;
		Marixt4x4	matView;

		mp_Impl->Draw( false, yaw, pitch, dist, matView, matProj );
	}

	void Sprite3D::Draw( Camera& in_Cam )
	{
		float	yaw		= in_Cam.GetYaw();
		float	pitch	= in_Cam.GetPitch();
		Vec3	dist	= in_Cam.GetDist();
		Marixt4x4	matView	= in_Cam.GetViewMat();
		Marixt4x4	matProj	= in_Cam.GetProjMat();

		mp_Impl->Draw( true, yaw, pitch, dist, matView, matProj );
	}

	void Sprite3D::_Clear()
	{
		mp_Impl	= NULL;
	}
}

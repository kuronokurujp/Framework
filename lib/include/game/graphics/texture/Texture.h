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
			�R���X�g���N�^
		*/
		explicit Texture();
		~Texture();

		/*
			@brief	�摜�t�@�C�����e�N�X�`���[�ɓ\��t����	
			@return	true : ���� / false : ���s
		*/
		const bool CreateImage( char *const pImgFileName, unsigned colorKey = 0 );

		/*
			@brief	��̃e�N�X�`���[�쐬
			@return	true : ���� / false : ���s
		*/
		const bool CreateEmpty( unsigned int w, unsigned int h );

		/*
			@brief	�j��
		*/
		void	Destroy();

		const bool IsEmpty() const { return m_SetFlg == false; }

		// �e�N�X�`���T�C�Y
		unsigned GetWidth() const;
		unsigned GetHeight() const;

		// �e�N�X�`����������
		void Write(unsigned int *pSrc, unsigned int w, unsigned int h);
		// �e�N�X�`����������(�P�Fonly)
		void Write(unsigned int color);

		// �e�N�X�`�������F�ݒ�
		void EnableTransColor();
		void DenableTransColor();

		// DirectX��p
		IDirect3DTexture9** GetTex() const;

		//	��{�̃e�N�X�`������N���X
		DirectX::TextureImpl*	GetTexImpl()	{ return mp_Impl; }

	private:
		bool	m_SetFlg;
		DirectX::TextureImpl *mp_Impl;
    };

} // namespace GameLib {

#endif // __GAME_TEXTURE_H__

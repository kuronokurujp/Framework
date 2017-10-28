/**
 *	@file 	manager.h
 *	@brief	DirectX�V�X�e��
 *	@author	yuto uchida
 *	@data   2010-11-29
 *	@note	���̊Ǘ��V�X�e�������[�g�ɂ��ăO���t�B�b�N�X�E���́E������t�Ƃ���B
 *
 */
#ifndef __DIRECTX_MANAGER_H__
#define __DIRECTX_MANAGER_H__

#include <windows.h>
#include <d3d9.h>
#include <tchar.h>

 //@todo ���L�̃C���N���[�h�t�@�C���͎g�����ŎQ�Ƃł��Ȃ��悤�ɂ�����
#include <d3dx9.h>

#include "directx/input/KeyTable.h"

namespace DirectX
{
	// �����[�X���
	#define SAFE_RELEASE(_p_) { if( (_p_) ) { (_p_)->Release(); (_p_) = NULL; } }

	//	��`

	//	���_���
	struct VERTEX {
		float x, y, z;
		float nx, ny, nz;
		float u, v;

		VERTEX() {}
		VERTEX( float _x, float _y, float _z,
			float _nx, float _ny, float _nz,
			float in_u, float in_v ) :
		x(_x), y(_y), z(_z),
			nx(_nx), ny(_ny), nz(_nz),
			u( in_u ), v( in_v ) {}

		void Set(	float _x, float _y, float _z,
			float _nx, float _ny, float _nz,
			float in_u, float in_v )
		{
			x = _x;
			y = _y;
			z = _z;
			nx = _nx;
			ny = _ny;
			nz = _nz;
			u	= in_u;
			v	= in_v;
		}

		enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 } ;
	};

	struct TLVERTEX {
		float x, y, z;
		float rhw;
		DWORD color;
		float tu0, tv0;

		enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 } ;
	} ;

	//	�}�e���A���f�[�^�擾
	//	RGB�l����}�e���A���f�[�^���쐬
	D3DMATERIAL9 CreateMaterialData( float r, float g, float b );

	class Manager
	{
	public:
		//	�萔
		typedef enum
		{
			eNONE	= D3DCULL_NONE,		//	�J�����O���Ȃ�
			eCW		= D3DCULL_CW,		//	�E����ŃJ�����O
			eCCW	= D3DCULL_CCW,		//	������ŃJ�����O
		}eCullMode;

		/*
			@brief	�C���X�^���X�쐬
			@param	�X�N���[���̉���
			@param	�X�N���[���̏c��
			@param	�t���X�N���[�����ǂ���
		*/
		static void Create( HINSTANCE ih_inst, HWND ih_wnd,
							unsigned i_w, unsigned i_h, bool ib_full_screen );

		/*
			@brief	�C���X�^���X�擾
		*/
		static Manager&	Inst() { return *msp_inst; }

		/*
			@brief	�C���X�^���X�j��
		*/
		static void Destroy();

		/*
			@brief	DirectX�̃f�o�C�X�擾
		*/
		IDirect3DDevice9*	GetDevice() const { return mp_d3d_device; }

		/*
			@brief	Z�e�X�g�ݒ�
			@param	: in_Flg �L�� = true / ���� = false
		*/
		void	EnableZTest( const bool in_Flg );

		/*
			@brief	�A���r�G���g�ݒ�
			@param	: in_Color �J���[�l( ARGB )
		*/
		void	SetAmbientColor( const unsigned in_Color );

		/*
			@brief	�J�����O�ݒ�
		*/
		void	SetCullMode( eCullMode in_Mode );

		/*
			@brief	�L�[����
			@param	i_key	:	�w�肵���L�[�����������`�F�b�N
		*/
		bool IsKeyOn(unsigned char i_key);
		bool IsKeyTriggerOn(unsigned char i_key);
		bool IsKeyRepertOn(unsigned char i_key);

		/*
			@brief	�p�b�h����
			@param	i_pad	:	�w�肵���{�^�������������`�F�b�N
		*/
		bool IsPadOn( Input::ePadKey i_pad);
		bool IsPadTriggerOn( Input::ePadKey i_pad);
		bool IsPadRepertOn( Input::ePadKey i_pad);

		//	�w�i�F�ݒ�E�擾
		void SetScreenColor( const unsigned in_rgb )	{ m_rgb = in_rgb; }
		const unsigned	GetScreenColor()	const { return m_rgb; }

		/*
			@breif	�f�o�b�O�e�L�X�g�`��
			@param	ip_str	:	�e�L�X�g
			@param	i_x		:	x���W
			@param	i_y		:	y���W
			@param	i_color	:	�J���[�ݒ�
		*/
		void DrawDebugText( const _TCHAR* ip_str, int i_x, int i_y, const int i_color );

		// ���L�̏����̓V�X�e�����Ŏg�p����̂Ŏg��Ȃ�
		/*
			@brief	���͍X�V
			@note	���͌��ʂ𔽉f
		*/
		void InputUpdate();
		/*
			@brief	�����X�V
			@note	Sound���ʂ𔽉f
		*/
		void SoundUpdate();

		/*
			@note	DirectX�̕`��͏����ƌ�n������ɍs���K�v������
					�`�揈���͏����ƌ�n���̏����̊Ԃɏ����Ȃ��Ɣ��f����Ȃ��B
		*/
		/*
			@brief	�`��O�X�V
		*/
		void DrawPreUpdate();
		/*
			@brief	�`���X�V
		*/
		void DrawPostUpdate();

	private:
		Manager( HINSTANCE ih_inst, HWND ih_wnd, unsigned i_w, unsigned i_h, bool ib_full_screen );
		~Manager();

		//	�ϐ�
		IDirect3D9*			mp_d3d;
		IDirect3DDevice9*	mp_d3d_device;

		LPD3DXFONT			mp_font;
		unsigned int		m_rgb;

		static Manager*	msp_inst;
	};
} // namespace DirectX

#endif // __DIRECTX_MANAGER_H__

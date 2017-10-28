/**
 *	@file 	D:/work/dungeon/framework/game/GameSystem.h
 *	@brief	�Q�[���V�X�e���S
 *	@author	yuto uchida
 *	@data   2010-11-30
 *	@note 	�Q�[���쐬�ɕK�v�ȃV�X�e���N���X
 *			�N��/�X�V/�`�揈���ƃQ�[���ݒ���ł���
 *
 */
#ifndef __GAMESYSTEM_H__
#define __GAMESYSTEM_H__

#include "directx/input/KeyTable.h"
#include "directx/Manager.h"

#include "common/Common.h"
#include "graphics/Camera.h"

namespace GameLib
{
	class GameSystem
	{
	public:
		class GameConfig;

		/*
			���[�U��`���\�b�h
			�������d�v�ŕK���g�����Ŏ������Ȃ��Ƃ����Ȃ��B

			���������͊֐����ɌĂ΂��B
		*/
		/*
			@brief	�Q�[���ݒ�
		*/
		void	Config(GameConfig* in_pData);

		/*
		@brief	������
		@note
		���d�v
		�Q�[���N�����̏���������������
		�t���[�����[�N�v���W�F�N�g�Ŏ��ۂ��Ȃ��B
		�g�p����v���W�F�N�g���Œ��g�̏��������B
		*/
		void	Start();

		/*
		@brief	�X�V
		@note	�Q�[���X�V
		*/
		bool	Update();

		/*
		@brief	�I��
		@note	�Q�[���I�����ɌĂ΂��
		*/
		void	Final();


		/*
			@brief	�C���X�^���X�擾
		*/
		static GameSystem&	Inst();

		/*
			@brief	3D�A�N�e�B�u�J�����擾
		*/
		Camera&	GetActiveCam();

		/*
			@brief	�X�N���[���T�C�Y��Ԃ�	
		*/
		const unsigned GetScreenWidth() const;
		const unsigned GetScreenHeight() const;

		/*
			@breif	�{�^������
			@param	i_key	:	�w�肵���{�^���������ꂽ��
		*/
		bool	IsButtonOn( unsigned char i_key );
		bool	IsButtonTriggerOn( unsigned char i_key );
		bool	IsButtonRepertOn( unsigned char i_key );
		/*
			@breif	�Q�[���p�b�h����
			@param	i_pad	:	�w�肵���{�^���������ꂽ��
		*/
		bool IsPadOn( Input::ePadKey i_pad );
		bool IsPadTriggerOn( Input::ePadKey i_pad );
		bool IsPadRepertOn( Input::ePadKey i_pad );

		//	�w�i�F�ݒ�E�擾
		void SetScreenColor( const unsigned in_rgb );
		const unsigned	GetScreenColor()	const;

		//	�_��`��
		void	DrawPoint( const Vec2& in_Pos );

		/*
			@breif	�f�o�b�O�e�L�X�g�`��
			@param	ip_str	:	�e�L�X�g
			@param	i_x		:	x���W
			@param	i_y		:	y���W
			@param	i_color	:	�e�L�X�g�J���[(ARGB)
		*/
		void DrawDebugText( const char* ip_str, int i_x, int i_y, const int i_color = 0xffffffff );

		//	��`
		/*
			@brief	�Q�[���ݒ�
		*/
		class GameConfig
		{
		public:
			//	�R���X�g���N�^
			GameConfig()	{ _Clear(); }
			~GameConfig()	{}

			//	��`
			typedef enum
			{
				SIZE_640_480	= 0,
				SIZE_NUM,
			} SCREEN_SIZE_ENUM;

			//	�֐�
			void	_Clear();

			const unsigned	GetScreenSizeX() const;
			const unsigned	GetScreenSizeY() const;

			//	�ϐ�
			SCREEN_SIZE_ENUM	m_ScreenSizeType;
			char				m_AppName[ 256 ];
		};

		/*
			@brief	�R���t�B�O�擾
		*/
		const GameConfig&	GetConfig() const;


	private:
		GameSystem();
		~GameSystem()	{}

		Camera*	mp_Cam;
	};

} // namespace GameLib
#endif // __GAMESYSTEM_H__

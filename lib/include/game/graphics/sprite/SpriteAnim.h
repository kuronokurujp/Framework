/**
 *	@file 	Sp.h
 *	@brief	�X�v���C�g�摜����
 *	@author	yuto uchida
 *	@data   2010-03-09
 *	@note	gpc�t�@�C���������N���X
 *
 */
#ifndef __GAME_SPRITE_ANIM_IMP_H__
#define __GAME_SPRITE_ANIM_IMP_H__

#include "common/Man.h"
#include "game/graphics/Camera.h"

namespace GameLib
{
	class	SpriteInterface;
	class	Texture;
	class	File;

	class SpriteAnim
	{
	public:
		//	��`
		enum DRAW_TYPE
		{
			TYPE_2D	= 0,
			TYPE_3D,
		};

		//	�R���X�g���N�^
		SpriteAnim( GameLib::File* file, const DRAW_TYPE in_Type );
		~SpriteAnim();

		// �A�j���ő吔
		unsigned GetMaxAnim() { return mp_Data->GetDatMax(); }

		// �A�j��Idx
		unsigned GetIdxAnim() const;

		// �A�j���ύX
		void ChgIdxAnim( unsigned idx );

		// �A�j���ύX(���O�w��p)
		// �܂�����ĂȂ�
		void ChgNameAnim( const char *const name );

		// �A�j���X�g�b�v
		void Stop() { mp_Anim->mb_Play = false; }
		// �A�j���Đ�
		void Play( bool bInitFrame = false ) { mp_Anim->Play(bInitFrame); }
		//	�A�j���Đ����[�v
		void PlayLoop( bool bInitFrame = false );

		bool IsPlay() { return mp_Anim->mb_Play; }
		// �A�j���X�s�[�h
		void SetAnimSpeed( float speed ) { mp_Anim->mf_AnimSpeed = speed; }
		// �t���[���ݒ�
		void SetAnimFrame( unsigned frame ) { mp_Anim->m_NowFrame = frame; }

		// ���݃t���[��
		const unsigned GetAnimFrame() const { return mp_Anim->m_NowFrame; }
		// �ő�t���[�����擾
		const unsigned GetAnimFrameMax() const { return mp_Data->GetFrameMax(mp_Anim->m_DatIdx); }

		// �X�v���C�g��]
		void SetRota( float sita );
		// �X�v���C�g�g��k��
		void SetScale( float scale );

		// ��`���擾
		RECT_DATA_ST& GetRect();
		// ���W�擾
		Vec3& GetPos();
		// �F �ݒ�/�擾
		unsigned GetAddRGB() const;
		void SetAddRGB( unsigned rgb );

		// �����x�w��
		void SetAlpha( const unsigned char a );
		unsigned char GetAlpha() const;

		// �`��ON/OFF
		void SetVisible( bool bFlg );
		// ���W�ݒ�
		void SetPos( const float x, const float y );
		void SetPos( const Vec3 &vec );
		void SetLeftPos( const float x, const float y );
		void SetLeftPos( const Vec3 &vec );

		// �X�V
		void Update() { mp_Anim->Update(); }

		// �`��
		void Draw();
		void Draw( Camera& in_Cam );
	private:
		//	�X�v���C�g�f�[�^
		class Data
		{
		public:
			//	��`
			//	�t�@�C���w�b�_�[
			struct	_tag_head
			{
				unsigned	max;			//	�X�v���C�g��
				unsigned	transColor;		//	���ߐF
				unsigned	w, h;			//	�X�v���C�g�̏c���T�C�Y
				unsigned	pixelSize;		//	�X�v���C�g�̑��s�N�Z���̃T�C�Y
			} m_Head;

			struct	_tag_galeDat
			{
				unsigned	frameMax;		//	�X�v���C�g�̃t���[����
				char	*pName;				//

				//	�A�j���f�[�^
				struct	_tag_frame
				{
					unsigned	time;		//	�t���[���؂�ւ��^�C��
					unsigned	layerMax;	//	���C�A�E�g��(�P�t���[�����ɑ����̃��C�A�E�g)
					unsigned	**p;
				} *pFrame;
			} *mp_Dat;

			//	�R���X�g���N�^
			Data( GameLib::File* file );
			~Data();

			const unsigned w() const { return m_Head.w; }
			const unsigned h() const { return m_Head.h; }
			const unsigned GetDatMax() const { return m_Head.max; }
			const unsigned GetTransColor() const { return m_Head.transColor; }
			const unsigned GetFrameMax( unsigned datIdx ) const { return mp_Dat[datIdx].frameMax; }
			const unsigned GetLayerMax( unsigned datIdx, unsigned frameIdx ) const
				{ return mp_Dat[datIdx].pFrame[frameIdx].layerMax; }
			const unsigned GetAnimTime( unsigned datIdx, unsigned frameIdx ) const
				{ return mp_Dat[datIdx].pFrame[frameIdx].time; }
			unsigned **GetAddrPixel( unsigned datIdx, unsigned frameIdx )
				{ return mp_Dat[datIdx].pFrame[frameIdx].p; }
		};

		/*
			@brief	�A�j������
		*/
		class Anim
		{
		public:
			//	�R���X�g���N�^
			Anim( Data *pData );
			~Anim() {}

			//	�A�j���ύX
			void ChgAnim( unsigned idx );

			// �X�V
			void Update();
			//	�Đ�
			void Play( bool bInitFrame );

			// Sprite�N���X���̂݌���̃N���X�Ȃ̂�Sprite�N���X�Ńf�[�^�𒼂Ŏg�p�ł���悤�ɂ���B
			// �֐��̃I�[�o�[�w�b�h���|��
			// �ׂ����ݒ�����Ă��郁�\�b�h�ɂ���
			unsigned	m_AnimTime,  m_NowFrame, m_AnmTime, m_DatIdx;
			float	mf_NowFrame, mf_AnimSpeed;
			bool	mb_Play, mb_Loop;
			Data	*mp_Data;
		};

		SpriteInterface	*mp_Sp;
		Texture			*mp_Tex;
		Data			*mp_Data;
		Anim			*mp_Anim;

		unsigned char m_Alpha;
	};

}	//	GameLib

#endif // __GAME_SPRITE_ANIM_IMP_H__


/**
 *	@file 	File.cpp
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-08-14
 *	@note 
 *
 */
#include "game/utl/File.h"

#include <stdio.h>
#include <windows.h>

#include "common/Common.h"

namespace GameLib {

// �t�@�C�����w��
// �t�@�C�����g���q�w��(�g���q�`�F�b�N�Ɏg�p)
// �t�@�C���f�[�^���r�b�N�G���f�B�A���Ȃ��O������false
File::File( const char* ip_filename, const char* ip_ext, bool ib_little_endian )
{
	_Clear();

	Load( ip_filename, ip_ext, ib_little_endian );
}

File::~File()
{
	UnLoad();
}

/*
	@brief	�t�@�C�����[�h
	@return	���[�h���� : true / ���s : false
	@param	[in] ip_filename		: �ǂݍ��ރt�@�C���p�X��
	@param	[in] ip_ext				: �t�@�C�����̊g���q
	@param	[in] ib_little_endian	: �t�@�C���o�C�g�񂪃��g�����r�b�N��
*/
const bool	File::Load( const char* ip_filename, const char* ip_ext, bool ib_little_endian )
{
	mb_little_endian	= ib_little_endian;

	if( ip_ext != NULL ) {
		// �t�@�C���g���q�`�F�b�N
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		// �t�@�C�����̂ݎ��o��
		_splitpath_s(ip_filename, drive, dir, fname, ext);
		if( strcmp(ext, ip_ext) != 0 ) {
			STRING_ASSERT(false, " �t�@�C���Ɋg���q���Ȃ��I�I\n");
			ASSERT(0);
		}
	}

	m_Name	= ip_filename;

	FILE *fp = NULL;
	// �t�@�C���T�C�Y�擾
	{
		fpos_t size = 0;
		fopen_s(&fp, ip_filename, "r");
		ASSERT(fp);
		fseek(fp, 0, SEEK_END);
		fgetpos(fp, &size);
		fclose(fp);

		m_size = static_cast<unsigned>(size);
		mp_data = new char[m_size];
		ASSERT(mp_data);
	}

	// �t�@�C�����J��
	fp = NULL;
	{
		fopen_s(&fp, ip_filename, "r");
		ASSERT(fp);
	}

	// �t�@�C���f�[�^��ǂݍ���
	{
		//	�T�C�Y����萔�ȏ�ł���΃X���b�h�ɂ���
		fread(mp_data, m_size, 1, fp);
	}

	// �t�@�C�������
	{
		fclose(fp);
	}

	return	true;
}

/*
	@brief	�t�@�C���A�����[�h
*/
void	File::UnLoad()
{
	SAFE_DELETE_ARRAY(mp_data);
}

// 4�o�C�g�T�C�Y�̒l�擾
// �ǂ̃f�[�^�ʒu����ǂݏo�����w��
unsigned File::GetUnsigned( int i_dat_pos ) const {
	
	const unsigned char* dat = reinterpret_cast<const unsigned char* >(&mp_data[i_dat_pos]);

	unsigned ret = 0;

	// ���g���G���f�B�A���̏ꍇ
	// ��ʃA�h���X -> ���ʃA�h���X ���l�̕���
	// 1234 �Ȃ� 
	// �A�h���X0	4	��ʃA�h���X
	// �A�h���X1	3	��
	// �A�h���X2	2	��
	// �A�h���X3	1	���ʃA�h���X
	// �r�b�N�G���f�B�A���͂���̋t
	if( mb_little_endian ) {
		ret	=	dat[0];
		ret |=	dat[1] << 8;
		ret |=	dat[2] << 16;
		ret	|=	dat[3] << 24;
	}
	else {
		// �r�b�N�G���f�B�A��
		ret	=	dat[3];
		ret |=	dat[2] << 8;
		ret |=	dat[1] << 16;
		ret	|=	dat[0] << 24;
	}
	return ret;
}

/*
	@brief	������
*/
void	File::_Clear()
{
	mb_little_endian	= false;
	m_size				= 0;
	mp_data				= NULL;

	m_Name.clear();
}

} //namespace GameLib

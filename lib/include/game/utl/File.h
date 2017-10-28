/**
 *	@file 	File.h
 *	@brief	
 *	@author	yuto uchida
 *	@data   2010-08-14
 *	@note 
 *
 */
#ifndef __GAME_UTL_FILE_H__
#define __GAME_UTL_FILE_H__

#include <string>

namespace GameLib
{
class File
{
public:
	// �t�@�C�����w��
	// �t�@�C�����g���q�w��(�g���q�`�F�b�N�Ɏg�p)
	//	�g���q���Ȃ��Ȃ� NULL �w��
	// �t�@�C���f�[�^���r�b�N�G���f�B�A���Ȃ��O������false
	File() { _Clear(); }
	File( const char* ip_filename, const char* ip_ext, bool ib_little_endian = true );
	~File();

	//	�ǂݍ���
	const bool	Load( const char* ip_filename, const char* ip_ext, bool ib_little_endian = true );
	void		UnLoad();

	// �t�@�C���T�C�Y
	unsigned Size() const { return m_size; }
	// �t�@�C���f�[�^�擾
	char*	Data()	const	{ return mp_data; }

	// 4�o�C�g�T�C�Y�̒l�擾
	// �ǂ̃f�[�^�ʒu����ǂݏo�����w��
	unsigned GetUnsigned( int i_dat_pos ) const;

private:
	//	�֐�
	void	_Clear();

	//	�ϐ�
	bool		mb_little_endian;
	unsigned	m_size;
	char*		mp_data;

	std::string	m_Name;
};

} //namespace GameLib

#endif // __GAME_UTL_FILE_H__

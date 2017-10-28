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
	// ファイル名指定
	// ファイル名拡張子指定(拡張子チェックに使用)
	//	拡張子がないなら NULL 指定
	// ファイルデータがビックエンディアンなら第三引数はfalse
	File() { _Clear(); }
	File( const char* ip_filename, const char* ip_ext, bool ib_little_endian = true );
	~File();

	//	読み込み
	const bool	Load( const char* ip_filename, const char* ip_ext, bool ib_little_endian = true );
	void		UnLoad();

	// ファイルサイズ
	unsigned Size() const { return m_size; }
	// ファイルデータ取得
	char*	Data()	const	{ return mp_data; }

	// 4バイトサイズの値取得
	// どのデータ位置から読み出すか指定
	unsigned GetUnsigned( int i_dat_pos ) const;

private:
	//	関数
	void	_Clear();

	//	変数
	bool		mb_little_endian;
	unsigned	m_size;
	char*		mp_data;

	std::string	m_Name;
};

} //namespace GameLib

#endif // __GAME_UTL_FILE_H__

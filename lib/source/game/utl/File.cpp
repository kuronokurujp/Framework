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

// ファイル名指定
// ファイル名拡張子指定(拡張子チェックに使用)
// ファイルデータがビックエンディアンなら第三引数はfalse
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
	@brief	ファイルロード
	@return	ロード成功 : true / 失敗 : false
	@param	[in] ip_filename		: 読み込むファイルパス名
	@param	[in] ip_ext				: ファイル名の拡張子
	@param	[in] ib_little_endian	: ファイルバイト列がリトルかビックか
*/
const bool	File::Load( const char* ip_filename, const char* ip_ext, bool ib_little_endian )
{
	mb_little_endian	= ib_little_endian;

	if( ip_ext != NULL ) {
		// ファイル拡張子チェック
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		// ファイル名のみ取り出す
		_splitpath_s(ip_filename, drive, dir, fname, ext);
		if( strcmp(ext, ip_ext) != 0 ) {
			STRING_ASSERT(false, " ファイルに拡張子がない！！\n");
			ASSERT(0);
		}
	}

	m_Name	= ip_filename;

	FILE *fp = NULL;
	// ファイルサイズ取得
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

	// ファイルを開く
	fp = NULL;
	{
		fopen_s(&fp, ip_filename, "r");
		ASSERT(fp);
	}

	// ファイルデータを読み込む
	{
		//	サイズが一定数以上であればスレッドにする
		fread(mp_data, m_size, 1, fp);
	}

	// ファイルを閉じる
	{
		fclose(fp);
	}

	return	true;
}

/*
	@brief	ファイルアンロード
*/
void	File::UnLoad()
{
	SAFE_DELETE_ARRAY(mp_data);
}

// 4バイトサイズの値取得
// どのデータ位置から読み出すか指定
unsigned File::GetUnsigned( int i_dat_pos ) const {
	
	const unsigned char* dat = reinterpret_cast<const unsigned char* >(&mp_data[i_dat_pos]);

	unsigned ret = 0;

	// リトルエンディアンの場合
	// 上位アドレス -> 下位アドレス が値の並び
	// 1234 なら 
	// アドレス0	4	上位アドレス
	// アドレス1	3	↓
	// アドレス2	2	↓
	// アドレス3	1	下位アドレス
	// ビックエンディアンはこれの逆
	if( mb_little_endian ) {
		ret	=	dat[0];
		ret |=	dat[1] << 8;
		ret |=	dat[2] << 16;
		ret	|=	dat[3] << 24;
	}
	else {
		// ビックエンディアン
		ret	=	dat[3];
		ret |=	dat[2] << 8;
		ret |=	dat[1] << 16;
		ret	|=	dat[0] << 24;
	}
	return ret;
}

/*
	@brief	初期化
*/
void	File::_Clear()
{
	mb_little_endian	= false;
	m_size				= 0;
	mp_data				= NULL;

	m_Name.clear();
}

} //namespace GameLib

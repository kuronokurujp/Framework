/**
 *	@file 	D:/ProgramStady/Game/Lib/Sys/src/sys/input/Manager.h
 *	@brief	入力管理
 *	@author	yuto uchida
 *	@data   2009-11-23
 *	@note	2012/0212	実機動作チェックがまだ
 *						ひとつのデバイスしか対応していない
 *
 */
#ifndef __KEYMANAGERIMPL_H__
#define __KEYMANAGERIMPL_H__

#include <windows.h>

namespace KeyInput
{
    class KeyManagerImpl
	{
	public:

		KeyManagerImpl::KeyManagerImpl() :
		  m_BufCount(0){
			  for( int i=0; i < cnKeyMax; i++ )
			  {
				  m_KeyTbl[0][i] = false;
				  m_KeyTbl[1][i] = false;
				  m_KeyOnRepertCntTbl[ i ] = 0;
			  }
		  }

		  KeyManagerImpl::~KeyManagerImpl() {}

		  void KeyManagerImpl::Update()
		  {
			  m_BufCount = 1 - m_BufCount;
			  unsigned char keyTbl[cnKeyMax];

			  // キー入力更新
			  GetKeyboardState(keyTbl);
			  for( int i=0; i<cnKeyMax; i++ ) {
				  m_KeyTbl[m_BufCount][i] = ( (keyTbl[i] & 0x80) != 0 ) ? true : false;
			  }
		  }

		  bool KeyManagerImpl::IsKeyOn(unsigned char key)
		  {
			  key = ConvKey(key);
			  return m_KeyTbl[m_BufCount][key];
		  }

		  bool KeyManagerImpl::IsKeyTriggerOn(unsigned char key)
		  {
			  key = ConvKey(key);
			  return ( m_KeyTbl[m_BufCount][key] && (!m_KeyTbl[1-m_BufCount][key]) );
		  }

		  bool KeyManagerImpl::IsKeyRepertOn( unsigned char key )
		  {
			  bool	ret	= false;
			  if( IsKeyOn( key ) )
			  {
				  if( m_KeyOnRepertCntTbl[ key ] > cnRepertCnt )
				  {
					  ret	= true;
				  }
				  else
				  {
					  ++m_KeyOnRepertCntTbl[ key ];
				  }
			  }
			  else
			  {
				  m_KeyOnRepertCntTbl[ key ]	= 0;
			  }

			  return ret;
		  }

		  unsigned char KeyManagerImpl::ConvKey(unsigned char key)
		  {
			  if( (key >= 'a') && (key <= 'z') )
			  {
				  // 仮想キーは小文字のa~zを対応していないので、大文字に変換する。
				  // a~zを押したら大文字のA^Zを押したことになっている
				  key = 'A' + (key - 'a');
			  }
			  return key;
		  }

	private:
		//	変数
		static const unsigned int cnKeyMax = 256;
		static const unsigned int cnBufMax = 2;
		static const unsigned int cnRepertCnt	= 10;

		bool			m_KeyTbl[cnBufMax][cnKeyMax];
		unsigned int	m_KeyOnRepertCntTbl[cnKeyMax];
		unsigned char m_BufCount;
    };
}	// namespace	__key_input__

#endif // __KEYMANAGERIMPL_H__

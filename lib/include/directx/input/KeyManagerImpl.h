/**
 *	@file 	D:/ProgramStady/Game/Lib/Sys/src/sys/input/Manager.h
 *	@brief	���͊Ǘ�
 *	@author	yuto uchida
 *	@data   2009-11-23
 *	@note	2012/0212	���@����`�F�b�N���܂�
 *						�ЂƂ̃f�o�C�X�����Ή����Ă��Ȃ�
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

			  // �L�[���͍X�V
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
				  // ���z�L�[�͏�������a~z��Ή����Ă��Ȃ��̂ŁA�啶���ɕϊ�����B
				  // a~z����������啶����A^Z�����������ƂɂȂ��Ă���
				  key = 'A' + (key - 'a');
			  }
			  return key;
		  }

	private:
		//	�ϐ�
		static const unsigned int cnKeyMax = 256;
		static const unsigned int cnBufMax = 2;
		static const unsigned int cnRepertCnt	= 10;

		bool			m_KeyTbl[cnBufMax][cnKeyMax];
		unsigned int	m_KeyOnRepertCntTbl[cnKeyMax];
		unsigned char m_BufCount;
    };
}	// namespace	__key_input__

#endif // __KEYMANAGERIMPL_H__

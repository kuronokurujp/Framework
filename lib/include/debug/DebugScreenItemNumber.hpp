/**
 *	@file 	DebugScreenItemNumber.hpp
 *	@brief	ゲーム画面内でのデバッグ数値制御
 *	@author	yuto uchida
 *	@data   2011-04-18
 *	@note 
 *
 */
#ifndef __DEBUGSCREENITEMNUMBER_HPP__
#define __DEBUGSCREENITEMNUMBER_HPP__

#include "game/GameSystem.h"
#include "debug/DebugScreenItem.h"

#include <stdio.h>

//	数字制御デバッグアイテム
template< class T >
class DbgItemInputNumber	:	public I_DbgItem
{
public:
	DbgItemInputNumber( 	const char*	in_pText,
							T*	out_pAddr,
							T	in_InitNum,
							T	in_MinNum,
							T	in_MaxNum,
							T	in_PointNum	 )
	{
		::memset( m_pText, 0, sizeof( m_pText[ 0 ]) * eTEXT_MAX );
		if( in_pText != NULL ) {
			::strcpy_s( m_pText, in_pText );
		}

		m_Num		= in_InitNum;
		m_MinNum	= in_MinNum;
		m_MaxNum	= in_MaxNum;
		m_PointNum	= in_PointNum;

		if( out_pAddr != NULL )
		{
			m_pData		= out_pAddr;
		}

		m_Num	= ClampNum( m_Num );
	}

	virtual	~DbgItemInputNumber( void ){ m_pData	= NULL; }

	/*
		@brief	更新	
	*/
	virtual void	Update( void )
	{
		GameLib::GameSystem&	inst	= GameLib::GameSystem::Inst();
		if( ( inst.IsButtonTriggerOn( Input::KEY_LEFT ) ) ||
			( inst.IsButtonRepertOn( Input::KEY_LEFT) )	) {
			// 減らす
			m_Num	-= m_PointNum;
		}
		else if( 	( inst.IsButtonTriggerOn( Input::KEY_RIGHT ) ) ||
					( inst.IsButtonRepertOn( Input::KEY_RIGHT ) ) )
		{
			// 増やす
			m_Num	+= m_PointNum;
		}

		m_Num	= ClampNum( m_Num );
	}

	/*
		@brief	描画	
	*/
	virtual void Draw(const bool in_ActiveFlg,	const int in_X, const int in_Y )
	{
		// テキスト生成
		int	Color	= 0xffffffff;
		if( in_ActiveFlg == true )
		{
			Color	= 0xffff0000;
		}

		char	Text[ eTEXT_MAX ] = { 0 };
		CreateDrawText( Text );
		GameLib::GameSystem::Inst().DrawDebugText( Text, in_X, in_Y, Color );
	}

protected:
	enum
	{
		eTEXT_MAX	= 64,
	};

	T*	m_pData;
	char	m_pText[eTEXT_MAX];

	virtual void	CreateDrawText( char*	in_pText	)
	{
		::sprintf_s( in_pText, DbgItemInputNumber::eTEXT_MAX, "%s　%d", m_pText, (int)(*m_pData) );
	}

private:

	T	m_Num;
	T	m_MinNum;
	T	m_MaxNum;
	T	m_PointNum;

	T	ClampNum( T in_Num )
	{
		if( in_Num < m_MinNum )
		{
			in_Num	=  m_MinNum;
		}

		if( m_Num > m_MaxNum )
		{
			in_Num	=  m_MaxNum;
		}

		if( m_pData != NULL )
		{
			(*m_pData)	= in_Num;
		}

		return	in_Num;
	}
};

//	変数型違い
typedef DbgItemInputNumber< unsigned int >		DbgItemInputUInterger;
typedef DbgItemInputNumber< unsigned short >	DbgItemInputUShort;
typedef DbgItemInputNumber< unsigned char >		DbgItemInputUChar;
typedef DbgItemInputNumber< int >				DbgItemInputInterger;
typedef DbgItemInputNumber< short >				DbgItemInputShort;
typedef DbgItemInputNumber< char >				DbgItemInputChar;

//	浮動小数点は出力書式指定がことなるので別個で作成
class DbgItemInputFloat	:	public DbgItemInputNumber< float >
{
public:
	DbgItemInputFloat(	const char* in_pText,
							float* out_pAddr,
							float in_InitNum,
							float in_MinNum,
							float in_MaxNum, 
							float in_PointNum	 )	:
		DbgItemInputNumber( in_pText, out_pAddr, in_InitNum,	in_MinNum, in_MaxNum, in_PointNum ) {}
	virtual ~DbgItemInputFloat( void )	{}

protected:
	/*
		@brief	出力すテキスト作成	
	*/
	void	CreateDrawText( char*	in_pText )
	{
		::sprintf_s( in_pText, DbgItemInputNumber::eTEXT_MAX, "%s　%lf", m_pText, (*m_pData) );
	}
};

class DbgItemInputDouble	:	public DbgItemInputNumber< double >
{
public:
	DbgItemInputDouble(	const char* in_pText,
							double* out_pAddr,
							double in_InitNum,
							double in_MinNum,
							double in_MaxNum,
							double in_PointNum	 )	:
		DbgItemInputNumber( in_pText, out_pAddr, in_InitNum,	in_MinNum, in_MaxNum, in_PointNum ) {}
	virtual ~DbgItemInputDouble( void )	{}

protected:
	/*
		@brief	出力すテキスト作成	
	*/
	void	CreateDrawText( char*	in_pText )
	{
		::sprintf_s( in_pText, DbgItemInputNumber::eTEXT_MAX, "%s　%f", m_pText, (*m_pData) );
	}
};

#endif // __DEBUGSCREENITEMNUMBER_HPP__

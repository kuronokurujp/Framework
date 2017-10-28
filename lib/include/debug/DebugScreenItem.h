/**
 *	@file 	DebugScreenItem.h
 *	@brief	
 *	@author	yuto uchida
 *	@data   2011-05-03
 *	@note 
 *
 */
#ifndef __DEBUGSCREENITEM_H__
#define __DEBUGSCREENITEM_H__

/*
	デバッグ要素
*/
class I_DbgItem
{
public:
	I_DbgItem()				{}
	virtual	~I_DbgItem()	{}

	virtual	void	Update( void )	=	0;
	virtual void	Draw( const bool in_ActiveFlg,	const int in_X, const int in_Y )	= 0;
};


#endif // __DEBUGSCREENITEM_H__

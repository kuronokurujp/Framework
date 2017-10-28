/**
 *	@file 	D:/ProgramStady/Game/frame_work/sys/src/win/input/KeyTable.h
 *	@brief
 *	@author	yuto uchida
 *	@data   2010-02-25
 *	@note
 *
 */
#ifndef __KeyTableWin_H__
#define __KeyTableWin_H__

#include <windows.h>

namespace Input
{
	static const unsigned char KEY_UP = VK_UP;
	static const unsigned char KEY_DOWN = VK_DOWN;
	static const unsigned char KEY_LEFT = VK_LEFT;
	static const unsigned char KEY_RIGHT = VK_RIGHT;
	static const unsigned char KEY_SPACE = VK_SPACE;

	// 指定パッド
	typedef enum
	{
		PAD_KEY_UP = 0,
		PAD_KEY_DOWN,
		PAD_KEY_LEFT,
		PAD_KEY_RIGHT,

		// ボタン
		PAD_KEY_BTN,
		PAD_KEY_BTN_MAX = PAD_KEY_BTN + 32,

		PAD_KEY_MAX,
	} ePadKey;
}


#endif // __KeyTableWin_H__

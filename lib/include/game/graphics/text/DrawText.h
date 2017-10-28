/**
 *	@file 	D:/ProgramStady/Game/Lib/Sys/src/app/test/drawText.h
 *	@brief
 *	@author	yuto uchida
 *	@data   2010-01-19
 *	@note
 *
 */
#ifndef __drawText_H__
#define __drawText_H__

namespace __GRAPHICS__ {
	class Sprite;
}
// テキスト表示スクリーン
class drawText {

public:

	// インスタンス取得
	static drawText *inst();

	// 描画する文字列指定
	void draw(const char *pStr, float x, float y);
	// 描画する文字列指定(原点は文字列中心)
	void drawCenter(const char *pStr, float x, float y);

	// １文字のサイズ取得
	unsigned int width();
	unsigned int height();

	// 色 設定/取得
	void setColor(unsigned int rgb);
	unsigned int getColor();

	// フォントの影設定
	void setShadow( bool flg ) { mb_Shadow = flg; }

private:

	static const unsigned int mc_CharSizeW = 16;
	static const unsigned int mc_CharSizeH = 16;
	static const unsigned int mc_PutCharMax = 32;

	__GRAPHICS__::Sprite *mp_Sprite;

	bool	mb_Shadow;

	drawText();
	~drawText();

	// 文字列の縦横のサイズ取得
	void getargTextSize( const char *pStr, int &w, int &h );
	// 横の文字数
	unsigned getTextWidthLength( const char *pStr );
	// 縦の文字数
	unsigned getTextHeightLength( const char *pStr );

};

#endif // __drawText_H__

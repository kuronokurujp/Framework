/**
 *	@file 	D:/ProgramStady/Game/Lib/Sys/src/app/test/drawText.cpp
 *	@brief
 *	@author	yuto uchida
 *	@data   2010-01-19
 *	@note
 *
 */
#include "drawText.h"

#include "./../../modules/Graphics/Sprite.h"
#include "./../../common/Common.h"

drawText *drawText::inst() {
	static drawText inst;
	return &inst;
}

drawText::drawText() :
mp_Sprite(NULL) {

	mp_Sprite = new __GRAPHICS__::Sprite("./../data/Text.bmp", 0xff00ff00);
	ASSERT(mp_Sprite);
}
drawText::~drawText() {
	SAFE_DELETE(mp_Sprite);
}

// １文字のサイズ取得
unsigned int drawText::width() {
	return mc_CharSizeW;
}
unsigned int drawText::height() {
	return mc_CharSizeH;
}

// 色 設定/取得
void drawText::setColor(unsigned int rgb) {
	mp_Sprite->setAddRGB(rgb);
}
unsigned int drawText::getColor() {
	return mp_Sprite->getAddRGB();
}

// 文字列画面表示
void drawText::draw(const char *pStr, float x, float y) {

	ASSERT(pStr);

	int count = static_cast<unsigned int>(strlen(pStr));
	if( count <= 0 ) {
		return;
	}

	// アスキー文字のみ出力可能
	char chr = 0;
	unsigned int imgX, imgY;
	unsigned int max = 0;
	for( max=0; pStr[max] != NULL; max++ ) {}
	// 初期座標を算出

	__GRAPHICS__::Sprite *ps = mp_Sprite;
	float fh_size = static_cast<float>(height());
	float fw_size = static_cast<float>(width());
	float fx = static_cast<float>(x);
	float fy = static_cast<float>(y);
	float x_tmp = fx;
	float y_tmp = fy;
	for( unsigned int i=0; i<max; i++ ) {
		// 値チェック
		chr = pStr[i];
		if( '\n' == chr ) {
			y_tmp += fh_size;
			x_tmp = fx;
			continue;
		}
		// 制御文字などがないか調べる
		if( 32 > chr || chr >= 128 ) {
			chr = 127;
		}
		chr -= 32;
		imgX = (chr % 16) * mc_CharSizeW;
		imgY = (chr >> 4) * mc_CharSizeH;

		ps->setImgRect(imgX, imgY, imgX + mc_CharSizeW, imgY + mc_CharSizeH);
		ps->setLeftPos(x_tmp, y_tmp);
		ps->draw();

		x_tmp += fw_size;
	}
}

// 文字列画面表示
void drawText::drawCenter(const char *pStr, float x, float y) {

	unsigned w_length = getTextWidthLength( pStr );
	unsigned h_length = getTextHeightLength( pStr );

	// 描画座標は画像中心座標となっている。
	x = x - ( (w_length - 1) * (width() >> 1)	);
	y = y - ( (h_length - 1) * (height() >> 1 ) );

	x -= (width() >> 1);
	y -= (height() >> 1);

	draw( pStr, x, y );
}

// 文字列の縦横のサイズ取得
void drawText::getargTextSize( const char *pStr, int &w, int &h )
{
	ASSERT(pStr);

	unsigned w_length = getTextWidthLength( pStr );
	unsigned h_length = getTextHeightLength( pStr );

	w = width() * w_length;
	h = height() * h_length;
}

// 横の文字数
unsigned drawText::getTextWidthLength( const char *pStr ) {
	unsigned int max = 0;
	for( max=0; pStr[max] != NULL; max++ ) {}

	return max;
}
// 縦の文字数
unsigned drawText::getTextHeightLength( const char *pStr ) {
	unsigned int max = 1;
	for( int i=0; pStr[i] != NULL; i++ ) {
		if( pStr[i] == '\n' ) { max++; }
	}
	return max;
}

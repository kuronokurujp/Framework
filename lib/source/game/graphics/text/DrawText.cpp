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

// �P�����̃T�C�Y�擾
unsigned int drawText::width() {
	return mc_CharSizeW;
}
unsigned int drawText::height() {
	return mc_CharSizeH;
}

// �F �ݒ�/�擾
void drawText::setColor(unsigned int rgb) {
	mp_Sprite->setAddRGB(rgb);
}
unsigned int drawText::getColor() {
	return mp_Sprite->getAddRGB();
}

// �������ʕ\��
void drawText::draw(const char *pStr, float x, float y) {

	ASSERT(pStr);

	int count = static_cast<unsigned int>(strlen(pStr));
	if( count <= 0 ) {
		return;
	}

	// �A�X�L�[�����̂ݏo�͉\
	char chr = 0;
	unsigned int imgX, imgY;
	unsigned int max = 0;
	for( max=0; pStr[max] != NULL; max++ ) {}
	// �������W���Z�o

	__GRAPHICS__::Sprite *ps = mp_Sprite;
	float fh_size = static_cast<float>(height());
	float fw_size = static_cast<float>(width());
	float fx = static_cast<float>(x);
	float fy = static_cast<float>(y);
	float x_tmp = fx;
	float y_tmp = fy;
	for( unsigned int i=0; i<max; i++ ) {
		// �l�`�F�b�N
		chr = pStr[i];
		if( '\n' == chr ) {
			y_tmp += fh_size;
			x_tmp = fx;
			continue;
		}
		// ���䕶���Ȃǂ��Ȃ������ׂ�
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

// �������ʕ\��
void drawText::drawCenter(const char *pStr, float x, float y) {

	unsigned w_length = getTextWidthLength( pStr );
	unsigned h_length = getTextHeightLength( pStr );

	// �`����W�͉摜���S���W�ƂȂ��Ă���B
	x = x - ( (w_length - 1) * (width() >> 1)	);
	y = y - ( (h_length - 1) * (height() >> 1 ) );

	x -= (width() >> 1);
	y -= (height() >> 1);

	draw( pStr, x, y );
}

// ������̏c���̃T�C�Y�擾
void drawText::getargTextSize( const char *pStr, int &w, int &h )
{
	ASSERT(pStr);

	unsigned w_length = getTextWidthLength( pStr );
	unsigned h_length = getTextHeightLength( pStr );

	w = width() * w_length;
	h = height() * h_length;
}

// ���̕�����
unsigned drawText::getTextWidthLength( const char *pStr ) {
	unsigned int max = 0;
	for( max=0; pStr[max] != NULL; max++ ) {}

	return max;
}
// �c�̕�����
unsigned drawText::getTextHeightLength( const char *pStr ) {
	unsigned int max = 1;
	for( int i=0; pStr[i] != NULL; i++ ) {
		if( pStr[i] == '\n' ) { max++; }
	}
	return max;
}

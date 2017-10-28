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
// �e�L�X�g�\���X�N���[��
class drawText {

public:

	// �C���X�^���X�擾
	static drawText *inst();

	// �`�悷�镶����w��
	void draw(const char *pStr, float x, float y);
	// �`�悷�镶����w��(���_�͕����񒆐S)
	void drawCenter(const char *pStr, float x, float y);

	// �P�����̃T�C�Y�擾
	unsigned int width();
	unsigned int height();

	// �F �ݒ�/�擾
	void setColor(unsigned int rgb);
	unsigned int getColor();

	// �t�H���g�̉e�ݒ�
	void setShadow( bool flg ) { mb_Shadow = flg; }

private:

	static const unsigned int mc_CharSizeW = 16;
	static const unsigned int mc_CharSizeH = 16;
	static const unsigned int mc_PutCharMax = 32;

	__GRAPHICS__::Sprite *mp_Sprite;

	bool	mb_Shadow;

	drawText();
	~drawText();

	// ������̏c���̃T�C�Y�擾
	void getargTextSize( const char *pStr, int &w, int &h );
	// ���̕�����
	unsigned getTextWidthLength( const char *pStr );
	// �c�̕�����
	unsigned getTextHeightLength( const char *pStr );

};

#endif // __drawText_H__

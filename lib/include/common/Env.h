/**
 *	@file 	Env.h
 *	@brief	���m���Ŏg�p����}�N��/�֐��̈ꎮ
 *	@author	yuto uchida
 *	@data   2010-01-30
 *	@note 	�����Ŏg�p������̂�C/C++�����Ŏg�p�\�Ȃ̂�z�肵�Ă���
 *			������C++�����g���Ȃ������͂����ȁ[�[
 *
 */
#ifndef __COMMONENV_H__
#define __COMMONENV_H__

#define NUM_TO_ABS(_x_) ( ((_x_) < 0) ? (-(_x_)) : (_x_) )
// �z��̌��擾
// (�������擾�̔z��͕s�\)
// �֐��`���}�N���� #define XXX() ()�Ƃ���

// �z��̌��擾
#define ARRAY_NUM(_tbl_) (sizeof((_tbl_)) / sizeof((_tbl_[0])))
// �z��̑S�f�[�^�T�C�Y�擾
#define ARRAY_SIZE(_tbl_) (ARRAY_NUM((_tbl_)) * (sizeof((_tbl_[0]))))

// �P�����̔z����Q�����Ƃ��ĉ��肵���Ƃ���idx�擾
#define VRAM_IDX(_x_, _y_, _w_) ((_y_) * (_w_) + (_x_))
// �P�����̔z����Q�����Ƃ��ĉ��肵���Ƃ��̃f�[�^�擾
#define VRAM_ARRAY(_p_, _x_, _y_, _w_) ((_p_[VRAM_IDX((_x_), (_y_), (_w_))]))

// ���g�p�̌x���폜
#define UNUSE(_x_) ((void)(_x_))

// �l=�r�b�g���ɕϊ�
#define BIT(_x_) (1 << _x_)

// �w�肵�������Ə���̒l�𐧌�
// ����l�̐���
#define UPPER( __src__, __max__) ((__src__) > (__max__) ? (__max__) : (__src__))
// �����l�̐���
#define LOWER( __src__, __min__) ((__src__) < (__min__) ? (__min__) : (__src__))

// �w�肵������̒l���[�v
#define LOOPER( __src__, __min__, __max__ ) \
  ((__src__) > (__max__) ? (__min__) : ((__src__) < (__min__) ? (__max__) : (__src__)))

// �w�肵���l�𒴂��Ȃ�
#define CLAMP( __src__, __min__, __max__ ) \
  ((__src__) > (__max__) ? (__max__) : ((__src__) < (__min__) ? (__min__) : (__src__)))


#endif // __COMMONENV_H__

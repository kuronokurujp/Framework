/**
 *	@file 	Env.h
 *	@brief	高確率で使用するマクロ/関数の一式
 *	@author	yuto uchida
 *	@data   2010-01-30
 *	@note 	ここで使用するものはC/C++両方で使用可能なのを想定している
 *			だからC++しか使えない処理はいれるなーー
 *
 */
#ifndef __COMMONENV_H__
#define __COMMONENV_H__

#define NUM_TO_ABS(_x_) ( ((_x_) < 0) ? (-(_x_)) : (_x_) )
// 配列の個数取得
// (メモリ取得の配列は不可能)
// 関数形式マクロは #define XXX() ()とする

// 配列の個数取得
#define ARRAY_NUM(_tbl_) (sizeof((_tbl_)) / sizeof((_tbl_[0])))
// 配列の全データサイズ取得
#define ARRAY_SIZE(_tbl_) (ARRAY_NUM((_tbl_)) * (sizeof((_tbl_[0]))))

// １次元の配列を２次元として仮定したときのidx取得
#define VRAM_IDX(_x_, _y_, _w_) ((_y_) * (_w_) + (_x_))
// １次元の配列を２次元として仮定したときのデータ取得
#define VRAM_ARRAY(_p_, _x_, _y_, _w_) ((_p_[VRAM_IDX((_x_), (_y_), (_w_))]))

// 未使用の警告削除
#define UNUSE(_x_) ((void)(_x_))

// 値=ビット数に変換
#define BIT(_x_) (1 << _x_)

// 指定した下限と上限の値を制御
// 上限値の制御
#define UPPER( __src__, __max__) ((__src__) > (__max__) ? (__max__) : (__src__))
// 下限値の制御
#define LOWER( __src__, __min__) ((__src__) < (__min__) ? (__min__) : (__src__))

// 指定した上限の値ループ
#define LOOPER( __src__, __min__, __max__ ) \
  ((__src__) > (__max__) ? (__min__) : ((__src__) < (__min__) ? (__max__) : (__src__)))

// 指定した値を超えない
#define CLAMP( __src__, __min__, __max__ ) \
  ((__src__) > (__max__) ? (__max__) : ((__src__) < (__min__) ? (__min__) : (__src__)))


#endif // __COMMONENV_H__

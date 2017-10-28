/**
 *	@file 	D:/work/dungeon/framework/game/GameSystem.h
 *	@brief	ゲームシステム郡
 *	@author	yuto uchida
 *	@data   2010-11-30
 *	@note 	ゲーム作成に必要なシステムクラス
 *			起動/更新/描画処理とゲーム設定もできる
 *
 */
#ifndef __GAMESYSTEM_H__
#define __GAMESYSTEM_H__

#include "directx/input/KeyTable.h"
#include "directx/Manager.h"

#include "common/Common.h"
#include "graphics/Camera.h"

namespace GameLib
{
	class GameSystem
	{
	public:
		class GameConfig;

		/*
			ユーザ定義メソッド
			すごく重要で必ず使う側で実装しないといけない。

			処理順序は関数順に呼ばれる。
		*/
		/*
			@brief	ゲーム設定
		*/
		void	Config(GameConfig* in_pData);

		/*
		@brief	初期化
		@note
		※重要
		ゲーム起動時の初期化処理を書く
		フレームワークプロジェクトで実際しない。
		使用するプロジェクト側で中身の処理を作る。
		*/
		void	Start();

		/*
		@brief	更新
		@note	ゲーム更新
		*/
		bool	Update();

		/*
		@brief	終了
		@note	ゲーム終了時に呼ばれる
		*/
		void	Final();


		/*
			@brief	インスタンス取得
		*/
		static GameSystem&	Inst();

		/*
			@brief	3Dアクティブカメラ取得
		*/
		Camera&	GetActiveCam();

		/*
			@brief	スクリーンサイズを返す	
		*/
		const unsigned GetScreenWidth() const;
		const unsigned GetScreenHeight() const;

		/*
			@breif	ボタン入力
			@param	i_key	:	指定したボタンが押されたか
		*/
		bool	IsButtonOn( unsigned char i_key );
		bool	IsButtonTriggerOn( unsigned char i_key );
		bool	IsButtonRepertOn( unsigned char i_key );
		/*
			@breif	ゲームパッド入力
			@param	i_pad	:	指定したボタンが押されたか
		*/
		bool IsPadOn( Input::ePadKey i_pad );
		bool IsPadTriggerOn( Input::ePadKey i_pad );
		bool IsPadRepertOn( Input::ePadKey i_pad );

		//	背景色設定・取得
		void SetScreenColor( const unsigned in_rgb );
		const unsigned	GetScreenColor()	const;

		//	点を描画
		void	DrawPoint( const Vec2& in_Pos );

		/*
			@breif	デバッグテキスト描画
			@param	ip_str	:	テキスト
			@param	i_x		:	x座標
			@param	i_y		:	y座標
			@param	i_color	:	テキストカラー(ARGB)
		*/
		void DrawDebugText( const char* ip_str, int i_x, int i_y, const int i_color = 0xffffffff );

		//	定義
		/*
			@brief	ゲーム設定
		*/
		class GameConfig
		{
		public:
			//	コンストラクタ
			GameConfig()	{ _Clear(); }
			~GameConfig()	{}

			//	定義
			typedef enum
			{
				SIZE_640_480	= 0,
				SIZE_NUM,
			} SCREEN_SIZE_ENUM;

			//	関数
			void	_Clear();

			const unsigned	GetScreenSizeX() const;
			const unsigned	GetScreenSizeY() const;

			//	変数
			SCREEN_SIZE_ENUM	m_ScreenSizeType;
			char				m_AppName[ 256 ];
		};

		/*
			@brief	コンフィグ取得
		*/
		const GameConfig&	GetConfig() const;


	private:
		GameSystem();
		~GameSystem()	{}

		Camera*	mp_Cam;
	};

} // namespace GameLib
#endif // __GAMESYSTEM_H__

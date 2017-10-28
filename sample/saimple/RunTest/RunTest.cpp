#include "stdafx.h"

#include "game/GameSystem.h"

#include "common/Common.h"

namespace GameLib {

	/*
		@brief	コンフィグ
	*/
	void GameSystem::Config(GameConfig* in_pData)
	{
	}

	/*
		@brief	ゲーム開始時に呼ばれる。
	*/
	void GameSystem::Start()
	{

	}

	/*
		@brief	更新
	*/
	bool GameSystem::Update()
	{
		return true;
	}

	/*
		@brief	ゲーム終了時に呼ばれる。
	*/
	void GameSystem::Final()
	{
	}
}

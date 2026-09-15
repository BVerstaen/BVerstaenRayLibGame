#pragma once

#include "raylib.h"
#include "resource_dir.h"

#include <Core/ScoreSystem.h>
#include <Core/GameFont.h>
#include <Core/Random.h>

#include <Game/Background.h>
#include <Game/Player/Player.h>
#include <Game/Target/TargetManager.h>
#include <Game/Player/PlayerProjectile.h>
#include <Game/ScoreUI.h>
#include <Game/Hazard/HazardManager.h>

#include <GameOver/GameOverManager.h>

class Application
{
private:
	enum class GameState
	{
		TITLE,
		GAME,
		GAMEOVER
	};

public:
	void Run();

#pragma region Tick

private:
	void LogicTick(float deltaTime);
	void RenderTick(float deltaTime);

#pragma endregion

#pragma region Change state

private:
	void BeginState(GameState newGameState);
	void EndState(GameState oldGameState);
	void SwitchGameState(GameState newGameState);

#pragma endregion


private:
	GameState m_currentGameState;
	
	//Game Systems
	Random m_rand;
	GameFont m_font;
	ScoreSystem m_scoreSys;
	Background m_background;
	Player m_player;
	PlayerProjectile m_playerProj;
	TargetManager m_targetManager;
	HazardManager m_hazardManager;
	ScoreUI m_scoreUI;

	GameOverManager m_gameOverManager;


private:
	Camera2D camera;

};
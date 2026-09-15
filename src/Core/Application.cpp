#include "Application.h"

void Application::Run()
{
	m_currentGameState = GameState::GAME;

	m_scoreSys.ResetScore();
	m_player.Setup(&m_background);

	//Game loop
	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		LogicTick(deltaTime);
		RenderTick(deltaTime);
	}	
}

void Application::LogicTick(float deltaTime)
{
	//LOGIC UPDATE
	switch (m_currentGameState)
	{
	case GameState::TITLE:
		break;

	case GameState::GAME:
	{
		m_background.UpdateLogic(deltaTime);

		m_player.UpdateLogic(deltaTime);
		if (m_player.IsFiring())
			m_playerProj.SpawnProjectile(m_player.GetPosition());
		m_playerProj.UpdateLogic(deltaTime);

		m_targetManager.UpdateLogic(deltaTime, m_background.GetSpeed(), m_background.GetGroundLayerSpeed());
		m_targetManager.UpdateCollisions(m_scoreSys, m_playerProj.GetProjectilePositions(), m_playerProj.GetProjectileSize());
		m_hazardManager.UpdateLogic(deltaTime, m_background.GetSpeed(), m_background.GetGroundLayerSpeed());

		m_scoreSys.UpdateScore(deltaTime, m_background.GetSpeed());

		if (m_player.CheckGroundCollision() || m_hazardManager.UpdateCollisions(m_player.GetRectangle()))
			SwitchGameState(GameState::GAMEOVER);
		break;
	}

	case GameState::GAMEOVER:
		if (m_gameOverManager.UpdateLogic(deltaTime))
			SwitchGameState(GameState::GAME);
		break;

	default:
		TraceLog(LOG_ERROR, "Unknown game state");
		break;
	}
}

void Application::RenderTick(float deltaTime)
{
	//RENDER UPDATE
	BeginDrawing();
	ClearBackground(BLACK);

	switch (m_currentGameState)
	{
	case GameState::TITLE:
		break;

	case GameState::GAME:
	{
		m_background.UpdateRender();
		m_targetManager.UpdateRender();
		m_player.UpdateRender(deltaTime);
		m_playerProj.UpdateRender();
		m_hazardManager.UpdateRender();

		m_scoreUI.DrawScore(deltaTime, m_scoreSys.CurrentScore);
		break;
	}

	case GameState::GAMEOVER:
	{
		m_background.UpdateRender();
		m_targetManager.UpdateRender();
		m_player.RenderDeath();
		m_playerProj.UpdateRender();
		m_hazardManager.UpdateRender();

		m_gameOverManager.UpdateRender(m_scoreSys.CurrentScore);
		break;
	}

	default:
		TraceLog(LOG_ERROR, "Unknown game state");
		break;
	}

	EndDrawing();
}

void Application::BeginState(GameState newGameState)
{
	switch (m_currentGameState)
	{
	case GameState::TITLE:
		break;
	case GameState::GAME:
		break;
	case GameState::GAMEOVER:
		m_scoreSys.AddScoreToHighScore();
		break;
	default:
		TraceLog(LOG_ERROR, "Unknown game state");
		break;
	}
}

void Application::EndState(GameState oldGameState)
{
	switch (m_currentGameState)
	{
	case GameState::TITLE:
		break;
	case GameState::GAME:
		break;
	case GameState::GAMEOVER:
		break;
	default:
		TraceLog(LOG_ERROR, "Unknown game state");
		break;
	}
}

void Application::SwitchGameState(GameState newGameState)
{
	EndState(m_currentGameState);
	BeginState(newGameState);
	m_currentGameState = newGameState;
}


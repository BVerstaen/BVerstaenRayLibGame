#include "Application.h"

void Application::Run()
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	m_currentGameState = GameState::GAME;

	m_scoreSys.ResetScore();
	m_player.Setup(&m_background);

	camera = { 0 };
	camera.target = Vector2(0, 0);
	camera.offset = Vector2(0, 0);//Vector2(screenWidth / 2.0f, screenHeight / 2.0f);
	camera.rotation = 0.0f;
	camera.zoom = 1.5f;

	//Game loop
	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		LogicTick(deltaTime);
		RenderTick(deltaTime);
	}
}

#pragma region Tick

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
	ClearBackground(RED);

	switch (m_currentGameState)
	{
	case GameState::TITLE:
		break;

	case GameState::GAME:
	{
		BeginMode2D(camera);
		
		m_background.UpdateRender();
		m_targetManager.UpdateRender();
		m_player.UpdateRender(deltaTime);
		m_playerProj.UpdateRender();
		m_hazardManager.UpdateRender();
		
		EndMode2D();

		m_scoreUI.DrawScore(deltaTime, m_scoreSys.CurrentScore);
		break;
	}

	case GameState::GAMEOVER:
	{
		BeginMode2D(camera);

		m_background.UpdateRender();
		m_targetManager.UpdateRender();
		m_player.RenderDeath();
		m_playerProj.UpdateRender();
		m_hazardManager.UpdateRender();

		EndMode2D();

		m_gameOverManager.UpdateRender(m_scoreSys.CurrentScore, m_hasReachHighScore);
		break;
	}

	default:
		TraceLog(LOG_ERROR, "Unknown game state");
		break;
	}

	EndDrawing();
}

#pragma endregion


#pragma region Change state

void Application::BeginState(GameState newGameState)
{
	switch (newGameState)
	{
	case GameState::TITLE:
		break;

	case GameState::GAME:
		m_hasReachHighScore = false;
		m_scoreSys.ResetScore();
		m_player.Reset();
		m_playerProj.Reset();
		m_hazardManager.Reset();
		m_targetManager.Reset();
		break;

	case GameState::GAMEOVER:
		m_hasReachHighScore = m_scoreSys.AddScoreToHighScore();
		break;

	default:
		TraceLog(LOG_ERROR, "Unknown game state");
		break;
	}
}

void Application::EndState(GameState oldGameState)
{
	switch (oldGameState)
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

#pragma endregion
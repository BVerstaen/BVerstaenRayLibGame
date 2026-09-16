#include "Application.h"

void Application::Run()
{
	//Setup systems
	m_scoreSys.ResetScore();
	m_player.Setup(&m_background);
	m_playerProj.Setup(&m_player);

	//Launch first state
	m_currentGameState = GameState::TITLE;
	BeginState(m_currentGameState);

	//Game loop
	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		m_audio.UpdateMusic();

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
	case GameState::INSTRUCTION:
	{
		m_background.UpdateLogic(deltaTime);
		m_titleScreen.UpdateLogic(deltaTime);
		if (InputManager::Instance().IsAnyKeyPressed())
			SwitchGameState(m_currentGameState == GameState::INSTRUCTION ? GameState::GAME : GameState::INSTRUCTION);
		break;
	}

	case GameState::GAME:
	{
		InputManager::Instance().UpdateInputs();

		m_background.UpdateLogic(deltaTime);
		m_camera.UpdateLogic(deltaTime);
		
		m_player.UpdateLogic(deltaTime);
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
	{
		if (m_gameOverManager.UpdateLogic(deltaTime) && InputManager::Instance().IsAnyKeyPressed())
			SwitchGameState(GameState::TITLE);
		break;
	}

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
	{
		BeginMode2D(m_camera.GetCamera());

		m_background.UpdateRender();

		EndMode2D();

		m_titleScreen.UpdateRender(m_scoreSys.HighScoreList);
		break;
	}

	case GameState::INSTRUCTION:
	{
		BeginMode2D(m_camera.GetCamera());

		m_background.UpdateRender();

		EndMode2D();

		m_titleScreen.UpdateInstruction();
		break;
	}

	case GameState::GAME:
	{
		BeginMode2D(m_camera.GetCamera());
		m_camera.BeginScissor(m_player.GetRectangle());

		m_background.UpdateRender();
		m_targetManager.UpdateRender();
		m_player.UpdateRender(deltaTime);

		m_playerProj.UpdateRender();
		m_hazardManager.UpdateRender();

		m_camera.EndScissor();
		EndMode2D();

		m_scoreUI.DrawScore(deltaTime, m_scoreSys.CurrentScore);
		break;
	}

	case GameState::GAMEOVER:
	{
		BeginMode2D(m_camera.GetCamera());

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
	{
		m_background.SetSpeed(500);

		m_audio.PlayMusicFromList(AudioManager::MusicList::TITLE);
		break;
	}

	case GameState::INSTRUCTION:
		break;

	case GameState::GAME:
	{
		m_hasReachHighScore = false;

		m_camera.Reset();
		m_background.ResetSpeed();
		m_scoreSys.ResetScore();
		m_player.Reset();
		m_playerProj.Reset();
		m_hazardManager.Reset();
		m_targetManager.Reset();

		m_audio.PlayMusicFromList(AudioManager::MusicList::GAME);
		break;
	}

	case GameState::GAMEOVER:
	{
		AudioManager::Instance().PlaySoundFromList(AudioManager::SoundList::PLAYERDEATH);
		m_hasReachHighScore = m_scoreSys.AddScoreToHighScore();
		m_gameOverManager.Reset();

		m_audio.PlayMusicFromList(AudioManager::MusicList::GAMEOVER);
		break;
	}

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
	case GameState::GAMEOVER:
	case GameState::INSTRUCTION:
		m_audio.StopCurrentMusic();
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
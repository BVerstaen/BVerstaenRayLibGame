#include "GameOverManager.h"

#pragma region Game over text data

GameOverManager::GameOverText::GameOverText()
{
}

GameOverManager::GameOverText::GameOverText(std::string text, Vector2 pos, float delay, Color col)
{
}

#pragma endregion




GameOverManager::GameOverManager():m_counter(0), m_gameOverText("GAME OVER"), m_finalTextText("Final score: "), m_pressAnyKeyText("Press any key"), m_gameOverTextDelay(0.0f), m_finalTextDelay(2.0f), m_pressAnyKeyTextDelay(5.0f)
{
}

void GameOverManager::UpdateLogic(float deltaTime)
{
	m_counter += deltaTime;
}

void GameOverManager::UpdateRender(float deltaTime)
{
	if (m_counter >= m_gameOverTextDelay)
	{

	}
	if (m_counter >= m_finalTextDelay)
	{

	}
	if (m_counter >= m_pressAnyKeyTextDelay)
	{

	}
}
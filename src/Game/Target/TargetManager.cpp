#include "TargetManager.h"
#include <string>

TargetManager::TargetManager():m_spawnDelayRange(Vector2(3.0f,5.0f)), m_spawnPosition(Vector2(928,302))
{
	m_spawnDelay = GetRandomValue(m_spawnDelayRange.x, m_spawnDelayRange.y);

	//Add textures
	const int targetNumber = 3;
	for (int i = 0; i < targetNumber; i++)
	{
		std::string texPath = "Sprites\\Hazards\\GroundTarget_" + std::to_string(i) + ".png";
		if (!FileExists(texPath.c_str()))
		{
			TraceLog(LOG_ERROR, "File [%s] is invalid", texPath.c_str());
			continue;
		}

		m_targetTextures.push_back(LoadTexture(texPath.c_str()));
	}
}

TargetManager::~TargetManager()
{
	for (Texture& texture : m_targetTextures)
	{
		UnloadTexture(texture);
	}
}

void TargetManager::UpdateLogic(float deltaTime, float groundSpeed)
{
	//Delay logic
	m_spawnDelay -= deltaTime;
	if (m_spawnDelay <= 0)
	{
		m_spawnDelay = GetRandomValue(m_spawnDelayRange.x, m_spawnDelayRange.y);

		//Spawn new target
		m_targetList.push_back(Target(m_targetTextures[GetRandomValue(0, m_targetTextures.size())], m_spawnPosition));
	}

	//TargetLogic
	auto targetListIT = m_targetList.begin();
	while (targetListIT != m_targetList.end())
	{
		if (targetListIT->UpdateLogic(deltaTime, groundSpeed))
			targetListIT = m_targetList.erase(targetListIT);
	}
}

void TargetManager::UpdateRender(float deltaTime)
{
	for (Target target : m_targetList)
	{
		target.UpdateRender(deltaTime);
	}
}

#include "TargetManager.h"
#include <string>
#include <random>

TargetManager::TargetManager():m_spawnDelayRange(Vector2(.25f,0.5f)), m_spawnPosition(Vector2(928,474))
{
	m_spawnDelay = GetRandomDelay();

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

const float TargetManager::GetRandomDelay() const
{
	//TODO -> Use proper Random class
	std::mt19937 mt = std::mt19937();
	std::uniform_real_distribution<> dis(m_spawnDelayRange.x, m_spawnDelayRange.y);
	return dis(mt);
}

void TargetManager::UpdateLogic(float deltaTime, float groundSpeed)
{
	//Delay logic
	m_spawnDelay -= deltaTime;
	TraceLog(LOG_INFO, "[%f]", m_spawnDelay);

	if (m_spawnDelay <= 0)
	{
		m_spawnDelay = GetRandomDelay();

		//Spawn new target
		m_targetList.push_back(Target(m_targetTextures[GetRandomValue(0, m_targetTextures.size() - 1)], m_spawnPosition));
	}

	//TargetLogic
	auto targetListIT = m_targetList.begin();
	while (targetListIT != m_targetList.end())
	{
		if (targetListIT->UpdateLogic(deltaTime, groundSpeed))
			targetListIT = m_targetList.erase(targetListIT);
		else
			targetListIT++;
	}
}

void TargetManager::UpdateRender(float deltaTime)
{
	for (Target target : m_targetList)
	{
		target.UpdateRender(deltaTime);
	}
}

#include "HazardManager.h"
#include <random>

HazardManager::HazardManager() :m_spawnDelayRange(Vector2(1.0f, 3.0f)), m_spawnPosition(Vector2(928, 474))
{
	m_spawnDelay = Random::Instance().RandomRange(m_spawnDelayRange.x, m_spawnDelayRange.y);

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

		m_hazardTextures.push_back(LoadTexture(texPath.c_str()));
	}
}

HazardManager::~HazardManager()
{
	for (Texture& texture : m_hazardTextures)
	{
		UnloadTexture(texture);
	}
}


void HazardManager::UpdateLogic(float deltaTime, float backgroundSpeed, float groundSpeed)
{
}

void HazardManager::UpdateRender(float deltaTime)
{
}

void HazardManager::UpdateCollisions(ScoreSystem& score, const Rectangle& playerRectangle)
{
}
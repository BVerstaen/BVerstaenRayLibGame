#include "HazardManager.h"

HazardManager::HazardManager() :m_spawnDelayRange(Vector2(1.0f, 3.0f)), m_spawnPosition(Vector2(928, 474)), m_pointsForHit(50)
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
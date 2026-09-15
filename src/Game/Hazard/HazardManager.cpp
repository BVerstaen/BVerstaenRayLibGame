#include "HazardManager.h"
#include <Core/Random.h>
#include <random>

#pragma region Constructors / Desctructors / Movement

HazardManager::HazardManager() :m_spawnPositionYRange(Vector2(100, 350)), m_spawnDelayRange(Vector2(1.0f, 3.0f)), m_baseRotationRange(Vector2(0.0f,359.0f)), m_baseSpeedRange(Vector2(1.0f, 5.0f))
{
	m_spawnDelay = Random::Instance().RandomRange(m_spawnDelayRange.x, m_spawnDelayRange.y);

	//Add textures
	const int AirHazardSprites = 2;
	for (int i = 0; i < AirHazardSprites; i++)
	{
		std::string texPath = "Sprites\\Hazards\\AirHazard_" + std::to_string(i) + ".png";
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

#pragma endregion


void HazardManager::UpdateLogic(float deltaTime, float backgroundSpeed, float groundSpeed)
{
	//Delay logic
	float speedMultiplier = (backgroundSpeed / 100.0f);
	m_spawnDelay -= deltaTime * speedMultiplier;

	if (m_spawnDelay <= 0)
	{
		Random& rand = Random::Instance();
		m_spawnDelay = rand.RandomRange(m_spawnDelayRange.x, m_spawnDelayRange.y);

		//Spawn new target
		Vector2 newSpawnPosition = Vector2(848, rand.RandomRange(m_spawnPositionYRange.x, m_spawnPositionYRange.y));
		float newRotation = rand.RandomRange(m_baseRotationRange.x, m_baseRotationRange.y);
		float newSpeed = rand.RandomRange(m_baseSpeedRange.x, m_baseSpeedRange.y);
		m_hazardList.push_back(Hazard(m_hazardTextures[GetRandomValue(0, m_hazardTextures.size() - 1)], newSpawnPosition, newRotation, newSpeed));
	}

	//Hazard logic (movement & destruction)
	auto It = m_hazardList.begin();
	while (It != m_hazardList.end())
	{
		if (It->UpdateLogic(deltaTime, groundSpeed))
			It = m_hazardList.erase(It);
		else
			It++;
	}
}

void HazardManager::UpdateRender()
{
	for (Hazard& hazard : m_hazardList)
	{
		hazard.UpdateRender();
	}
}

bool HazardManager::UpdateCollisions(const Rectangle& playerRectangle)
{
	const float minimumXPosition = playerRectangle.x + playerRectangle.width;

	//Cache rect because sizes are the same
	Rectangle currentHazardRect = Rectangle(0, 0, 48, 48);
	for (Hazard& hazard : m_hazardList)
	{
		const Vector2& hazardPos = hazard.GetPosition();
		//Don't check knife if hasn't reach player, cause can't be in range
		if (hazardPos.x > minimumXPosition)
			continue;

		//Setup rect & check collisions
		currentHazardRect.x = hazardPos.x;
		currentHazardRect.y = hazardPos.y;
		if (CheckCollisionRecs(playerRectangle, currentHazardRect))
			return true;
	}
	return false;
}
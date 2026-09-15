#include "TargetManager.h"
#include <string>
#include <random>

TargetManager::TargetManager():m_spawnDelayRange(Vector2(1.0f,3.0f)), m_spawnPosition(Vector2(928,474)), m_pointsForHit(50)
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

void TargetManager::UpdateLogic(float deltaTime, float backgroundSpeed, float groundSpeed)
{
	//Delay logic
	float speedMultiplier = (backgroundSpeed / 100.0f);
	m_spawnDelay -= deltaTime * speedMultiplier;

	if (m_spawnDelay <= 0)
	{
		m_spawnDelay = GetRandomDelay();

		//Spawn new target
		m_targetList.push_back(Target(m_targetTextures[GetRandomValue(0, m_targetTextures.size() - 1)], m_spawnPosition));
	}

	//Targe logic (movement & destruction)
	auto It = m_targetList.begin();
	while (It != m_targetList.end())
	{
		if (It->UpdateLogic(deltaTime, groundSpeed))
			It = m_targetList.erase(It);
		else
			It++;
	}
}

void TargetManager::UpdateRender(float deltaTime)
{
	for (Target target : m_targetList)
	{
		target.UpdateRender(deltaTime);
	}
}

void TargetManager::UpdateCollisions(ScoreSystem& score, const std::vector<Vector2>& projectileList, const Vector2& projectileSize)
{
	const float minimumYPos = m_spawnPosition.y;

	//Cache rect because sizes are the same
	Rectangle currentProjectileRect = Rectangle(0, 0, projectileSize.x, projectileSize.y);
	Rectangle currentTargetRect = Rectangle(0, 0, 64, 64);
	for (Vector2 projectilePos : projectileList)
	{
		//Don't check projectile still in the air, cause can't be in range
		if (projectilePos.y <= minimumYPos)
			continue;

		//Setup rect & check collisions
		currentProjectileRect.x = projectilePos.x;
		currentProjectileRect.y = projectilePos.y;

		auto It = m_targetList.begin();
		while (It != m_targetList.end())
		{
			currentTargetRect.x = It->GetPosition().x;
			currentTargetRect.y = It->GetPosition().y;

			if (CheckCollisionRecs(currentProjectileRect, currentTargetRect))
			{
				score.CurrentScore += m_pointsForHit;
				It = m_targetList.erase(It);
			}
			else
				It++;
		}
	}
}
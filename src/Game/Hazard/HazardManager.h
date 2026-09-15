#pragma once

#include <vector>
#include "raylib.h"
#include "Hazard.h"
#include <Core\ScoreSystem.h>


class HazardManager
{
public:
	HazardManager();
	~HazardManager();
	HazardManager(const HazardManager& hazardManager) = delete;
	HazardManager& operator=(const HazardManager& hazardManager) = delete;
	HazardManager(HazardManager&& hazardManager) noexcept = delete;
	HazardManager& operator=(HazardManager&& hazardManager) noexcept = delete;

private:
	const float GetRandomDelay() const;

public:
	void UpdateLogic(float deltaTime, float backgroundSpeed, float groundSpeed);
	void UpdateRender(float deltaTime);
	void UpdateCollisions(ScoreSystem& score, const Rectangle& playerRectangle);

private:
	std::vector<Hazard> m_hazardList;
	std::vector<Texture> m_hazardTextures;

	float m_spawnDelay;
	Vector2 m_spawnDelayRange;

	Vector2 m_spawnPosition;
	Vector2 m_baseRotationRange;
	Vector2 m_baseSpeedRange;
};
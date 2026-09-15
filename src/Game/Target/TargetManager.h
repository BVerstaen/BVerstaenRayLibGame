#pragma once

#include <vector>
#include "raylib.h"
#include "Target.h"
#include <Core\ScoreSystem.h>


class TargetManager
{
#pragma region Constructors / Desctructors / Movement

public:
	TargetManager();
	~TargetManager();
	TargetManager(const TargetManager& targetManager) = delete;
	TargetManager& operator=(const TargetManager& targetManager) = delete;
	TargetManager(TargetManager&& targetManager) noexcept = delete;
	TargetManager& operator=(TargetManager&& targetManager) noexcept = delete;

#pragma endregion 

public:
	void Reset();

	void UpdateLogic(float deltaTime, float backgroundSpeed, float groundSpeed);
	void UpdateRender();
	void UpdateCollisions(ScoreSystem& score, std::vector<Vector2>& projectileList, const Vector2& projectileSize);

private:
	std::vector<Target> m_targetList;
	std::vector<Texture> m_targetTextures;

	float m_spawnDelay;
	Vector2 m_spawnDelayRange;

	Vector2 m_spawnPosition;
	int m_pointsForHit;
};
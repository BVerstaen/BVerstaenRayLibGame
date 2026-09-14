#pragma once

#include <vector>
#include "raylib.h"
#include "Target.h"

class TargetManager
{
public:
	TargetManager();
	~TargetManager();
	TargetManager(const TargetManager& targetManager) = delete;
	TargetManager& operator=(const TargetManager& targetManager) = delete;
	TargetManager(TargetManager&& targetManager) noexcept = delete;
	TargetManager& operator=(TargetManager&& targetManager) noexcept = delete;

private:
	const float GetRandomDelay() const;

public:
	void UpdateLogic(float deltaTime, float backgroundSpeed, float groundSpeed);
	void UpdateRender(float deltaTime);
	void UpdateCollisions(const std::vector<Vector2>& projectileList, const Vector2& projectileSize);

private:
	std::vector<Target> m_targetList;
	std::vector<Texture> m_targetTextures;

	float m_spawnDelay;
	Vector2 m_spawnDelayRange;

	Vector2 m_spawnPosition;
};
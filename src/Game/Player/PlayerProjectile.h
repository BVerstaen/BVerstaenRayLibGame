#pragma once

#include "raylib.h"
#include <vector>

class PlayerProjectile
{
public:
	PlayerProjectile();
	~PlayerProjectile();
	PlayerProjectile(const PlayerProjectile& playerProjectile) = delete;
	PlayerProjectile& operator=(const PlayerProjectile& playerProjectile) = delete;
	PlayerProjectile(PlayerProjectile&& playerProjectile) noexcept = delete;
	PlayerProjectile& operator=(PlayerProjectile&& playerProjectile) noexcept = delete;

public:
	void SpawnProjectile(Vector2 playerPos);

	void UpdateLogic(float deltaTime);
	void UpdateRender(float deltaTime);

private:
	const float m_projectileSpeed;
	const int m_projectileLimit;
	Texture m_projectileTexture;
	Vector2 m_projectileDirection;

public:
	std::vector<Vector2> m_projectilePositions;
};
#pragma once

#include "raylib.h"
#include <vector>

class PlayerProjectile
{
#pragma region Constructors / Desctructors / Movement

public:
	PlayerProjectile();
	~PlayerProjectile();
	PlayerProjectile(const PlayerProjectile& playerProjectile) = delete;
	PlayerProjectile& operator=(const PlayerProjectile& playerProjectile) = delete;
	PlayerProjectile(PlayerProjectile&& playerProjectile) noexcept = delete;
	PlayerProjectile& operator=(PlayerProjectile&& playerProjectile) noexcept = delete;

#pragma endregion

public:
	void Reset();
	void SpawnProjectile(Vector2 playerPos);

	void UpdateLogic(float deltaTime);
	void UpdateRender();

public:
	const std::vector<Vector2>& GetProjectilePositions() const;
	const Vector2& GetProjectileSize() const;

private:
	const float m_projectileSpeed;
	const int m_projectileLimit;
	Texture m_projectileTexture;
	Vector2 m_projectileDirection;
	Vector2 m_projectileSize;

	const Vector2 m_spawnOffset;

private:
	std::vector<Vector2> m_projectilePositions;
};
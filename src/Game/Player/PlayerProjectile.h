#pragma once

#include "raylib.h"
#include "Player.h"
#include <Core/InputManager.h>
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
	void Setup(const Player* player);
	void Reset();

	void UpdateLogic(float deltaTime);
	void UpdateRender();

public:
	std::vector<Vector2>& GetProjectilePositions();
	const Vector2& GetProjectileSize() const;

private:
	const Player* m_player;
	const float m_projectileSpeed;
	const int m_projectileLimit;
	Texture m_projectileTexture;
	Vector2 m_projectileDirection;
	Vector2 m_projectileSize;

	const Vector2 m_spawnOffset;

private:
	std::vector<Vector2> m_projectilePositions;
};
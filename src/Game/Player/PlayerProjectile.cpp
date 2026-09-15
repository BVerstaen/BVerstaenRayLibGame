#include "PlayerProjectile.h"
#include "raymath.h"

PlayerProjectile::PlayerProjectile(): m_projectileLimit(5), m_projectileDirection(Vector2(0.5f,0.5f)), m_projectileSpeed(300.0f), m_spawnOffset(Vector2(140, 30))
{
	m_projectileTexture = LoadTexture("Sprites\\Player\\PlayerProjectile.png");
	m_projectileSize = Vector2(m_projectileTexture.width, m_projectileTexture.height);
}

PlayerProjectile::~PlayerProjectile()
{
	UnloadTexture(m_projectileTexture);
}

void PlayerProjectile::SpawnProjectile(Vector2 playerPos)
{
	if(m_projectilePositions.size() < m_projectileLimit)
		m_projectilePositions.push_back(Vector2Add(playerPos, m_spawnOffset));
}

void PlayerProjectile::UpdateLogic(float deltaTime)
{
	//Projectile logic
	Vector2 cachedVectorIncrement = Vector2Scale(m_projectileDirection, deltaTime * m_projectileSpeed);

	auto It = m_projectilePositions.begin();
	while (It != m_projectilePositions.end())
	{
		*It = Vector2Add(*It, cachedVectorIncrement);
		if (It->x >= 800 || It->y >= 600)
			It = m_projectilePositions.erase(It);
		else
			It++;
	}
}

void PlayerProjectile::UpdateRender(float deltaTime)
{
	for (Vector2 pos : m_projectilePositions)
	{
		DrawTextureV(m_projectileTexture, pos, WHITE);
	}
}

const std::vector<Vector2>& PlayerProjectile::GetProjectilePositions() const
{
	return m_projectilePositions;
}

const Vector2& PlayerProjectile::GetProjectileSize() const
{
	return m_projectileSize;
}

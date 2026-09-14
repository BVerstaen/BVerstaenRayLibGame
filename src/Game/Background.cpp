#include "Background.h"

Background::Background() : m_speed(1.0f), m_backgroundSpeedMultiplier(0.0f), m_foregroundSpeedMultiplier(0.5f), m_groundSpeedMultiplier(1.0f)
{
	m_backgroundLayerTexture = LoadTexture("Sprites\\Background_0.png");
	m_foregroundLayerTexture = LoadTexture("Sprites\\Background_1.png");
	m_groundLayerTexture = LoadTexture("Sprites\\Ground.png");

	m_backgroundPosition = Vector2(0,0);
	m_foregroundPosition = Vector2(0,0);
	m_groundPosition = Vector2(0,0);
}

Background::~Background()
{
	UnloadTexture(m_backgroundLayerTexture);
	UnloadTexture(m_foregroundLayerTexture);
	UnloadTexture(m_groundLayerTexture);
}

void Background::SetSpeed(float newSpeed)
{
	m_speed = newSpeed;
}

void Background::UpdateLogic(float deltaTime)
{
	m_backgroundPosition.x -= deltaTime * (m_speed * m_backgroundSpeedMultiplier);
	m_foregroundPosition.x -= deltaTime * (m_speed * m_foregroundSpeedMultiplier);
	m_groundPosition.x -= deltaTime * (m_speed * m_groundSpeedMultiplier);
}

void Background::UpdateRender(float deltaTime)
{
	DrawTexture(m_backgroundLayerTexture, m_backgroundPosition.x, m_backgroundPosition.y, WHITE);
	DrawTexture(m_foregroundLayerTexture, m_foregroundPosition.x, m_foregroundPosition.y, WHITE);
	DrawTexture(m_groundLayerTexture, m_groundPosition.x, m_groundPosition.y, WHITE);
}

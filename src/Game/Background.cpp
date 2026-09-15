#include "Background.h"
#include <cmath>
#include <iostream>


Background::BackgroundData::BackgroundData():BackgroundTexture(Texture()), Position(Vector2(0, 0)), SpeedMultiplier(0), TextureHalfWidth(0){}

Background::BackgroundData::BackgroundData(Texture tex, float baseSpeed)
{
	BackgroundTexture = tex;
	Position = Vector2(0, 600 - BackgroundTexture.height);
	SpeedMultiplier = baseSpeed;
	TextureHalfWidth = BackgroundTexture.width / 2;
}


Background::Background() : m_speed(100.0f)
{
	m_backgroundLayer = BackgroundData(LoadTexture("Sprites\\Background_0.png"), 0.0f);
	m_foregroundLayer = BackgroundData(LoadTexture("Sprites\\Background_1.png"), 1.0f);
	m_groundLayer = BackgroundData(LoadTexture("Sprites\\Ground.png"), 3.0f);
}

Background::~Background()
{
	UnloadTexture(m_backgroundLayer.BackgroundTexture);
	UnloadTexture(m_foregroundLayer.BackgroundTexture);
	UnloadTexture(m_groundLayer.BackgroundTexture);
}

const float Background::GetSpeed() const
{
	return m_speed;
}

const float Background::GetGroundLayerSpeed() const
{
	return m_speed * m_groundLayer.SpeedMultiplier;
}

void Background::SetSpeed(float newSpeed)
{
	m_speed = newSpeed;
}

void Background::UpdateLogic(float deltaTime)
{
	m_backgroundLayer.Position.x = std::fmod(m_backgroundLayer.Position.x - (deltaTime * (m_speed * m_backgroundLayer.SpeedMultiplier)), m_backgroundLayer.TextureHalfWidth);
	m_foregroundLayer.Position.x = std::fmod(m_foregroundLayer.Position.x - (deltaTime * (m_speed * m_foregroundLayer.SpeedMultiplier)), m_foregroundLayer.TextureHalfWidth);
	m_groundLayer.Position.x = std::fmod(m_groundLayer.Position.x - (deltaTime * (m_speed * m_groundLayer.SpeedMultiplier)), m_groundLayer.TextureHalfWidth);
}

void Background::UpdateRender()
{
	DrawTextureV(m_backgroundLayer.BackgroundTexture, m_backgroundLayer.Position, WHITE);
	DrawTextureV(m_foregroundLayer.BackgroundTexture, m_foregroundLayer.Position, WHITE);
	DrawTextureV(m_groundLayer.BackgroundTexture, m_groundLayer.Position, WHITE);
}

#pragma once
#include "raylib.h"

class Background
{
public:
	Background();
	~Background();
	Background(const Background& background) = delete;
	Background& operator=(const Background& background) = delete;
	Background(Background&& background) noexcept = delete;
	Background& operator=(Background&& background) noexcept = delete;

	void SetSpeed(float newSpeed);
	void UpdateLogic(float deltaTime);
	void UpdateRender(float deltaTime);

private:
	Texture m_backgroundLayerTexture;
	Texture m_foregroundLayerTexture;
	Texture m_groundLayerTexture;

	Vector2 m_backgroundPosition;
	Vector2 m_foregroundPosition;
	Vector2 m_groundPosition;

	float m_speed;
	const float m_backgroundSpeedMultiplier;
	const float m_foregroundSpeedMultiplier;
	const float m_groundSpeedMultiplier;

};
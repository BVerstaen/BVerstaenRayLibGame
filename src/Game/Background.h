#pragma once
#include "raylib.h"
class Background
{

private:
	struct BackgroundData
	{
	public:
		BackgroundData();
		BackgroundData(Texture tex, float baseSpeed);

	public:
		Texture BackgroundTexture;
		Vector2 Position;
		float SpeedMultiplier;
		float TextureHalfWidth;
	};

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
	BackgroundData m_backgroundLayer;
	BackgroundData m_foregroundLayer;
	BackgroundData m_groundLayer;

	float m_speed;
};
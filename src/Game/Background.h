#pragma once
#include "raylib.h"

class Background
{
#pragma region Background data

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
#pragma endregion

#pragma region Constructors / Desctructors / Movement

public:
	Background();
	~Background();
	Background(const Background& background) = delete;
	Background& operator=(const Background& background) = delete;
	Background(Background&& background) noexcept = delete;
	Background& operator=(Background&& background) noexcept = delete;

#pragma endregion

public:
	void ResetSpeed();

	const float GetSpeed() const;
	const float GetGroundLayerSpeed() const;
	void SetSpeed(float newSpeed);
	void UpdateLogic(float deltaTime);
	void UpdateRender();

private:
	BackgroundData m_backgroundLayer;
	BackgroundData m_foregroundLayer;
	BackgroundData m_groundLayer;

	float m_speed;
	float m_defaultSpeed;
};
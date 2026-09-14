#pragma once
#include "raylib.h"

class Background;

class Player
{
public:
	Player(Background* background);

	void UpdateLogic(float deltaTime);
	void UpdateRender(float deltaTime);

private:
	Background* m_background;

	Vector2 m_position;
	float m_verticalGravity;


private:
	Texture m_idleTexture;
	Texture m_flapTexture;
	Texture m_deathTexture;

	float m_slowSpeed;
	float m_defaultSpeed;
	float m_fastSpeed;
	bool m_isChangingSpeed;
};
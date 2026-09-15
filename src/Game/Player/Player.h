#pragma once
#include "raylib.h"

class Background;

class Player
{
public:
	Player();
	~Player();
	Player(const Player& player) = delete;
	Player& operator=(const Player& player) = delete;
	Player(Player&& player) noexcept = delete;
	Player& operator=(Player&& player) noexcept = delete;

	void Setup(Background* background);
	void UpdateLogic(float deltaTime);
	void UpdateRender(float deltaTime);

	const bool IsFiring();
	const bool CheckGroundCollision();

private:
	const bool IsFlapping() const;

public:
	const Vector2& GetPosition() const;
	const Rectangle& GetRectangle() const;

private:
	Background* m_background;

private:
	Vector2 m_position;
	float m_verticalVelocity;
	float m_gravityForce;

private:
	Texture m_idleTexture;
	Texture m_flapTexture;
	Texture m_deathTexture;
	float m_currentFlapAnimationTimer;
	float m_flapAnimationTimer;

	float m_slowSpeed;
	float m_defaultSpeed;
	float m_fastSpeed;
	int m_isChangingSpeed;
};
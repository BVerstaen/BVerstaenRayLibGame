#include "Player.h"

#include <Game/Background.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>


Player::Player(Background* background) : m_position(Vector2(100, 300)), m_verticalVelocity(1), m_gravityForce(50.0f)
{
	if (!background)
		throw std::runtime_error("No valid background");
	m_background = background;

	m_idleTexture = LoadTexture("Sprites\\Player\\Player_Idle.png");
	m_flapTexture = LoadTexture("Sprites\\Player\\Player_Flap.png");
	m_deathTexture = LoadTexture("Sprites\\Player\\Player_Death.png");

	m_slowSpeed = m_background->GetSpeed() * 0.5f;
	m_defaultSpeed = m_background->GetSpeed();
	m_fastSpeed = m_background->GetSpeed() * 1.5f;
	m_isChangingSpeed = false;

	m_flapAnimationTimer = 0.1f;
	m_currentFlapAnimationTimer = 0.0f;
}

Player::~Player()
{
	UnloadTexture(m_idleTexture);
	UnloadTexture(m_flapTexture);
	UnloadTexture(m_deathTexture);
}

void Player::UpdateLogic(float deltaTime)
{
	//Flap logic
	if (IsKeyPressed(KEY_UP))
	{
		m_verticalVelocity -= 100.0f;
		m_currentFlapAnimationTimer = m_flapAnimationTimer;
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		m_verticalVelocity += 100.0f;
		m_currentFlapAnimationTimer = m_flapAnimationTimer;
	}

	//Change speed
	if (IsKeyDown(KEY_LEFT))
	{
		if (m_isChangingSpeed != -1)
		{
			m_background->SetSpeed(m_slowSpeed);
			m_isChangingSpeed = -1;
		}
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		if (m_isChangingSpeed != 1)
		{
			m_background->SetSpeed(m_fastSpeed);
			m_isChangingSpeed = 1;
		}
	}
	else if (m_isChangingSpeed != 0)
	{
		m_background->SetSpeed(m_defaultSpeed);
		m_isChangingSpeed = false;
	}
	
	//Physics logic
	m_verticalVelocity += deltaTime * m_gravityForce;
	m_position.y += deltaTime * m_verticalVelocity;
	if (m_position.y < 0)
	{
		m_position.y = 0;
		m_verticalVelocity = 0;
	}
}

void Player::UpdateRender(float deltaTime)
{
	//Animation logic
	if (IsFlapping())
		m_currentFlapAnimationTimer -= deltaTime;

	DrawTextureV(IsFlapping() ? m_flapTexture : m_idleTexture, m_position, WHITE);
}

const bool Player::CheckDeathCollisions()
{
	//Ground collision
	const float groundYPosition = 430.0f;
	if (m_position.y >= groundYPosition)
		return true;

	return false;
}

const bool Player::IsFlapping() const
{
	return m_currentFlapAnimationTimer > 0.0f;
}

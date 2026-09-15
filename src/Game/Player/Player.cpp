#include "Player.h"

#include <Game/Background.h>
#include <Core/AudioManager.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#pragma region Constructors / Desctructors / Movement
Player::Player() : m_defaultPosition(Vector2(100, 300)), m_verticalVelocity(1), m_gravityForce(50.0f), m_background(nullptr), m_defaultSpeed(0), m_fastSpeed(0), m_slowSpeed(0)
{
	m_position = m_defaultPosition;
	m_idleTexture = LoadTexture("Sprites\\Player\\Player_Idle.png");
	m_flapTexture = LoadTexture("Sprites\\Player\\Player_Flap.png");
	m_deathTexture = LoadTexture("Sprites\\Player\\Player_Death.png");
	m_isChangingSpeed = false;

	m_playerSize = Vector2(m_idleTexture.width, m_idleTexture.height);

	m_flapAnimationTimer = 0.1f;
	m_currentFlapAnimationTimer = 0.0f;
}

Player::~Player()
{
	UnloadTexture(m_idleTexture);
	UnloadTexture(m_flapTexture);
	UnloadTexture(m_deathTexture);
}
#pragma endregion

void Player::Setup(Background* background)
{
	if (!background)
		throw std::runtime_error("No valid background");
	m_background = background;

	m_slowSpeed = m_background->GetSpeed() * 0.5f;
	m_defaultSpeed = m_background->GetSpeed();
	m_fastSpeed = m_background->GetSpeed() * 1.5f;
}

void Player::Reset()
{
	m_position = m_defaultPosition;
	m_verticalVelocity = 1.0f;
	m_currentFlapAnimationTimer = 0.0f;
}

void Player::UpdateLogic(float deltaTime)
{
	//Flap logic
	if (IsKeyPressed(KEY_UP))
	{
		m_verticalVelocity -= 100.0f;
		m_currentFlapAnimationTimer = m_flapAnimationTimer;
		AudioManager::Instance().PlaySoundFromList(AudioManager::SoundList::PLAYERFLAP);
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		m_verticalVelocity += 100.0f;
		m_currentFlapAnimationTimer = m_flapAnimationTimer;
		AudioManager::Instance().PlaySoundFromList(AudioManager::SoundList::PLAYERFLAP);
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

void Player::RenderDeath()
{
	DrawTextureV(m_deathTexture, m_position, WHITE);
}

const bool Player::IsFiring()
{
	return IsKeyPressed(KEY_SPACE);
}

const bool Player::CheckGroundCollision()
{
	//Ground collision
	const float groundYPosition = 480.0f;
	if (m_position.y >= groundYPosition)
		return true;

	return false;
}

const bool Player::IsFlapping() const
{
	return m_currentFlapAnimationTimer > 0.0f;
}

const Vector2& Player::GetPosition() const
{
	return m_position;
}

const Rectangle& Player::GetRectangle() const
{
	//Using flap collision made the game unplayable
	//Texture currentTexture = IsFlapping() ? m_flapTexture : m_idleTexture;
	return Rectangle(m_position.x, m_position.y, m_playerSize.x, m_playerSize.y);
}

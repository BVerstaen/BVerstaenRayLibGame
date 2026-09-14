#include "Player.h"
#include "Background.h"
#include <stdexcept>
#include <iostream>



Player::Player(Background* background)
{
	if (!background)
		throw std::runtime_error("No valid background");

	m_background = background;
	m_position = Vector2(100, 300);
	m_verticalGravity = 1;

	m_idleTexture = LoadTexture("Sprites\\Player\\Player_Idle.png");
	m_flapTexture = LoadTexture("Sprites\\Player\\Player_Flap.png");
	m_deathTexture = LoadTexture("Sprites\\Player\\Player_Death.png");

	m_slowSpeed = m_background->GetSpeed() * 0.5f;
	m_defaultSpeed = m_background->GetSpeed();
	m_fastSpeed = m_background->GetSpeed() * 1.5f;
	m_isChangingSpeed = false;
}

void Player::UpdateLogic(float deltaTime)
{
	//Process input
	if (IsKeyPressed(KEY_UP))
	{

	}
	if (IsKeyPressed(KEY_DOWN))
	{

	}

	//Change speed
	if (IsKeyDown(KEY_LEFT))
	{
		if (!m_isChangingSpeed)
		{
			m_background->SetSpeed(m_slowSpeed);
			m_isChangingSpeed = true;
		}
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		if (!m_isChangingSpeed)
		{
			m_background->SetSpeed(m_fastSpeed);
			m_isChangingSpeed = true;
		}
	}
	else if (m_isChangingSpeed)
	{
		m_background->SetSpeed(m_defaultSpeed);
		m_isChangingSpeed = false;
	}

	m_position.y += deltaTime * m_verticalGravity;
}

void Player::UpdateRender(float deltaTime)
{
	DrawTextureV(m_idleTexture, m_position, WHITE);

}

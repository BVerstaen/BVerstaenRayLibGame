#include "Target.h"

Target::Target(Texture tex, Vector2 basePosition)
{
	m_targetTexture = tex;
	m_position = basePosition;
}

//Returns true if out of screen
bool Target::UpdateLogic(float deltaTime, float groundSpeed)
{
	m_position.x -= (deltaTime * groundSpeed);

	return m_position.x <= -m_targetTexture.width;
}

void Target::UpdateRender(float deltaTime)
{
	DrawTextureV(m_targetTexture, m_position, WHITE);
}

bool Target::CheckCollisions()
{
	return false;
}

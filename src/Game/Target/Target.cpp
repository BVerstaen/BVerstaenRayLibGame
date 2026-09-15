#include "Target.h"

Target::Target(Texture tex, Vector2 basePosition):m_targetTexture(tex), m_position(basePosition)
{
}

//Returns true if out of screen
bool Target::UpdateLogic(float deltaTime, float groundSpeed)
{
	m_position.x -= (deltaTime * groundSpeed);

	return m_position.x <= -m_targetTexture.width;
}

void Target::UpdateRender()
{
	DrawTextureV(m_targetTexture, m_position, WHITE);
}

const Vector2 Target::GetPosition() const
{
	return m_position;
}

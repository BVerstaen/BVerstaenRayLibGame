#include "Hazard.h"

Hazard::Hazard(Texture tex, Vector2 basePosition, float baseRotation, float speed): m_hazardTexture(tex), m_position(basePosition), m_rotation(baseRotation), m_speed(speed), m_rotationSpeed(20)
{
}

//Returns true if out of screen
bool Hazard::UpdateLogic(float deltaTime, float groundSpeed)
{
	m_position.x -= m_speed + (deltaTime * groundSpeed);
	m_rotation += deltaTime * m_rotationSpeed;

	return m_position.x <= -m_hazardTexture.width;
}

void Hazard::UpdateRender(float deltaTime)
{
	DrawTextureEx(m_hazardTexture, m_position, m_rotation, 1.0f, WHITE);
}

const Vector2 Hazard::GetPosition() const
{
	return m_position;
}

#include "Hazard.h"
#include "raymath.h"

Hazard::Hazard(Texture tex, Vector2 basePosition, float baseRotation, float speed): m_hazardTexture(tex), m_position(basePosition), m_rotation(baseRotation), m_speed(speed), m_rotationSpeed(500)
{
}

//Returns true if out of screen
bool Hazard::UpdateLogic(float deltaTime, float groundSpeed)
{
	m_position.x -= m_speed + (deltaTime * groundSpeed);
	m_rotation += deltaTime * m_rotationSpeed;

	return m_position.x <= -m_hazardTexture.width;
}

void Hazard::UpdateRender()
{
	Rectangle drawRect = Rectangle(0, 0, m_hazardTexture.width, m_hazardTexture.height);
	Vector2 centerRect = Vector2(m_hazardTexture.width / 2, m_hazardTexture.height / 2);
	DrawTexturePro(m_hazardTexture, drawRect, Rectangle(m_position.x + centerRect.x, m_position.y + centerRect.y, drawRect.width, drawRect.height), centerRect, m_rotation, WHITE);
}

const Vector2 Hazard::GetPosition() const
{
	Vector2 centerRect = Vector2(m_hazardTexture.width / 2, m_hazardTexture.height / 2);
	return Vector2Add(m_position, centerRect);
}

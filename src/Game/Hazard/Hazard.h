#pragma once

#include "raylib.h"

class Hazard
{
public:
	Hazard(Texture tex, Vector2 basePosition, float baseRotation, float speed);

	bool UpdateLogic(float deltaTime, float groundSpeed);
	void UpdateRender();

public:
	const Vector2 GetPosition() const;

private:
	Texture m_hazardTexture;
	Vector2 m_position;
	float m_rotation;
	float m_rotationSpeed;
	float m_speed;
};
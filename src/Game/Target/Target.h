#pragma once

#include "raylib.h"

class Target 
{
public:
	Target(Texture tex, Vector2 basePosition);

	bool UpdateLogic(float deltaTime, float groundSpeed);
	void UpdateRender();

public:
	const Vector2 GetPosition() const;

private:
	Texture m_targetTexture;
	Vector2 m_position;
};
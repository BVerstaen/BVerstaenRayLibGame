#pragma once
#include "raylib.h"
#include <Core/ScoreSystem.h>

class GameFont;

class ScoreUI
{
public:
	ScoreUI();

	void DrawScore(float deltaTime, int currentScore);

private:
	GameFont& m_gameFont;
	const Vector2 m_textPosition;
	const int m_fontSize;
	float m_counter;
	float m_rotation;
};
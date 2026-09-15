#pragma once
#include "raylib.h"
#include <Core/ScoreSystem.h>

class GameFont;

class ScoreUI
{
public:
	ScoreUI();

	void DrawScore(int currentScore);

private:
	GameFont& m_gameFont;
	const int m_screenWidth;
	const int m_fontSize;
};
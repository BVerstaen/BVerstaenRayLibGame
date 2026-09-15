#pragma once
#include "raylib.h"
#include <vector>

class TitleScreen
{
#pragma region Constructors / Desctructors / Movement

public:
	TitleScreen();

#pragma endregion

public:
	bool CheckStartKey();
	void UpdateRender(const std::vector<int> highscoreList);

private:
	const float m_highScoreGap;
	const Vector2 m_highScoreStartPosition;
};
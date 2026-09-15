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
	bool UpdateLogic(float deltaTime);
	void UpdateRender(const std::vector<int> highscoreList);
	void UpdateInstruction();

private:
	Texture m_instructionTexture;

	float m_titleHue;
	const float m_hueSpeed;

	const float m_highScoreGap;
	const Vector2 m_highScoreStartPosition;
};
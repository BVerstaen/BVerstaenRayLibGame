#pragma once
#include "raylib.h"
#include <vector>

class TitleScreen
{
#pragma region Constructors / Desctructors / Movement

public:
	TitleScreen();
	~TitleScreen();
	TitleScreen(const TitleScreen& titleScreen) = delete;
	TitleScreen& operator=(const TitleScreen& titleScreen) = delete;
	TitleScreen(TitleScreen&& titleScreen) noexcept = delete;
	TitleScreen& operator=(TitleScreen&& titleScreen) noexcept = delete;

#pragma endregion

public:
	void UpdateLogic(float deltaTime);
	void UpdateRender(const std::vector<int> highscoreList);
	void UpdateInstruction();

private:
	std::vector<Texture> m_medalsTextures;
	Texture m_instructionTexture;

	float m_titleHue;
	const float m_hueSpeed;

	const float m_highScoreGap;
	const Vector2 m_highScoreStartPosition;
};
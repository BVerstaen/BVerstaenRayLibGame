#pragma once
#include <string>
#include <vector>
#include "raylib.h"
#include <Core/GameFont.h>

class GameOverManager
{
#pragma region Game over text data
private:
	struct GameOverText
	{
	public:
		GameOverText();
		GameOverText(std::string text, Vector2 pos, float delay, float rotationAmp, float textSize = -1, Color col = WHITE, bool addScoreAtEnd = false);

	public:
		std::string Text;
		Vector2 Position;

		float Delay;
		float Size;
		float Amplitude;
		Color TextColor;

		bool AddScoreToText;
	};
#pragma endregion

public:
	GameOverManager();

public:
	bool UpdateLogic(float deltaTime);
	void UpdateRender(int currentScore);

private:
	GameFont& m_gameFont;
	std::vector<GameOverText> m_gameOverTextList;

	float m_counter;
	float m_pressAnyKeyCounter;
};
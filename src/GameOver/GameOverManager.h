#pragma once
#include <string>
#include <vector>
#include "raylib.h"
#include <Core/GameFont.h>

class GameOverManager
{
private: 
	enum class TextType
	{
		STANDARD,
		ADDSCOREATEND,
		DISPLAYIFHIGHSCORE
	};

#pragma region Game over text data
private:
	struct GameOverText
	{
	public:
		GameOverText();
		GameOverText(std::string text, Vector2 pos, float delay, float rotationAmp, float textSize = -1, Color col = WHITE, TextType textType = TextType::STANDARD);

	public:
		std::string Text;
		Vector2 Position;

		float Delay;
		float Size;
		float Amplitude;
		Color TextColor;

		TextType Type;
	};
#pragma endregion

public:
	GameOverManager();

public:
	void Reset();

	bool UpdateLogic(float deltaTime);
	void UpdateRender(int currentScore, bool hasReachHighScore);

private:
	GameFont& m_gameFont;
	std::vector<GameOverText> m_gameOverTextList;

	float m_counter;
	float m_pressAnyKeyCounter;
};
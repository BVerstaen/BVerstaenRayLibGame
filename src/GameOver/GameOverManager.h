#pragma once
#include <string>
#include "raylib.h"
#include <vector>

class GameOverManager
{
#pragma region Game over text data
private:
	struct GameOverText
	{
	public:
		GameOverText();
		GameOverText(std::string text, Vector2 pos, float delay, Color col = WHITE);

	public:
		std::string Text;
		Vector2 Position;
		float Delay;
		Color Color;
	};
#pragma endregion

public:
	GameOverManager();

public:
	void UpdateLogic(float deltaTime);
	void UpdateRender(float deltaTime);

private:
	std::vector<GameOverText> m_gameOverTextList;
	float m_counter;
};
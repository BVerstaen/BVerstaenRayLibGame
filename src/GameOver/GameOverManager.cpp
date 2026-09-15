#include "GameOverManager.h"
#include <cmath>
#include <string>

#pragma region Game over text data

GameOverManager::GameOverText::GameOverText() :Text(""), Position(Vector2(0, 0)), Delay(0), TextColor(WHITE), Amplitude(0), Size(-1), Type(TextType::STANDARD)
{
}

GameOverManager::GameOverText::GameOverText(std::string text, Vector2 pos, float delay, float rotationAmp, float textSize, Color col, TextType textType) :Text(text), Position(pos), Delay(delay), Amplitude(rotationAmp), Size(textSize), TextColor(col), Type(textType)
{
}

#pragma endregion


GameOverManager::GameOverManager() : m_counter(0), m_gameFont(GameFont::Instance()), m_pressAnyKeyCounter(1.0f)
{
	//Add text
	m_gameOverTextList.push_back(GameOverText("GAME OVER", Vector2(400, 150), 0.0f, 10.0f, 60.0f, RED));
	m_gameOverTextList.push_back(GameOverText("Final score: ", Vector2(400, 300), 0.5f, 0.0f, -1, WHITE, TextType::ADDSCOREATEND));
	m_gameOverTextList.push_back(GameOverText("You reached a new highscore !!!", Vector2(400, 340), 0.5f, 0.0f, -1, ORANGE, TextType::DISPLAYIFHIGHSCORE));
	m_gameOverTextList.push_back(GameOverText("press any key", Vector2(400, 400), 1.0f, -5.0f, -1, RAYWHITE));
}

void GameOverManager::Reset()
{
	m_counter = 0.0f;
}

//Returns true if switch state
bool GameOverManager::UpdateLogic(float deltaTime)
{
	m_counter += deltaTime;
	return (m_counter >= m_pressAnyKeyCounter && GetKeyPressed() != 0);
}

void GameOverManager::UpdateRender(int currentScore, bool hasReachHighScore)
{
	//Display text if reach delay
	for (const GameOverText& textData : m_gameOverTextList)
	{
		if (m_counter >= textData.Delay)
		{
			float rotation = textData.Amplitude != 0 ? std::sin(m_counter * 100 * PI / 180.0) * textData.Amplitude : 0;

			switch (textData.Type)
			{

			case TextType::ADDSCOREATEND:
			{
				m_gameFont.PrintTextPro(textData.Text + std::to_string(currentScore), textData.Position, rotation, textData.Size, textData.TextColor);
				break;
			}

			case TextType::DISPLAYIFHIGHSCORE:
				if(!hasReachHighScore)
					break;
			case TextType::STANDARD:
			default:
				m_gameFont.PrintTextPro(textData.Text, textData.Position, rotation, textData.Size, textData.TextColor);
				break;
			}
		}
	}
}
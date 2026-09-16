#include "TitleScreen.h"
#include <Core/GameFont.h>
#include <Core/ColorUtilities.h>

#pragma region Constructors / Desctructors / Movement

TitleScreen::TitleScreen() : m_highScoreStartPosition(Vector2(100, 270)), m_highScoreGap(75), m_hueSpeed(1.0f)
{
	m_titleHue = 0.0f;
	m_instructionTexture = LoadTexture("Sprites\\Instruction.png");

	//Add textures
	const int targetNumber = 3;
	for (int i = 0; i < targetNumber; i++)
	{
		std::string texPath = "Sprites\\HighScore_" + std::to_string(i) + ".png";
		if (!FileExists(texPath.c_str()))
		{
			TraceLog(LOG_ERROR, "File [%s] is invalid", texPath.c_str());
			continue;
		}

		m_medalsTextures.push_back(LoadTexture(texPath.c_str()));
	}

}

TitleScreen::~TitleScreen()
{
	for (Texture& texture : m_medalsTextures)
	{
		UnloadTexture(texture);
	}
}

#pragma endregion

void TitleScreen::UpdateLogic(float deltaTime)
{
	m_titleHue += deltaTime * m_hueSpeed;
}

void TitleScreen::UpdateRender(const std::vector<int> highscoreList)
{
	//Display title screen
	GameFont::Instance().PrintTextPro("Dragon Rampage", Vector2(400,200), 0.0f, 80.0f, ColorUtilities::ColorFromHue(m_titleHue));

	//Display highscores
	GameFont::Instance().PrintText("Highscores:", m_highScoreStartPosition, -1, RED);
	Vector2 newPosition = m_highScoreStartPosition;

	newPosition.x += 30.0f; //Extra padding
	newPosition.y += m_highScoreGap;
	for (int i = 0; i < highscoreList.size(); i++)
	{
		std::string highScoreText = std::to_string(highscoreList[i]);

		DrawTexture(m_medalsTextures[i], m_highScoreStartPosition.x - 10, newPosition.y - (m_medalsTextures[i].height / 3), WHITE);
		GameFont::Instance().PrintText("  - " + highScoreText, newPosition);
		newPosition.y += m_highScoreGap;
	}

	GameFont::Instance().PrintTextPro("Press any key", Vector2(550, 400), 0.0f, -1, WHITE);

}

void TitleScreen::UpdateInstruction()
{
	DrawTexture(m_instructionTexture, 100, 150, WHITE);
	GameFont::Instance().PrintTextPro("Press any key", Vector2(400, 475), 0.0f, -1, WHITE);
}

#include "TitleScreen.h"
#include <Core/GameFont.h>
#include <Core/ColorUtilities.h>

TitleScreen::TitleScreen() : m_highScoreStartPosition(Vector2(300, 300)), m_highScoreGap(40), m_hueSpeed(1.0f)
{
	m_titleHue = 0.0f;
}

//returns true if a key is pressed
bool TitleScreen::UpdateLogic(float deltaTime)
{
	m_titleHue += deltaTime * m_hueSpeed;

	return GetKeyPressed();
}

void TitleScreen::UpdateRender(const std::vector<int> highscoreList)
{
	//Display title screen
	GameFont::Instance().PrintTextPro("Dragon Rampage", Vector2(400,200), 0.0f, 80.0f, ColorUtilities::ColorFromHue(m_titleHue));

	//Display highscores
	Vector2 newPosition = m_highScoreStartPosition;

	GameFont::Instance().PrintText("Highscores:", newPosition, -1, RED);
	newPosition.y += m_highScoreGap;
	for (int i = 0; i < highscoreList.size(); i++)
	{
		std::string highScoreText = std::to_string(highscoreList[i]);

		GameFont::Instance().PrintText(std::to_string(i+1) + " - " + highScoreText, newPosition);
		newPosition.y += m_highScoreGap;
	}
}
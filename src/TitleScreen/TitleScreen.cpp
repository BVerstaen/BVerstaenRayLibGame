#include "TitleScreen.h"
#include <Core/GameFont.h>

TitleScreen::TitleScreen() : m_highScoreStartPosition(Vector2(300, 300)), m_highScoreGap(40)
{
}

bool TitleScreen::CheckStartKey()
{
	return GetKeyPressed();
}

void TitleScreen::UpdateRender(const std::vector<int> highscoreList)
{
	//Display title screen
	GameFont::Instance().PrintTextPro("Dragon Rampage", Vector2(400,200), 0.0f, 80.0f, WHITE);

	//Display highscores
	Vector2 newPosition = m_highScoreStartPosition;

	GameFont::Instance().PrintText("Highscores:", newPosition, -1, RED);
	newPosition.y += m_highScoreGap;
	for (int i = 0; i < highscoreList.size(); i++)
	{
		std::string highScoreText = std::to_string(highscoreList[i]);

		GameFont::Instance().PrintText(std::to_string(i) + " - " + highScoreText, newPosition);
		newPosition.y += m_highScoreGap;
	}
}

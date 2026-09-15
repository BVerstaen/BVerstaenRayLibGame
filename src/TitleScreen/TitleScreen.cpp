#include "TitleScreen.h"
#include <cmath>
#include <Core/GameFont.h>


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
	GameFont::Instance().PrintTextPro("Dragon Rampage", Vector2(400,200), 0.0f, 80.0f, ColorFromHue(m_titleHue));

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

Color TitleScreen::ColorFromHue(float hue)
{
	hue = std::fmod(hue, 1.0f);
	if (hue < 0.0f) hue += 1.0f;

	Color newColor;

	float r = std::fmod(5 + hue * 6, 6);
	float g = std::fmod(3 + hue * 6, 6);
	float b = std::fmod(1 + hue * 6, 6);

	newColor.r = 255 * (1 - std::max(std::min(std::min(r, 4 - r), 1.0f), 0.0f));
	newColor.g = 255 * (1 - std::max(std::min(std::min(g, 4 - g), 1.0f), 0.0f));
	newColor.b = 255 * (1 - std::max(std::min(std::min(b, 4 - b), 1.0f), 0.0f));

	return newColor;
}

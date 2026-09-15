#include "ScoreUI.h"
#include <Core/GameFont.h>

ScoreUI::ScoreUI() : m_screenWidth(800), m_gameFont(GameFont::Instance()), m_fontSize(40)
{	
}

void ScoreUI::DrawScore(int currentScore)
{
	std::string scoreText = std::to_string(currentScore);
	Vector2 textSize = m_gameFont.MesureText(scoreText, m_fontSize);
	Vector2 textPosition = Vector2((m_screenWidth - textSize.x) / 2.0f, 50);

	m_gameFont.PrintText(scoreText, textPosition, m_fontSize);
}

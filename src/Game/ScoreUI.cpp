#include "ScoreUI.h"
#include <cmath>
#include <Core/GameFont.h>

ScoreUI::ScoreUI() : m_textPosition(Vector2(400,50)), m_gameFont(GameFont::Instance()), m_fontSize(40), m_rotation(0), m_counter(0)
{	
}

void ScoreUI::DrawScore(float deltaTime, int currentScore)
{
	m_counter += deltaTime * 100;
	m_rotation = std::sin(m_counter * PI / 180.0) * 10;

	m_gameFont.PrintTextPro(std::to_string(currentScore), m_textPosition, m_rotation, m_fontSize);
}

#include "GameFont.h"
#include <string>

GameFont::GameFont():m_defaultSize(32)
{
	const char* gameFontPath = "Font\\GameFont.ttf";
	m_gameFont = LoadFont(gameFontPath);
}

GameFont::~GameFont()
{
	UnloadFont(m_gameFont);
}

void GameFont::PrintText(const std::string& text, Vector2 position, float size, Color color)
{
	if (size <= 0)
		size = m_defaultSize;

	
	DrawTextEx(m_gameFont, text.c_str(), position, size, m_gameFont.glyphPadding, color);

}


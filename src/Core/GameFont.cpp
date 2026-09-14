#include "GameFont.h"
#include <string>

GameFont::GameFont()
{
	const char* gameFontPath = "Font\\GameFont.tff";
	m_gameFont = LoadFont(gameFontPath);
}

GameFont::~GameFont()
{
	UnloadFont(m_gameFont);
}

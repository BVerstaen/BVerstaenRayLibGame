#include "GameFont.h"
#include <string>
#include <stdexcept>

#pragma region Constructors / Desctructors / Movement
GameFont::GameFont():m_defaultSize(32), m_spacing(5)
{
	const char* gameFontPath = "Font\\GameFont.ttf";
	m_gameFont = LoadFont(gameFontPath);

	//Singleton
	if (s_instance)
		throw std::runtime_error("There can only be one input manager");
	s_instance = this;
}

GameFont::~GameFont()
{
	UnloadFont(m_gameFont);
	s_instance = nullptr;
}
#pragma endregion


#pragma region Singleton

GameFont* GameFont::s_instance = nullptr;
GameFont& GameFont::Instance()
{
	if (!s_instance)
		throw std::runtime_error("No game font was created");

	return *s_instance;
}

#pragma endregion

void GameFont::PrintText(const std::string& text, Vector2 position, float size, Color color)
{
	if (size <= 0)
		size = m_defaultSize;

	DrawTextEx(m_gameFont, text.c_str(), position, size, m_spacing, color);

}

void GameFont::PrintTextPro(const std::string& text, Vector2 position, float rotation, float size, Color color)
{
	if (size <= 0)
		size = m_defaultSize;

	Vector2 textSize = MesureText(text, size);
	Vector2 origin = Vector2(textSize.x / 2, textSize.y / 2);
	DrawTextPro(m_gameFont, text.c_str(), position, origin, rotation, size, m_spacing, color);
}

const Vector2 GameFont::MesureText(const std::string text, float size) const
{
	if (size <= 0)
		size = m_defaultSize;

	return MeasureTextEx(m_gameFont, text.c_str(), size, m_spacing);
}


#pragma once

#include "raylib.h"
#include <string>

class GameFont
{
#pragma region Constructors / Desctructors / Movement
public:
	GameFont();
	~GameFont();
	GameFont(const GameFont& font) = delete;
	GameFont& operator=(const GameFont& font) = delete;
	GameFont(GameFont&& font) noexcept = delete;
	GameFont& operator=(GameFont&& font) noexcept = delete;
#pragma endregion

#pragma region Singleton

public:
	static GameFont& Instance();
private:
	static GameFont* s_instance;

#pragma endregion

public:
	void PrintText(const std::string& text, Vector2 position, float size = -1, Color color = WHITE);
	void PrintTextPro(const std::string& text, Vector2 position, float rotation, float size = -1, Color color = WHITE);
	const Vector2 MesureText(const std::string text, float size = -1) const;

private:
	int m_defaultSize;
	float m_spacing;
	Font m_gameFont;
};
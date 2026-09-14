#pragma once

#include "raylib.h"
#include <string>

class GameFont
{
public:
	GameFont();
	~GameFont();
	GameFont(const GameFont& font) = delete;
	GameFont& operator=(const GameFont& font) = delete;
	GameFont(GameFont&& font) noexcept = delete;
	GameFont& operator=(GameFont&& font) noexcept = delete;

public:
	void PrintText(const std::string& text, Vector2 position, float size = -1, Color color = WHITE);

private:
	int m_defaultSize;
	Font m_gameFont;
};
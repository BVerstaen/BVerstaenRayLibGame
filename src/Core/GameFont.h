#pragma once

#include "raylib.h"

class GameFont
{
public:
	GameFont();
	~GameFont();
	GameFont(const GameFont& font) = delete;
	GameFont& operator=(const GameFont& font) = delete;
	GameFont(GameFont&& font) noexcept = delete;
	GameFont& operator=(GameFont&& font) noexcept = delete;

private:
	Font m_gameFont;
};
#include "raylib.h"
#include "resource_dir.h"

#include <Game/Background.h>
#include <Game/Player.h>
#include <Core/ScoreSystem.h>
#include <Core/GameFont.h>

int main ()
{
	//Init window & ressources
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(800, 600, "Dragon fly");
	SearchAndSetResourceDir("resources");

	GameFont font;
	
	Background background;
	Player player = Player(&background);
	ScoreSystem scoreSys = ScoreSystem();


	scoreSys.ResetScore();
	//Game loop
	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();

		//LOGIC UPDATE
		background.UpdateLogic(deltaTime);
		player.UpdateLogic(deltaTime);
		scoreSys.UpdateScore(deltaTime, background.GetSpeed());

		if (player.CheckDeathCollisions())
			break;

		//RENDER UPDATE
		BeginDrawing();
		ClearBackground(BLACK);

		background.UpdateRender(deltaTime);
		player.UpdateRender(deltaTime);
		font.PrintText(std::to_string(player.m_position.y), Vector2(30, 30));

		font.PrintText(std::to_string(scoreSys.CurrentScore), Vector2(30, 10));
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

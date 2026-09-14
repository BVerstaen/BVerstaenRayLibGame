#include "raylib.h"
#include "resource_dir.h"

#include "Game/Background.h"
#include <Game/Player.h>

int main ()
{
	//Init window & ressources
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(800, 600, "Dragon fly");
	SearchAndSetResourceDir("resources");

	//Background
	Background background;

	//Player
	Player player = Player(&background);

	//Game loop
	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();

		//LOGIC UPDATE
		background.UpdateLogic(deltaTime);
		player.UpdateLogic(deltaTime);

		//if (IsKeyDown(KEY_LEFT))
		//	playerPos.x -= playerSpeed;
		//else if (IsKeyDown(KEY_RIGHT))
		//	playerPos.x += playerSpeed;
		//if (IsKeyDown(KEY_UP))
		//	playerPos.y -= playerSpeed;
		//if (IsKeyDown(KEY_DOWN))
		//	playerPos.y += playerSpeed;

		//RENDER UPDATE
		BeginDrawing();
		ClearBackground(BLACK);

		background.UpdateRender(deltaTime);
		player.UpdateRender(deltaTime);
		
		EndDrawing();
	}

	// CLEAN UP
	//UnloadTexture(background);
	CloseWindow();
	return 0;
}

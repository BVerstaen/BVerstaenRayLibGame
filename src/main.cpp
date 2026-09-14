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

		//RENDER UPDATE
		BeginDrawing();
		ClearBackground(BLACK);

		background.UpdateRender(deltaTime);
		player.UpdateRender(deltaTime);
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

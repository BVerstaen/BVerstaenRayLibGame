
#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "Game/Background.h"

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(800, 600, "Hello Raylib");
	SearchAndSetResourceDir("resources");

	//Background
	Background background;

	//Player
	Texture player = LoadTexture("Sprites\\player.png");
	Vector2 playerPos = Vector2(100,100);
	constexpr float playerSpeed = 1.0f;

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		float deltaTime = GetFrameTime();


		//LOGIC UPDATE
		background.UpdateLogic(deltaTime);
		if (IsKeyDown(KEY_LEFT))
			playerPos.x -= playerSpeed;
		else if (IsKeyDown(KEY_RIGHT))
			playerPos.x += playerSpeed;
		if (IsKeyDown(KEY_UP))
			playerPos.y -= playerSpeed;
		if (IsKeyDown(KEY_DOWN))
			playerPos.y += playerSpeed;

		//RENDER UPDATE
		BeginDrawing();
		ClearBackground(BLACK);
		background.UpdateRender(deltaTime);

		DrawTexture(player, playerPos.x, playerPos.y, WHITE);
		
		EndDrawing();
	}

	// CLEAN UP
	//UnloadTexture(background);
	CloseWindow();
	return 0;
}

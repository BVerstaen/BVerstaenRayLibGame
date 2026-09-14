
#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture background = LoadTexture("Sprites\\Background.png");
	
	//Player
	Texture player = LoadTexture("Sprites\\player.png");
	Vector2 playerPos = Vector2(100,100);
	constexpr float playerSpeed = 1.0f;

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		float deltaTime = GetFrameTime();

		//LOGIC UPDATE
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

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,WHITE);

		// draw our texture to the screen
		DrawTexture(background, 0, 0, WHITE);
		DrawTexture(player, playerPos.x, playerPos.y, WHITE);
		
		EndDrawing();
	}

	// CLEAN UP
	UnloadTexture(background);
	CloseWindow();
	return 0;
}

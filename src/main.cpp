#include "raylib.h"
#include "resource_dir.h"

#include <Core/Application.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main()
{
	//Init window & ressources
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dragon rampage");
	SearchAndSetResourceDir("resources");

	Application app;
	app.Run();

	CloseWindow();
	return 0;
}

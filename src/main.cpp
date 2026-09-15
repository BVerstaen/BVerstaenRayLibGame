#include "raylib.h"
#include "resource_dir.h"

#include <Core/Application.h>

int main()
{
	//Init window & ressources
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(800, 600, "Dragon rampage");
	SearchAndSetResourceDir("resources");

	Application app;
	app.Run();

	CloseWindow();
	return 0;
}

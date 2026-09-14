#include "raylib.h"
#include "resource_dir.h"

#include <Game/Background.h>
#include <Game/Player/Player.h>
#include <Core/ScoreSystem.h>
#include <Core/GameFont.h>
#include <Game/Target/TargetManager.h>
#include <Game/Player/PlayerProjectile.h>

int main ()
{
	//Init window & ressources
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(800, 600, "Dragon rampage");
	SearchAndSetResourceDir("resources");

	GameFont font;
	ScoreSystem scoreSys = ScoreSystem();

	Background background;
	Player player = Player(&background);
	PlayerProjectile playerProj = PlayerProjectile();
	TargetManager targetManager = TargetManager();


	scoreSys.ResetScore();
	//Game loop
	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();

		//LOGIC UPDATE
		background.UpdateLogic(deltaTime);
		player.UpdateLogic(deltaTime);

		//TODO -> move to player
		if (IsKeyPressed(KEY_SPACE))
			playerProj.SpawnProjectile(player.GetPosition());
		playerProj.UpdateLogic(deltaTime);

		targetManager.UpdateLogic(deltaTime, background.GetSpeed(), background.GetGroundLayerSpeed());
		targetManager.UpdateCollisions(playerProj.GetProjectilePositions(), playerProj.GetProjectileSize());
		scoreSys.UpdateScore(deltaTime, background.GetSpeed());

		if (player.CheckDeathCollisions())
			break;

		//RENDER UPDATE
		BeginDrawing();
		ClearBackground(BLACK);

		background.UpdateRender(deltaTime);
		targetManager.UpdateRender(deltaTime);
		player.UpdateRender(deltaTime);
		playerProj.UpdateRender(deltaTime);

		font.PrintText(std::to_string(scoreSys.CurrentScore), Vector2(30, 10));

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

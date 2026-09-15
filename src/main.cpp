#include "raylib.h"
#include "resource_dir.h"

#include <Core/ScoreSystem.h>
#include <Core/GameFont.h>
#include <Core/Random.h>
#include <Game/Background.h>
#include <Game/Player/Player.h>
#include <Game/Target/TargetManager.h>
#include <Game/Player/PlayerProjectile.h>
#include <Game/ScoreUI.h>
#include <Game/Hazard/HazardManager.h>

int main()
{
	//Init window & ressources
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(800, 600, "Dragon rampage");
	SearchAndSetResourceDir("resources");

	Random rand;
	GameFont font;
	ScoreSystem scoreSys = ScoreSystem();

	Background background;
	Player player = Player(&background);
	PlayerProjectile playerProj = PlayerProjectile();

	TargetManager targetManager = TargetManager();
	HazardManager hazardManager = HazardManager();

	ScoreUI scoreUI = ScoreUI();

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
		targetManager.UpdateCollisions(scoreSys, playerProj.GetProjectilePositions(), playerProj.GetProjectileSize());

		hazardManager.UpdateLogic(deltaTime, background.GetSpeed(), background.GetGroundLayerSpeed());

		scoreSys.UpdateScore(deltaTime, background.GetSpeed());

		if (player.CheckGroundCollision() || hazardManager.UpdateCollisions(player.GetRectangle()))
			break;

		//RENDER UPDATE
		BeginDrawing();
		ClearBackground(BLACK);

		background.UpdateRender(deltaTime);
		targetManager.UpdateRender(deltaTime);
		player.UpdateRender(deltaTime);
		playerProj.UpdateRender(deltaTime);
		hazardManager.UpdateRender(deltaTime);

		scoreUI.DrawScore(scoreSys.CurrentScore);

		EndDrawing();
	}
	scoreSys.AddScoreToHighScore();

	CloseWindow();
	return 0;
}

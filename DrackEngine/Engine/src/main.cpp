/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-11-2022  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 		Main.hpp      		  *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "myIncludes/game.hpp"

//******************************************************************************//
//									MAIN										//
//******************************************************************************//

void ftChooseMode(Menu *menu)
{
	static int ct;

	if (!ct)
		ct = 1;

	if (IsKeyPressed(KEY_W))
		ct--;
	else if (IsKeyPressed(KEY_S))
		ct++;
	if (ct > 2)
		ct = 1;
	else if (ct < 1)
		ct = 2;

	if (IsKeyPressed(KEY_ENTER))
	{
		if (ct == 1)
			menu->ftChangeStart(9);
		else if (ct == 2)
			menu->ftChangeStart(8);
	}

	if (ct == 1)
	{
		DrawText("<---*", 750, 360, 20, DARKGRAY);
	}
	else if (ct == 2)
	{
		DrawText("<---*", 750, 410, 20, DARKGRAY);
	}
}

void	ftBigMenuControl(Menu *menu)
{
	DrawText("Welcome to DrackEngine", 535, 250, 40, BLACK);
	DrawText("2D Engine ", 535, 350, 30, DARKGRAY);
	DrawText("3D Engine ", 535, 400, 30, DARKGRAY);

	ftChooseMode(menu);
}

void PrintMsgTests(void)
{
	DE_TRACE("Hello World! %f", 1.0f);
	DE_DEBUG("Hello World! %f", 1.0f);
	DE_INFO("Hello World! %f", 1.0f);
	DE_WARN("Hello World! %f", 1.0f);
	DE_ERROR("Hello World! %f", 1.0f);
	DE_FATAL("Hello World! %f", 1.0f);
}

int main(void)
{
	Game	game;
	Menu	menu;

	PrintMsgTests();

	game.font1 = LoadFontEx("../fonts/Greenscr.ttf", 32, 0, 250);

	InitWindow(game.screenWidth, game.screenHeight, "DrackEngine");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		if (menu.ftReturnStart() == 10) // Control menu
		{
			ftBigMenuControl(&menu);
		}
		if (menu.ftReturnStart() == 9) // 2D Mode
		{
			EndDrawing();
			menu.ftChangeStart(0);
			ftMode2D(&game, &menu);
			menu.ftChangeStart(10);
		}
		if (menu.ftReturnStart() == 8) // 3D Mode
		{
			EndDrawing();
			ftMode3D(&game);
			menu.ftChangeStart(10);
		}
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}

#define WIN32_LEAN_AND_MEAN
#define WIN32_LEANER_AND_MEANER

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

#include "window.h"
#include "font.h"
#include "keyboard.h"

#include "menu.h"
#include "game.h" 

enum GameModes
{
    TitleScreen,
    Game,
	GameOver
};

const int KEY_DELAY = 150;

int OPENGL_XRES = 800;
int OPENGL_YRES = 630;
int OPENGL_FULLSCREEN = false;

Window win;

DWORD tickCount;

int mouseCoords [2];
bool mouseLeftButtonClicked = false;

Font verdana,
	 courier;

GameModes GameMode;

void Initialize()
{            
	verdana.init (100, 120, "Verdana", win);
	courier.init (40, 100, "Courier New", win);

	GameMode = TitleScreen;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmd, int n)
{
	MSG msg = { 0 };
	bool done = false;
	Menu menu;
	AdoktrisGame game;
	DWORD tickCountPreviousUpdate = 0,
	    tickCountKeyPressed [2] = { 0, 0 };
	KeyBoardState oldState,
	              newState;
	KeyBoard keyboard;

	if (!win.create ("AdoktrisGL"))
		return 0;

	Initialize ();

	DWORD startTime = GetTickCount ();

	srand (startTime);

	while (!done)
	{
			if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					done = true;
				else
				{
					TranslateMessage (&msg);
					DispatchMessage (&msg);
				}
			}
			else
			{
				glEnable (GL_POINT_SMOOTH);
				glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
				glEnable (GL_LINE_SMOOTH);
				glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);

				glClearColor (.38f, .58f, .93f, 1);
				glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glMatrixMode (GL_PROJECTION);
				glLoadIdentity ();

				switch (GameMode)
				{
				case TitleScreen:
					if (GetAsyncKeyState (VK_ESCAPE))
						done = true;

					if (GetAsyncKeyState (VK_UP) | GetAsyncKeyState (VK_DOWN))
					{
						menu.ChangeState ();
						while (GetAsyncKeyState (VK_UP) || GetAsyncKeyState (VK_DOWN));
					}

					if (GetAsyncKeyState (VK_RETURN))
					{
						GameMode = Game;
						game.SetNumberPlayers (menu.GetState ());
						game.Start ();
					}

					menu.Draw ();
					break;

				case Game:
					if (GetAsyncKeyState (VK_ESCAPE))
					{
						GameMode = TitleScreen;
						while (GetAsyncKeyState (VK_ESCAPE));
					}

					if (game.IsGameOver ())
						GameMode = GameOver;

					newState = keyboard.GetState ();

					switch (menu.GetState ())
					{
					case 1:
						if (newState.IsKeyDown (VK_UP) || newState.IsKeyDown ('W'))
						{
							if (!oldState.IsKeyDown (VK_UP) && !oldState.IsKeyDown ('W'))
								game.RotateCurrentPattern (0);
						}
						else if (newState.IsKeyDown (VK_LEFT) || newState.IsKeyDown ('A'))
						{
							if ((!oldState.IsKeyDown (VK_LEFT) && !oldState.IsKeyDown ('A')) || tickCount - tickCountKeyPressed [0] > KEY_DELAY)
							{
								tickCountKeyPressed [0] = tickCount;
								game.MoveLeftCurrentPattern (0);
			                }
                        }
						else if (newState.IsKeyDown (VK_RIGHT) || newState.IsKeyDown ('D'))
						{
							if ((!oldState.IsKeyDown (VK_RIGHT) && !oldState.IsKeyDown ('D')) || tickCount - tickCountKeyPressed [0] > KEY_DELAY)
							{
								tickCountKeyPressed [0] = tickCount;
								game.MoveRightCurrentPattern (0);
			                }
                        }
						else if (newState.IsKeyDown (VK_DOWN) || newState.IsKeyDown ('S'))
						{
							if (!oldState.IsKeyDown (VK_DOWN) && !oldState.IsKeyDown ('S'))
								game.DropCurrentPattern (0);
						}
						break;

					case 2:
						if (newState.IsKeyDown ('W'))
						{
							if (!oldState.IsKeyDown ('W'))
								game.RotateCurrentPattern (0);
						}
						else if (newState.IsKeyDown ('A'))
						{
							if (!oldState.IsKeyDown ('A') || tickCount - tickCountKeyPressed [0] > KEY_DELAY)
							{
								tickCountKeyPressed [0] = tickCount;
								game.MoveLeftCurrentPattern (0);
			                }
                        }
						else if (newState.IsKeyDown ('D'))
						{
							if (!oldState.IsKeyDown ('D') || tickCount - tickCountKeyPressed [0] > KEY_DELAY)
							{
								tickCountKeyPressed [0] = tickCount;
								game.MoveRightCurrentPattern (0);
							}
						}
						else if (newState.IsKeyDown ('S'))
						{
							if (!oldState.IsKeyDown ('S'))
								game.DropCurrentPattern (0);
						}

						if (newState.IsKeyDown (VK_UP))
						{
							if (!oldState.IsKeyDown (VK_UP))
								game.RotateCurrentPattern (1);
						}
						else if (newState.IsKeyDown (VK_LEFT))
						{
							if (!oldState.IsKeyDown (VK_LEFT) || tickCount - tickCountKeyPressed [1] > KEY_DELAY)
							{
								tickCountKeyPressed [1] = tickCount;
								game.MoveLeftCurrentPattern (1);
							}
						}
						else if (newState.IsKeyDown (VK_RIGHT))
						{
							if (!oldState.IsKeyDown (VK_RIGHT) || tickCount - tickCountKeyPressed [1] > KEY_DELAY)
							{
								tickCountKeyPressed [1] = tickCount;
								game.MoveRightCurrentPattern (1);
							}
						}
						else if (newState.IsKeyDown (VK_DOWN))
                        {
							if (!oldState.IsKeyDown (VK_DOWN))
								game.DropCurrentPattern (1);
						}
						break;
					}

					oldState = newState;

					tickCount = GetTickCount () - startTime;

					if (tickCount - tickCountPreviousUpdate > 2)
					{
						game.UpdateVariables ();
						tickCountPreviousUpdate = tickCount;
					}

					game.Draw ();
					break;

				case GameOver:
					if (GetAsyncKeyState (VK_ESCAPE) || GetAsyncKeyState (VK_RETURN))
					{
						GameMode = TitleScreen;
						while (GetAsyncKeyState (VK_ESCAPE) || GetAsyncKeyState (VK_RETURN));
					}

					game.Draw ();
					break;
				}

				SwapBuffers (win.getDC());
			}
	}

	return 1;
}

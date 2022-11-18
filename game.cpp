#include "game.h"

AdoktrisGame::AdoktrisGame ()
{
	playArea = new PlayArea [2];
	lines = new int [2];
	score = new int [2];
	currentPattern4 = new Pattern4 [2];
	newPattern = new bool [2];
	speed = new int [2];
	delay = new int [2];
	numberPlayers = 1;
	notEnter = false;
}

AdoktrisGame::~AdoktrisGame ()
{
}

void AdoktrisGame::Draw ()
{
	char tempChar [9];

	glLoadIdentity ();
	glTranslatef (0, 0, -1.0f);

	playArea [0].Draw ();
	currentPattern4 [0].Draw ();
	if (numberPlayers == 1)
	{
		glColor3f (1, 1, 0);
		courier.write ((570.0f - 400.0f) / 400.0f, (300.0f - 200.0f) / 300.0f, "PLAYER 1");
		courier.write ((570.0f - 400.0f) / 400.0f, (300.0f - 230.0f) / 300.0f, "Lines");
		myitoa (tempChar, lines [0]);
		RightAlign (tempChar, 8);
		courier.write ((570.0f - 400.0f) / 400.0f, (300.0f - 260.0f) / 300.0f, tempChar);
		courier.write ((570.0f - 400.0f) / 400.0f, (300.0f - 290.0f) / 300.0f, "Score");
		myitoa (tempChar, score [0]);
		RightAlign (tempChar, 8);
		courier.write ((570.0f - 400.0f) / 400.0f, (300.0f - 320.0f) / 300.0f, tempChar);
		courier.write ((570.0f - 400.0f) / 400.0f, (300.0f - 350.0f) / 300.0f, "Speed");
		myitoa (tempChar, speed [0]);
		RightAlign (tempChar, 8);
		courier.write ((570.0f - 400.0f) / 400.0f, (300.0f - 380.0f) / 300.0f, tempChar);
	}
	else if (numberPlayers == 2)
	{
		playArea [1].Draw ();
		currentPattern4 [1].Draw ();
		glColor3f (1, 1, 0);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 100.0f) / 300.0f, "PLAYER 1");
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 130.0f) / 300.0f, "Lines");
		myitoa (tempChar, lines [0]);
		RightAlign (tempChar, 8);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 160.0f) / 300.0f, tempChar);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 190.0f) / 300.0f, "Score");
		myitoa (tempChar, score [0]);
		RightAlign (tempChar, 8);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 220.0f) / 300.0f, tempChar);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 250.0f) / 300.0f, "Speed");
		myitoa (tempChar, speed [0]);
		RightAlign (tempChar, 8);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 280.0f) / 300.0f, tempChar);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 340.0f) / 300.0f, "PLAYER 2");
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 370.0f) / 300.0f, "Lines");
		myitoa (tempChar, lines [1]);
		RightAlign (tempChar, 8);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 400.0f) / 300.0f, tempChar);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 430.0f) / 300.0f, "Score");
		myitoa (tempChar, score [1]);
		RightAlign (tempChar, 8);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 460.0f) / 300.0f, tempChar);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 490.0f) / 300.0f, "Speed");
		myitoa (tempChar, speed [1]);
		RightAlign (tempChar, 8);
		courier.write ((310.0f - 400.0f) / 400.0f, (300.0f - 520.0f) / 300.0f, tempChar);
	}

	if (gameOver)
	{
		glColor3f (0, 0, 0);
		verdana.write ((138.0f - 400.0f) / 400.0f, (300.0f - 258.0f) / 300.0f, "GAME OVER");
		glColor3f (1, 0, 0);
		verdana.write ((140.0f - 400.0f) / 400.0f, (300.0f - 260.0f) / 300.0f, "GAME OVER");
	}
}

void AdoktrisGame::SetNumberPlayers (int num)
{
	numberPlayers = num;
}

void AdoktrisGame::Start ()
{
	gameOver = false;
	playArea [0].EmptyFields ();
	for (int i = 0; i < 2; i++)
		lines [i] = 0;
	for (int i = 0; i < 2; i++)
		score [i] = 0;
	newPattern [0] = true;
	newPattern [1] = false;
	speed [0] = 0;
	speed [1] = 0;
	delay [0] = 0;
	delay [1] = 0;

	if (numberPlayers == 1)
	{
		playArea [0].SetPosX (((800 - 300) / 2 - 400) / 400.0f);
		playArea [0].SetPosY (1);
		currentPattern4 [0].SetPlayArea (playArea [0]);
	}
	else if (numberPlayers == 2)
	{
		playArea [1].EmptyFields ();
		playArea [0].SetPosX (-1);
		playArea [0].SetPosY (1);
		playArea [1].SetPosX (((800 - 300) - 400) / 400.0f);
		playArea [1].SetPosY (1);
		newPattern [1] = true;
		currentPattern4 [0].SetPlayArea (playArea [0]);
        currentPattern4 [1].SetPlayArea (playArea [1]);
	}
}

void AdoktrisGame::UpdateVariables ()
{
	if (newPattern [0])
		NewPattern (0);

	if (numberPlayers == 2 && newPattern [1])
		NewPattern (1);

	MoveDown (0);

	if (numberPlayers == 2)
		MoveDown (1);
}

void AdoktrisGame::NewPattern (int player)
{
	int currentBlock = 4;
	int nextBlock;
	int numBlocksSet;
	int temp;

	newPattern [player] = false;

	currentPattern4 [player].EmptyMatrix();
	currentPattern4 [player].setMatrix (currentBlock);
	numBlocksSet = 1;
	while (numBlocksSet < 4)
	{
		temp = rand () % 3;
		if (temp == 0)
		{
			if (currentBlock - 4 >= 0)
				nextBlock = currentBlock - 4;
			else
				temp++;
		}
		if (temp == 1)
		{
			if (currentBlock + 4 < 4 * 4)
				nextBlock = currentBlock + 4;
			else 
				temp++;
		}
		if (temp == 2)
			nextBlock = currentBlock + 1;

		if (!currentPattern4 [player].getMatrix (nextBlock))
		{
			currentPattern4 [player].setMatrix (nextBlock);
			numBlocksSet++;
		}

		if (rand () % 2 == 0)
			currentBlock = nextBlock;
	}

	currentPattern4 [player].SetPositionInPlayArea (3, 0);

	currentPattern4 [player].AlignTop ();
	currentPattern4 [player].Rotate ();
	currentPattern4 [player].AlignTop ();

	currentPattern4 [player].CalcPosXY ();
	if (currentPattern4 [player].Intersects ())
		gameOver = true;
	delay [player] = 0;
}

bool AdoktrisGame::IsGameOver ()
{
	return gameOver;
}

void AdoktrisGame::MoveDown (int player)
{
	delay [player]++;
	if (delay [player] >= (30 - speed [player]))
	{
		delay [player] = 0;
		if (currentPattern4 [player].MoveDown ())
		{
			currentPattern4 [player].IncorporateInPlayArea ();
			playArea [player] = currentPattern4 [player].GetPlayArea ();
			int newLines = playArea [player].ClearLines ();
			lines [player] += newLines;
			switch (newLines)
			{
				case 0:
					break;

				case 1:
					score [player] += 1;
					break;

				case 2:
					score [player] += 3;
					break;

				case 3:
					score [player] += 6;
					break;

				case 4:
			        score [player] += 10;
        			break;
			}
			speed [player] = lines [player] / 20;
			newPattern [player] = true;
			currentPattern4 [player].SetPlayArea (playArea [player]);
		}
	}
}

void AdoktrisGame::RotateCurrentPattern (int player)
{
	currentPattern4 [player].Rotate ();
	currentPattern4 [player].AlignTop ();
}

void AdoktrisGame::MoveLeftCurrentPattern (int player)
{
	currentPattern4 [player].MoveLeft ();
}

void AdoktrisGame::MoveRightCurrentPattern (int player)
{
	currentPattern4 [player].MoveRight ();
}

void AdoktrisGame::DropCurrentPattern (int player)
{
	while (!currentPattern4 [player].MoveDown ());
}
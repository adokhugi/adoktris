#ifndef _GAME_H_
#define _GAME_H_

#include "font.h"
#include "pattern4.h"
#include "myitoa.h"

class AdoktrisGame
{
public:
	AdoktrisGame ();
	~AdoktrisGame ();
	void Draw ();
	void SetNumberPlayers (int num);
	void Start ();
	void UpdateVariables ();
	void NewPattern (int player);
	bool IsGameOver ();
	void MoveDown (int player);
	void RotateCurrentPattern (int player);
	void MoveLeftCurrentPattern (int player);
	void MoveRightCurrentPattern (int player);
	void DropCurrentPattern (int player);

private:
	int numberPlayers;
	PlayArea *playArea;
	int *lines;
	int *score;
	Pattern4 *currentPattern4;
	bool *newPattern;
	int *speed;
	int *delay;
	bool notEnter;
	bool gameOver;
};

extern Font courier;
extern Font verdana;

#endif
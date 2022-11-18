#ifndef _PLAYAREA_H_
#define _PLAYAREA_H_

#include "wcpt2d.h"
#include "block.h"

class PlayArea
{
public:
	PlayArea ();
	~PlayArea ();
	int getNumFieldsX ();
	int getNumFieldsY ();
	void EmptyFields ();
	void Draw ();
	void DrawAt (wcPt2D posXY);
	int ClearLines ();
	float GetPosX ();
	float GetPosY ();
	bool GetField (int pos);
	void SetField (int pos);
	void SetPosX (float x);
	void SetPosY (float y);

private:
	Block BlankBlock;
	Block FilledBlock;
	wcPt2D _posXY;
	bool Fields [200];
};

#endif
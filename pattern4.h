#ifndef _PATTERN4_H_
#define _PATTERN4_H_

#include "wcpt2d.h"
#include "playarea.h"
#include "block.h"

class Pattern4
{
public:
	Pattern4 ();
	~Pattern4 ();
	void EmptyMatrix ();
	void Draw ();
	void DrawAt (wcPt2D posXY);
	void Copy (Pattern4 source);
	void Rotate ();
	void AlignTop ();
	void CalcPosXY ();
	int Width ();
	int Height ();
	void MoveLeft ();
	void MoveRight ();
	bool MoveDown ();
	void RestoreOldPosition ();
	bool Intersects ();
	float getPositionInPlayAreaX ();
	float getPositionInPlayAreaY ();
	void setMatrix (int pos);
	bool getMatrix (int pos);
	void IncorporateInPlayArea ();
	void SetPlayArea (PlayArea playArea);
	void SetPositionInPlayArea (float x, float y);
	PlayArea GetPlayArea ();

private:
	Block TransparentBlock;
	Block FilledBlock;
	wcPt2D _posXY;
	wcPt2D _positionInPlayArea;
	wcPt2D _positionInPlayArea_old;
	bool Matrix [4 * 4];
	PlayArea _playArea;
};

#endif
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "wcpt2d.h"

enum BlockTypes
{
	Transparent,
	Blank,
	Filled
};

class Block
{
public:
	Block ();
	~Block ();
	void Draw ();
	void DrawAt (wcPt2D posXY);
	static float getSizeX ();
	static float getSizeY ();
	void setPosXY (wcPt2D PosXY);
	void setBlockType (BlockTypes type);

private:
	wcPt2D _posXY;
	BlockTypes BlockType;
};

#endif
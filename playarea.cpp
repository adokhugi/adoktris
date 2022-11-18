#include "playarea.h"

PlayArea::PlayArea ()
{
	BlankBlock.setBlockType (Blank);
	FilledBlock.setBlockType (Filled);
}

PlayArea::~PlayArea ()
{
}

int PlayArea::getNumFieldsX ()
{
	return 10;
}

int PlayArea::getNumFieldsY ()
{
	return 20;
}

void PlayArea::EmptyFields ()
{
	for (int i = 0; i < getNumFieldsX () * getNumFieldsY (); i++)
		Fields[i] = false;
}

void PlayArea::Draw ()
{
	DrawAt (_posXY);
}

void PlayArea::DrawAt (wcPt2D posXY)
{
	int pointer = 0;
	wcPt2D tempPosXY = posXY;

	for (int y = 0; y < getNumFieldsY (); y++)
	{
		tempPosXY.x = posXY.x;
		for (int x = 0; x < getNumFieldsX (); x++)
		{
			if (Fields [pointer])
				FilledBlock.DrawAt (tempPosXY);
			else
				BlankBlock.DrawAt (tempPosXY);
			pointer++;
			tempPosXY.x += FilledBlock.getSizeX ();
		}
		tempPosXY.y -= FilledBlock.getSizeY ();
	}
}

int PlayArea::ClearLines ()
{
	int numLines = 0;

	for (int y = (int)getNumFieldsY () - 1; y >= 0; y--)
	{
		bool lineFull = true;
		for (int x = 0; x < getNumFieldsX (); x++)
			if (Fields [y * (int)getNumFieldsX () + x] == false)
				lineFull = false;

		if (lineFull)
		{
			for (int i = y; i > 0; i--)
				for (int x = 0; x < getNumFieldsX (); x++)
					Fields [i * (int)getNumFieldsX () + x] = Fields[(i - 1) * (int)getNumFieldsX () + x];
			for (int x = 0; x < getNumFieldsX (); x++)
				Fields [x] = false;
			numLines++;
			y++;
		}
	}

	return numLines;
}

float PlayArea::GetPosX ()
{
	return _posXY.x;
}

float PlayArea::GetPosY ()
{
	return _posXY.y;
}

bool PlayArea::GetField (int pos)
{
	return Fields [pos];
}

void PlayArea::SetField (int pos)
{
	Fields [pos] = true;
}

void PlayArea::SetPosX (float x)
{
	_posXY.x = x;
}

void PlayArea::SetPosY (float y)
{
	_posXY.y = y;
}

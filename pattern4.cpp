#include "pattern4.h"

Pattern4::Pattern4 ()
{
	FilledBlock.setBlockType (Filled);
	TransparentBlock.setBlockType (Transparent);
}

Pattern4::~Pattern4 ()
{
}

void Pattern4::EmptyMatrix ()
{
	for (int i = 0; i < 4 * 4; i++)
		Matrix[i] = false;
}

void Pattern4::Draw ()
{
	DrawAt (_posXY);
}

void Pattern4::DrawAt (wcPt2D posXY)
{
	int pointer = 0;
	wcPt2D tempPosXY = posXY;

	for (int y = 0; y < 4; y++)
	{
		tempPosXY.x = posXY.x;
		for (int x = 0; x < 4; x++)
		{
			if (Matrix [pointer] == true)
				FilledBlock.DrawAt (tempPosXY);
			else
				TransparentBlock.DrawAt (tempPosXY);
			pointer++;
			tempPosXY.x += FilledBlock.getSizeX ();
		}
		tempPosXY.y -= FilledBlock.getSizeY ();
	}
}

void Pattern4::Copy (Pattern4 source)
{
	for (int i = 0; i < 4 * 4; i++)
		Matrix [i] = source.Matrix [i];
}

void Pattern4::Rotate ()
{
	int pointer = 0;
	bool oldMatrix [4 * 4];
	bool rotMatrix [4 * 4];

	for (int i = 0; i < 4 * 4; i++)
		oldMatrix [i] = Matrix [i];

	for (int x = 4 - 1; x >= 0; x--)
		for (int y = 0; y < 4; y++)
        {
            rotMatrix [pointer] = Matrix [y * 4 + x];
            pointer++;
        }

	for (int i = 0; i < 4 * 4; i++)
		Matrix [i] = rotMatrix [i];

	if (Intersects ())
		for (int i = 0; i < 4 * 4; i++)
			Matrix [i] = oldMatrix [i];
}

void Pattern4::AlignTop ()
{
	bool lineEmpty = true;
	while (lineEmpty)
	{
		for (int x = 0; x < 4; x++)
			if (Matrix[x])
				lineEmpty = false;

		if (lineEmpty)
		{
			for (int y = 0; y < 4 - 1; y++)
				for (int x = 0; x < 4; x++)
					Matrix [y * 4 + x] = Matrix [(y + 1) * 4 + x];

			for (int x = 0; x < 4; x++)
				Matrix [(4 - 1) * 4 + x] = false;
		}
	}
}

void Pattern4::CalcPosXY ()
{
	_posXY.x = _playArea.GetPosX () + _positionInPlayArea.x * FilledBlock.getSizeX ();
	_posXY.y = _playArea.GetPosY () - _positionInPlayArea.y * FilledBlock.getSizeY ();
}

int Pattern4::Width ()
{
	int width = 0;

	for (int y = 0; y < 4; y++)
		for (int x = 4 - 1; x >= 0; x--)
			if (Matrix [y * 4 + x] == true && x > width)
				width = x;

	return width;
}

int Pattern4::Height ()
{
	int height = 0;

	for (int x = 0; x < 4; x++)
		for (int y = 4 - 1; y >= 0; y--)
			if (Matrix[y * 4 + x] == true && y > height)
				height = y;

	return height;
}

void Pattern4::MoveLeft ()
{
	_positionInPlayArea_old.x = _positionInPlayArea.x;
	_positionInPlayArea_old.y = _positionInPlayArea.y;
            
	if (_positionInPlayArea.x > 0)
	{
		_positionInPlayArea.x--;
		CalcPosXY ();
	}

	if (Intersects ())
		RestoreOldPosition ();
}

void Pattern4::MoveRight ()
{
	_positionInPlayArea_old.x = _positionInPlayArea.x;
	_positionInPlayArea_old.y = _positionInPlayArea.y;

	if (_positionInPlayArea.x < _playArea.getNumFieldsX () - 1 - Width ())
	{
		_positionInPlayArea.x++;
		CalcPosXY ();
	}

	if (Intersects ())
		RestoreOldPosition ();
}

bool Pattern4::MoveDown ()
{
	_positionInPlayArea_old.x = _positionInPlayArea.x;
	_positionInPlayArea_old.y = _positionInPlayArea.y;

	if (_positionInPlayArea.y < _playArea.getNumFieldsY () - 1 - Height ())
	{
		_positionInPlayArea.y++;
		CalcPosXY ();
	}
	else
		return true;

	if (Intersects ())
	{
		RestoreOldPosition ();
		return true;
	}

    return false;
}

void Pattern4::RestoreOldPosition ()
{
	_positionInPlayArea.x = _positionInPlayArea_old.x;
	_positionInPlayArea.y = _positionInPlayArea_old.y;
	CalcPosXY ();
}

bool Pattern4::Intersects ()
{
	if (_positionInPlayArea.x + Width () >= _playArea.getNumFieldsX ())
		return true;

	if (_positionInPlayArea.y + Height () >= _playArea.getNumFieldsY ())
		return true;

	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			if (Matrix [y * 4 + x] && _playArea.GetField ((int)((_positionInPlayArea.y + y) * _playArea.getNumFieldsX () + _positionInPlayArea.x + x)))
				return true;

	return false;
}

float Pattern4::getPositionInPlayAreaX ()
{
	return _positionInPlayArea.x;
}

float Pattern4::getPositionInPlayAreaY ()
{
	return _positionInPlayArea.y;
}

void Pattern4::setMatrix (int pos)
{
	Matrix [pos] = true;
}

bool Pattern4::getMatrix (int pos)
{
	return Matrix [pos];
}

void Pattern4::IncorporateInPlayArea ()
{
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			if (Matrix [y * 4 + x])
				_playArea.SetField ((int)((getPositionInPlayAreaY () + y) * _playArea.getNumFieldsX () + getPositionInPlayAreaX () + x));
}

void Pattern4::SetPlayArea (PlayArea playArea)
{
	_playArea = playArea;
}

void Pattern4::SetPositionInPlayArea (float x, float y)
{
	_positionInPlayArea.x = x;
	_positionInPlayArea.y = y;
}

PlayArea Pattern4::GetPlayArea ()
{
	return _playArea;
}
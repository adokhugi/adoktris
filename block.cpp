#include "block.h"

Block::Block ()
{
}

Block::~Block ()
{
}

void Block::Draw ()
{
	DrawAt (_posXY);
}

void Block::DrawAt (wcPt2D posXY)
{
	glLoadIdentity ();
	glTranslatef (0, 0, -1.0f);

	switch (BlockType)
	{
	case Blank:
		glColor3f (1, 1, 1);
		glBegin (GL_POLYGON);
			glVertex2f (posXY.x, posXY.y);
			glVertex2f (posXY.x + getSizeX (), posXY.y);
			glVertex2f (posXY.x + getSizeX (), posXY.y - getSizeY ());
			glVertex2f (posXY.x, posXY.y - getSizeY ());
		glEnd ();
		break;

	case Filled:
		glColor3f (0, 0, 0);
		glBegin (GL_POLYGON);
			glVertex2f (posXY.x, posXY.y);
			glVertex2f (posXY.x + getSizeX (), posXY.y);
			glVertex2f (posXY.x + getSizeX (), posXY.y - getSizeY ());
			glVertex2f (posXY.x, posXY.y - getSizeY ());
		glEnd ();
		glColor3f (1, 1, 0);
		glBegin (GL_POLYGON);
			glVertex2f (posXY.x + .00125f * 3, posXY.y - .0016f * 3);
			glVertex2f (posXY.x + getSizeX () - .00125f * 3, posXY.y - .0016f * 3);
			glVertex2f (posXY.x + getSizeX () - .00125f * 3, posXY.y - getSizeY () + .0016f * 3);
			glVertex2f (posXY.x + .00125f * 3, posXY.y - getSizeY () + .0016f * 3);
		glEnd ();
		glColor3f (0, 0, 0);
		glBegin (GL_POLYGON);
			glVertex2f (posXY.x + .00125f * 3 * 5, posXY.y - .0016f * 3 * 5);
			glVertex2f (posXY.x + getSizeX () - .00125f * 3 * 5, posXY.y - .0016f * 3 * 5);
			glVertex2f (posXY.x + getSizeX () - .00125f * 3 * 5, posXY.y - getSizeY () + .0016f * 3 * 5);
			glVertex2f (posXY.x + .00125f * 3 * 5, posXY.y - getSizeY () + .0016f * 3 * 5);
		glEnd ();
		glColor3f (1, 0, 0);
		glBegin (GL_POLYGON);
			glVertex2f (posXY.x + .00125f * 3 * 6, posXY.y - .0016f * 3 * 6);
			glVertex2f (posXY.x + getSizeX () - .00125f * 3 * 6, posXY.y - .0016f * 3 * 6);
			glVertex2f (posXY.x + getSizeX () - .00125f * 3 * 6, posXY.y - getSizeY () + .0016f * 3 * 6);
			glVertex2f (posXY.x + .00125f * 3 * 6, posXY.y - getSizeY () + .0016f * 3 * 6);
		glEnd ();
		break;

	case Transparent:
		break;
	}
}

float Block::getSizeX ()
{
	return 2 * 30.0f / 800.0f;
}

float Block::getSizeY ()
{
	return 2 * 30.0f / 600.0f;
}

void Block::setPosXY (wcPt2D PosXY)
{
	_posXY.x = PosXY.x;
	_posXY.y = PosXY.y;
}

void Block::setBlockType (BlockTypes type)
{
	BlockType = type;
}
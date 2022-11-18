#include "menu.h"

Menu::Menu ()
{
	state = 1;
}

Menu::~Menu ()
{
}

void Menu::Draw ()
{
	glLoadIdentity ();
	glTranslatef (0, 0, -1.0f);

	glColor3f (1, 0, 0);
	verdana.write (-.43f, .25f, "Adoktris");
	glColor3f (1, 1, 1);
	if (state == 1)
	{
		courier.write (-.43f, -.28f, ">> 1 Player");
		courier.write (-.43f, -.28f - .125f, "   2 Players");
	}
	else if (state == 2)
	{
		courier.write (-.43f, -.28f, "   1 Player");
		courier.write (-.43f, -.28f - .125f, ">> 2 Players");
	}
	glColor3f (1, 1, 0);
	if (state == 1)
		courier.write (-.78f, -.72f, "Controls: Cursor Keys");
	else if (state == 2)
		courier.write (-.78f, -.72f, "Controls: WASD, Cursor Keys");
}

void Menu::ChangeState ()
{
	state = 3 - state;
}

int Menu::GetState ()
{
	return state;
}
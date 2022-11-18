#ifndef _MENU_H_
#define _MENU_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "font.h"

class Menu
{
public:
	Menu ();
	~Menu ();
	void Draw ();
	void ChangeState ();
	int GetState ();

private:
	int state;
};

extern Font verdana;
extern Font courier;

#endif
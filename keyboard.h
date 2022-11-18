#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <windows.h>
#include "keyboardstate.h"

class KeyBoard
{
public:
	KeyBoard ();
	~KeyBoard ();
	KeyBoardState GetState ();

private:
};

#endif
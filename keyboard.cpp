#include "keyboard.h"

KeyBoard::KeyBoard ()
{
}

KeyBoard::~KeyBoard ()
{
}

KeyBoardState KeyBoard::GetState ()
{
	KeyBoardState newKeyBoardState;

	for (int i = 0; i < 256; i++)
		if (GetAsyncKeyState ((char) i))
			newKeyBoardState.SetState ((char) i);

	return newKeyBoardState;
}


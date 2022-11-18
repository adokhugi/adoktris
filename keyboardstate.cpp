#include "keyboardstate.h"

KeyBoardState::KeyBoardState ()
{
	for (int i = 0; i < 256; i++)
		KeyState [i] = false;
}

KeyBoardState::~KeyBoardState ()
{
}

void KeyBoardState::SetState (char key)
{
	KeyState [key] = true;
}

bool KeyBoardState::IsKeyDown (char key)
{
	return KeyState [key];
}

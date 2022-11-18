#ifndef _KEYBOARDSTATE_H_
#define _KEYBOARDSTATE_H_

class KeyBoardState
{
public:
	KeyBoardState ();
	~KeyBoardState ();
	void SetState (char key);
	bool IsKeyDown (char key);

private:
	bool KeyState [256];
};

#endif
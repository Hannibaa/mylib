#pragma once
#include <Windows.h>

#define KeyOn(Key)           GetAsyncKeyState(Key) & 0x8000
#define KeyReleased(Key)     GetAsyncKeyState(Key) & 0x0001
#define KeyPressed(Key)      GetAsyncKeyState(Key) & 0x8001

#define TITLE(wtitle)         SetConsoleTitle(wtitle)

#define _u(Char)            ((unsigned)Char)

bool get_out() {

	if ( KeyOn(VK_ESCAPE)) return true;
	else return false;
	
}
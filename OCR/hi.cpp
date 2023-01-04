#include <stdio.h>
#include<iostream>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main() {

	OpenClipboard(0);
	EmptyClipboard();
	const char* op = "How Are You?";
	const size_t ln = strlen(op) + 1;
	HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, ln);
	memcpy(GlobalLock(h), op, ln);
	GlobalUnlock(h);
	SetClipboardData(CF_TEXT, h);
	CloseClipboard();
	getch();

}

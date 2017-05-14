#include <Windows.h>
#include <string>
#include <stdint.h>

#include "..\Headers\GameMain.h"
#include "..\Headers\Constants.h"

#include "..\..\BitmapFont.h"

BitmapFont* bitmapFont = nullptr;

/**
* create game object
*/
bool Create(const HWND /*hWnd*/)
{
    bitmapFont = new BitmapFont();
    return bitmapFont->Create(".\\Resources\\sjis.bmp");;
}

/**
* update frame
*/
void Update(const DWORD /*nowTime*/)
{

}

/**
* draw game object
*/
void Draw(const HDC hDC)
{
    bitmapFont->Draw(hDC);
}

/**
* destroy game object
*/
void Destroy()
{
    bitmapFont->Destroy();
    delete bitmapFont;
}

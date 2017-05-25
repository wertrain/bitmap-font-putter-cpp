#include <Windows.h>
#include <stdint.h>

#include "..\Headers\GameMain.h"
#include "..\Headers\Constants.h"

#include "..\..\BitmapFont.h"

BitmapFont* g_bitmapFont = nullptr;

/**
 * create game object
 */
bool Create(const HWND /*hWnd*/)
{
    g_bitmapFont = new BitmapFont();
    return g_bitmapFont->Create(".\\Resources\\sjis.bmp");
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
    g_bitmapFont->Draw(hDC);
}

/**
 * destroy game object
 */
void Destroy()
{
    g_bitmapFont->Destroy();
    delete g_bitmapFont;
    g_bitmapFont = nullptr;
}

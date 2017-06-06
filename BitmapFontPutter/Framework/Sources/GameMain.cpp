#include <Windows.h>
#include <stdint.h>

#include "..\Headers\GameMain.h"
#include "..\Headers\Constants.h"

#include "..\..\CharCodeConverter.h"
#include "..\..\BitmapFont.h"

BitmapFont* g_bitmapFont = nullptr;

/**
 * create game object
 */
bool Create(const HWND /*hWnd*/)
{
    g_bitmapFont = new BitmapFont();
    if (!g_bitmapFont->Create(".\\Resources\\sjis.bmp"))
        return false;
    return true;
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
    int32_t x = 16, y = 32;
    g_bitmapFont->DrawString(hDC, x, y, L"昔の話である。須々木乙彦は古着屋へはいって、"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"君のところに黒の無地の羽織はないか、と言った。"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"「セルなら、ございます。」"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"昭和五年の十月二十日、東京の街路樹の葉は、風に散りかけていた。"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"「まだセルでも、おかしくないか。」"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"「もっともっとお寒くなりましてからでも、"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"黒の無地なら、おかしいことはございませぬ。」"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"「よし。見せて呉れ。」"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"「あなたさまがお召しになるので？」"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"角帽をあみだにかぶり、袖口がぼろぼろの学生服を着ていた。"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"「そうだ。」差し出されたセルの羽織をその学生服の上にさっと羽織って、"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"「短かくないか。」五尺七寸ほどの、痩せてひょろ長い大学生であった。"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"「セルのお羽織なら、かえって少し短かめのほうが。」"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"「粋か。いくらだ。」"); y += BitmapFont::FONT_CHAR_HEIGHT;
}

/**
 * destroy game object
 */
void Destroy()
{
    if (g_bitmapFont != nullptr)
    {
        g_bitmapFont->Destroy();
        delete g_bitmapFont;
        g_bitmapFont = nullptr;
    }
}

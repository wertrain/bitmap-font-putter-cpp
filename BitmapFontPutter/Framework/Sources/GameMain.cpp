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
    g_bitmapFont->DrawString(hDC, x, y, L"�̘̂b�ł���B�{�X�؉��F�͌Ò����ւ͂����āA"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"�N�̂Ƃ���ɍ��̖��n�̉H�D�͂Ȃ����A�ƌ������B"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"�u�Z���Ȃ�A�������܂��B�v"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"���a�ܔN�̏\����\���A�����̊X�H���̗t�́A���ɎU�肩���Ă����B"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"�u�܂��Z���ł��A���������Ȃ����B�v"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"�u�����Ƃ����Ƃ������Ȃ�܂��Ă���ł��A"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"���̖��n�Ȃ�A�����������Ƃ͂������܂��ʁB�v"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"�u�悵�B�����Č���B�v"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"�u���Ȃ����܂��������ɂȂ�̂ŁH�v"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"�p�X�����݂��ɂ��Ԃ�A�������ڂ�ڂ�̊w�����𒅂Ă����B"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"�u�������B�v�����o���ꂽ�Z���̉H�D�����̊w�����̏�ɂ����ƉH�D���āA"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"�u�Z�����Ȃ����B�v�܎ڎ����قǂ́A�����ĂЂ�뒷����w���ł������B"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"�u�Z���̂��H�D�Ȃ�A�������ď����Z���߂̂ق����B�v"); y += BitmapFont::FONT_CHAR_HEIGHT;
    g_bitmapFont->DrawString(hDC, x, y, L"�u�����B�����炾�B�v"); y += BitmapFont::FONT_CHAR_HEIGHT;
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

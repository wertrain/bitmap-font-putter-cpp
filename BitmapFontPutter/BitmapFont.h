#ifndef BITMAPFONT_H_
#define BITMAPFONT_H_

class CharCodeConverter;

/**
 * Bitmapでフォント画像を管理するクラス
 *
 */
class BitmapFont
{
public:
    enum
    {
        FONT_CHAR_WIDTH = 31,
        FONT_CHAR_HEIGHT = 37,
        FONT_BIT = 4
    };

public:
    BitmapFont();
    ~BitmapFont();
    bool Create(const char* filename);
    void Destroy();

    uint32_t Draw(const HDC hDC);
    uint32_t DrawSJISChar(const HDC hDC, const int32_t x, const int32_t y, const int32_t c);
    void DrawSJISString(const HDC hDC, const int32_t x, const int32_t y, const char* str);
    uint32_t DrawChar(const HDC hDC, const int32_t x, const int32_t y, const int32_t c);
    void DrawString(const HDC hDC, const int32_t x, const int32_t y, const wchar_t* str);

protected:
    bool GetCharWidth(const uint32_t charPos, int32_t *minWidth, int32_t *maxWidth);
    uint32_t GetCharPos(const uint32_t c);

protected:
    uint8_t* m_pBmpRawData;
    uint8_t* m_pBmpPixelBuffer;
    uint32_t m_BmpWidth;
    uint32_t m_BmpHeight;
    uint32_t m_BmpCharLizeSize;
    CharCodeConverter* m_CharCodeConverter;
};

#endif // BITMAPFONT_H_

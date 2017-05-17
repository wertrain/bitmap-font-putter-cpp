#ifndef BITMAPFONT_H
#define BITMAPFONT_H

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

    uint32_t Draw(const HDC hdc);

protected:
    uint32_t BitmapFont::GetCharPos(const uint32_t c);

protected:
    HBITMAP m_hBmpData;
    BITMAP m_BmpData;
    HDC m_hMemdc;
    uint8_t* m_pBmpRawData;
    uint8_t* m_pBmpPixelBuffer;
    uint32_t m_BmpWidth;
    uint32_t m_BmpHeight;
};

#endif // BITMAPFONT_H

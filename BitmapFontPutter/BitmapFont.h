#ifndef BITMAPFONT_H_
#define BITMAPFONT_H_

class CharCodeConverter;

/**
 * Bitmapを読み込みフォント画像を描画するクラス
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

    /**
     * Shift-JIS コードを指定し文字を描画します。
     * @param hDC デバイスコンテキスト
     * @param x 表示位置X
     * @param y 表示位置Y
     * @param c Shift-JIS 文字
     * @return 描画文字幅
     */
    uint32_t DrawSJISChar(const HDC hDC, const int32_t x, const int32_t y, const int32_t c);
    /**
     * Shift-JIS コードを指定し文字列を描画します。
     * @param hDC デバイスコンテキスト
     * @param x 表示位置X
     * @param y 表示位置Y
     * @param str Shift-JIS 文字列
     */
    void DrawSJISString(const HDC hDC, const int32_t x, const int32_t y, const char* str);
    /**
     * Unicode を指定し文字を描画します。
     * @param hDC デバイスコンテキスト
     * @param x 表示位置X
     * @param y 表示位置Y
     * @param c Unicode 文字
     * @return 描画文字幅
     */
    uint32_t DrawChar(const HDC hDC, const int32_t x, const int32_t y, const int32_t c);
    /**
     * Unicode を指定し文字列を描画します。
     * @param hDC デバイスコンテキスト
     * @param x 表示位置X
     * @param y 表示位置Y
     * @param str Unicode 文字列
     */
    void DrawString(const HDC hDC, const int32_t x, const int32_t y, const wchar_t* str);
    /**
     * 文字色を設定します。
     * @param r 赤成分
     * @param g 緑成分
     * @param b 青成分
     */
    void SetColor(const uint8_t r, const uint8_t g, const uint8_t b);

protected:
    bool GetCharWidth(const uint32_t charPos, int32_t *minWidth, int32_t *maxWidth);
    uint32_t GetCharPos(const uint32_t c);

protected:
    uint8_t* m_pBmpRawData;
    uint8_t* m_pBmpPixelBuffer;
    uint32_t m_BmpWidth;
    uint32_t m_BmpHeight;
    uint32_t m_BmpCharLizeSize;
    uint32_t m_Color;
    CharCodeConverter* m_CharCodeConverter;
};

#endif // BITMAPFONT_H_

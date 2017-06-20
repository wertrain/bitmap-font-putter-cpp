#ifndef BITMAPFONT_H_
#define BITMAPFONT_H_

class CharCodeConverter;

/**
 * Bitmap��ǂݍ��݃t�H���g�摜��`�悷��N���X
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
     * Shift-JIS �R�[�h���w�肵������`�悵�܂��B
     * @param hDC �f�o�C�X�R���e�L�X�g
     * @param x �\���ʒuX
     * @param y �\���ʒuY
     * @param c Shift-JIS ����
     * @return �`�敶����
     */
    uint32_t DrawSJISChar(const HDC hDC, const int32_t x, const int32_t y, const int32_t c);
    /**
     * Shift-JIS �R�[�h���w�肵�������`�悵�܂��B
     * @param hDC �f�o�C�X�R���e�L�X�g
     * @param x �\���ʒuX
     * @param y �\���ʒuY
     * @param str Shift-JIS ������
     */
    void DrawSJISString(const HDC hDC, const int32_t x, const int32_t y, const char* str);
    /**
     * Unicode ���w�肵������`�悵�܂��B
     * @param hDC �f�o�C�X�R���e�L�X�g
     * @param x �\���ʒuX
     * @param y �\���ʒuY
     * @param c Unicode ����
     * @return �`�敶����
     */
    uint32_t DrawChar(const HDC hDC, const int32_t x, const int32_t y, const int32_t c);
    /**
     * Unicode ���w�肵�������`�悵�܂��B
     * @param hDC �f�o�C�X�R���e�L�X�g
     * @param x �\���ʒuX
     * @param y �\���ʒuY
     * @param str Unicode ������
     */
    void DrawString(const HDC hDC, const int32_t x, const int32_t y, const wchar_t* str);
    /**
     * �����F��ݒ肵�܂��B
     * @param r �Ԑ���
     * @param g �ΐ���
     * @param b ����
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

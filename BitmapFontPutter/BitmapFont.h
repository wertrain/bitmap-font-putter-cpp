#ifndef BITMAPFONT_H
#define BITMAPFONT_H

/**
 * Bitmap�Ńt�H���g�摜���Ǘ�����N���X
 *
 */
class BitmapFont
{
public:
	enum
	{
		FONT_CHAR_WIDTH = 16,
		FONT_CHAR_HEIGHT = 22,
		FONT_BIT = 4
	};

public:
	BitmapFont();
	~BitmapFont();
	bool ReadFromFile(const std::string& filename);
	void Destroy();

	uint32_t BitmapFont::GetCharPos(const uint32_t c);

protected:
	HBITMAP m_hBmpData;
	BITMAP m_BmpData;
	HDC m_hMemdc;
};

#endif // BITMAPFONT_H

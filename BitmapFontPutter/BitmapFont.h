#ifndef BITMAPFONT_H
#define BITMAPFONT_H

class BitmapFont
{
public:
	BitmapFont();
	~BitmapFont();
	bool ReadFromFile(const std::string& filename);

protected:
	HBITMAP m_hBmpData;
	BITMAP m_BmpData;
	HDC m_hMemdc;
};

#endif // BITMAPFONT_H

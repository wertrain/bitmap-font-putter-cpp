#include <Windows.h>
#include <string>
#include <stdint.h>

#include "BitmapFont.h"

namespace
{
#pragma pack(push,1)
	struct BitmapFileHeader
	{
		uint8_t bfType[2];
		uint16_t bfSize[2];
		uint16_t bfReserved1;
		uint16_t bfReserved2;
		uint16_t bfOffBits[2];
	};
#pragma pack(pop)

#pragma pack(push,1)
	struct BitmapInfoHeader
	{
		uint32_t biSize;
		int32_t biWidth;
		int32_t biHeight;
		uint16_t biPlanes;
		uint16_t biBitCount;
		uint32_t biCompression;
		uint32_t biSizeImage;
		int32_t biXPixPerMeter;
		int32_t biYPixPerMeter;
		uint32_t biClrUsed;
		uint32_t biClrImportant;
	};
#pragma pack(pop)
}

BitmapFont::BitmapFont()
	: m_hBmpData(NULL)
	, m_hMemdc(NULL)
{
}

BitmapFont::~BitmapFont()
{
}

bool BitmapFont::ReadFromFile(const std::string& filename)
{
	// 画像読み込み
	m_hBmpData = (HBITMAP)LoadImage(NULL, filename.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (m_hBmpData == NULL)
		return false;

	// ビットマップの情報を取得
	GetObject(m_hBmpData, sizeof(BITMAP), &m_BmpData);
	// メモリオブジェクトにコピー
	m_hMemdc = CreateCompatibleDC(NULL);
	SelectObject(m_hMemdc, m_hBmpData);

	return true;
}

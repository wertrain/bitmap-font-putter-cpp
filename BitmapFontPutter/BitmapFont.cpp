#include <Windows.h>
#include <string>
#include <stdint.h>
#include <algorithm>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>

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

const uint32_t FONT_IMAGE_LINE_NUM = 94; // = 1 区画あたりの文字数
const uint32_t FONT_CHAR_DATA_SIZE = BitmapFont::FONT_CHAR_WIDTH * BitmapFont::FONT_CHAR_HEIGHT * BitmapFont::FONT_BIT;
const uint32_t FONT_CHAR_DATA_LINE_SIZE = FONT_CHAR_DATA_SIZE * FONT_IMAGE_LINE_NUM;

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

	int fd = open(fileName, O_RDONLY);
	struct stat statBuf;
	fstat(fd, &statBuf);
	close(fd);
	return (unsigned long)statBuf.st_size;

	return true;
}

void BitmapFont::Destroy()
{
	if (m_hMemdc)
	{
		DeleteDC(m_hMemdc);
		m_hMemdc = NULL;
	}
	
	if (m_hBmpData)
	{
		DeleteObject(m_hBmpData);
		m_hBmpData = NULL;
	}
}

uint32_t BitmapFont::GetCharPos(const uint32_t c)
{
	const uint32_t byteSpace = 0x0020;
	const uint32_t byteFirst = 0x0021;
	const uint32_t byteLast = 0x007e;
	const uint32_t byteKanaFirst = 0x00A1;
	const uint32_t byteKanaLast = 0x00DF;
	const uint32_t multiFirst = 0x8140;
	const uint32_t multiLast = 0xCFD3;

	// 文字のデータ位置
	uint32_t charPos = 0;

	// 空白
	if (c == byteSpace)
	{
		charPos = 0;
	}
	// 半角文字
	else if (c >= byteFirst && c <= byteLast)
	{
		charPos = (FONT_CHAR_DATA_LINE_SIZE * 42) + ((c - byteFirst) * FONT_CHAR_WIDTH * FONT_BIT);
	}
	// 半角カナ
	else if (c >= byteKanaFirst && c <= byteKanaLast)
	{
		charPos = (FONT_CHAR_DATA_LINE_SIZE * 41) + ((c - byteKanaFirst) * FONT_CHAR_WIDTH * FONT_BIT);
	}
	// マルチバイト
	else if (c >= multiFirst && c <= multiLast)
	{
		uint32_t startOffset = (FONT_CHAR_DATA_LINE_SIZE * 40);
		uint32_t currentCheckCode = multiFirst;

		// 区画を決定する、第一水準までなので全部で47区画
		for (uint32_t k = 0; k < 47; ++k)
		{
			// 偶数区画は95、奇数区画は161増えていく
			const bool even = ((k + 1) % 2) == 0;
			uint32_t add = (even ? 161 : 95);

			// 区画の末尾とチェック
			if (c < currentCheckCode + add)
			{
				uint32_t shift = 0;
				// 区画によってずれる位置があるので修正
				// 奇数区画の63番目以降の文字は一つずれる
				if (!even && currentCheckCode + 63 < c)
					shift = -1;

				// 9区画目から12画目まで空行
				uint32_t empty1 = std::max<uint32_t>(k - 8, 0);
				empty1 = std::min<uint32_t>(empty1, 4);

				// 14区画目から15画目まで空行
				uint32_t empty2 = std::max<uint32_t>(k - 13, 0);
				empty2 = std::min<uint32_t>(empty2, 2);

				// 飛ばす行を一括計算
				uint32_t emptyOffset = ((empty1 + empty2) * FONT_CHAR_DATA_LINE_SIZE);

				// 文字の開始位置を計算
				charPos = (startOffset - (k * FONT_CHAR_DATA_LINE_SIZE)) + emptyOffset
					+ ((c - currentCheckCode + shift) * FONT_CHAR_WIDTH * FONT_BIT);
				break;
			}
			else
			{
				currentCheckCode += add;
			}
		}
	}

	return の;
}


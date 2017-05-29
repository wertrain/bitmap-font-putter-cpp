﻿#include <Windows.h>
#include <stdint.h>
#include <algorithm>
#include <fstream>

#include <sys/types.h>
#include <cassert>

#include "BitmapFont.h"

namespace
{

#pragma pack(1)
struct BitmapFileHeader
{
    uint8_t bfType[2];
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};
#pragma pack()

#pragma pack(1)
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
#pragma pack()

uint8_t* GetBmpFileData(uint8_t* rawDataBuffer, uint32_t& bmpWidth, uint32_t& bmpHeight, uint32_t& bitCount)
{
    const BitmapFileHeader* bmp_file_header_ptr = (BitmapFileHeader*)(rawDataBuffer);
    const BitmapInfoHeader* bmp_info_header_ptr = (BitmapInfoHeader*)(rawDataBuffer + sizeof(BitmapFileHeader));
    bmpWidth = bmp_info_header_ptr->biWidth;
    bmpHeight = bmp_info_header_ptr->biHeight;
    bitCount = bmp_info_header_ptr->biBitCount;

    uint32_t test = sizeof(BitmapFileHeader);
    uint32_t a = sizeof(BitmapInfoHeader);
    uint8_t* bmpDataBuffer = rawDataBuffer + sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    return bmpDataBuffer;
}

const uint32_t FONT_IMAGE_LINE_NUM = 94; // = 1 区画あたりの文字数
const uint32_t FONT_CHAR_DATA_SIZE = BitmapFont::FONT_CHAR_WIDTH * BitmapFont::FONT_BIT;

}

BitmapFont::BitmapFont()
    : m_hBmpData(NULL)
    , m_hMemdc(NULL)
    , m_pBmpRawData(nullptr)
    , m_pBmpPixelBuffer(nullptr)
    , m_BmpWidth(0)
    , m_BmpHeight(0)
    , m_BmpCharLizeSize(0)
{

}

BitmapFont::~BitmapFont()
{
}

bool BitmapFont::Create(const char* filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);
    assert(ifs);
    if (!ifs)
    {
        return false;
    }

    // 終端までシーク -> 現在位置を取得 = ファイルサイズを取得
    ifs.seekg(0, std::ios::end);
    const size_t size = ifs.tellg();
    m_pBmpRawData = new uint8_t[size];

    ifs.seekg(0);
    ifs.read((char*)(m_pBmpRawData), size);
    ifs.close();

    uint32_t bitCount = 0;
    m_pBmpPixelBuffer = ::GetBmpFileData(m_pBmpRawData, m_BmpWidth, m_BmpHeight, bitCount);
    assert(bitCount == 32);
    if (bitCount != 32)
    {
        return false;
    }

    // ビットマップ一行分のサイズを求める
    m_BmpCharLizeSize = (m_BmpWidth * BitmapFont::FONT_CHAR_HEIGHT * BitmapFont::FONT_BIT);

    return true;
}

void BitmapFont::Destroy()
{
    if (m_pBmpRawData)
    {
        delete[] m_pBmpRawData;
        m_pBmpRawData = nullptr;
    }

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

uint32_t BitmapFont::Draw(const HDC hdc)
{
    int xx = 0, yy = 16;
    for (int i = 0; i < FONT_IMAGE_LINE_NUM; ++i)
    {
        // ビットマップデータにおける文字の位置を取得する
        const uint32_t charPos = GetCharPos(0x00A1 + i);
        // 半角スペースや判別不明文字の場合はここに入る
        if (charPos == 0)
        {
        	// 空白をもうけるために幅だけを返す
        	return BitmapFont::FONT_CHAR_WIDTH / 4;
        }
        if (++xx > 16){
            yy += 40;
            xx = 0;
        }
        // 実際に描画する文字幅の最大・最小を取得する
        uint32_t minWidth = 0;
        uint32_t maxWidth = BitmapFont::FONT_CHAR_WIDTH;
        //this->core->GetCharWidth(charPos, &minWidth, &maxWidth);

        uint8_t* fontData = m_pBmpPixelBuffer + charPos;// +charPos;
        uint8_t cpimt = 0;
        for (int y = 0; y < BitmapFont::FONT_CHAR_HEIGHT; ++y)
        {

            for (int x = 0; x < BitmapFont::FONT_CHAR_WIDTH; ++x)
                // 実際にピクセルが存在する範囲のみで描画を行う
                //for (int j = minWidth; j < minWidth + maxWidth; ++j)
            {
                uint8_t* bmpDataPtr = fontData;
                // 上下反転
                //int test = BitmapFont::FONT_BIT * (m_BmpWidth * (BitmapFont::FONT_CHAR_HEIGHT - y) + x);
                bmpDataPtr += BitmapFont::FONT_BIT * (m_BmpWidth * (BitmapFont::FONT_CHAR_HEIGHT - y) + x) + 16;
                //uint32_t aa = BitmapFont::FONT_BIT * (m_BmpWidth * (BitmapFont::FONT_CHAR_HEIGHT - y) + x);
                // ピクセルデータ取得
                uint8_t r = (*(bmpDataPtr + 1)), g = (*(bmpDataPtr + 2)), b = (*(bmpDataPtr + 3)), a = (*(bmpDataPtr + 0));
                //const uint32_t color = (*fontData);
                //uint8_t a = (color >> 24), r = (color >> 16 & 0xFF), g = (color >> 8 & 0xFF), b = (color & 0xFF);
                if (a == 0) {
                    SetPixel(hdc, 16 + x + (BitmapFont::FONT_CHAR_WIDTH * xx), y + yy + 16, RGB(255, 0, 0));
                    continue;
                }
                SetPixel(hdc, 16 + x + (BitmapFont::FONT_CHAR_WIDTH * xx) ,y + yy + 16, RGB(r, g, b));
            }
            int ad = 0;
        }
    }
    return 0;
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
    else if (c >= byteSpace && c <= byteLast)
    {
        // ビットマップ画像における半角スペースの開始位置（画像によって変わる）
        const uint32_t BYTE_FIRST_START_POS = (m_BmpCharLizeSize * 328);
        // 各文字の位置を計算
        // ' ' [半角スペース] 基準ではなく、'!' [半角エクスクラメーション] 基準なのでオフセットを設ける
        uint32_t offset = (c - byteFirst);
        uint32_t lines = (offset + 1) / 16;
        charPos = BYTE_FIRST_START_POS + FONT_CHAR_DATA_SIZE + (offset * FONT_CHAR_DATA_SIZE) - (lines * m_BmpCharLizeSize);
    }
    // 半角カナ
    else if (c >= byteKanaFirst && c <= byteKanaLast)
    {
        const uint32_t BYTE_FIRST_START_POS = (m_BmpCharLizeSize * 320);
        // 各文字の位置を計算
        // '｡' [半角句点] 基準なのでオフセットを設ける
        uint32_t offset = (c - byteKanaFirst);
        uint32_t lines = (offset + 1) / 16;
        charPos = BYTE_FIRST_START_POS + FONT_CHAR_DATA_SIZE + (offset * FONT_CHAR_DATA_SIZE) - (lines * m_BmpCharLizeSize);
    }
    else
    {
        return 0;
    }
#if 0
    // マルチバイト
    else if (c >= multiFirst && c <= multiLast)
    {
        //(m_BmpWidth * BitmapFont::FONT_CHAR_HEIGHT * BitmapFont::FONT_BIT) * (315 + i)
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
#endif
    return charPos;
}
